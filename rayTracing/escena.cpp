#include "escena.hpp"

//------------------------------- PRIVADAS -----------------------------------//
InterseccionPrimitiva Escena::intersectarRayo(Rayo rayo){

    vector<Primitiva*> primitivasIntersectadas;
    vector<float> distanciasPrimitivas;
    Punto3D puntoInterseccion;
    InterseccionPrimitiva retorno;

    //Recorro todas las primitivas de mi escena y si intersecta con el rayo, la guardo
    for(const auto& pri : primitivas){  
        Interseccion inter = get<0>(pri->interseccionRayo(rayo));
        if(inter.intersecta){
            primitivasIntersectadas.push_back(pri);
            float minDistancia = calcularMIN(inter.distancia);
            for(int i = 0; i < inter.distancia.size(); i++){
                if(inter.distancia[i] == minDistancia){
                    puntoInterseccion = inter.puntoInterseccion[i];
                }
            }
            distanciasPrimitivas.push_back(minDistancia);
        }
    }

    //Tengo una lista de primitivas intersectadas por el rayo
    // Hay que ver que primitiva esta por delante
    if(primitivasIntersectadas.empty()){
        retorno.primitiva = nullptr;
        retorno.puntoInterseccion = Punto3D(0,0,0);
        return retorno;
    }

    Primitiva* primitivaVisible;
    //Obtengo la distancia a la que se encuentra la primera primitiva (la visible)
    float minimaDistancia = calcularMIN(distanciasPrimitivas);

    // Recorro todo el vector de primitivas hasta que encuentro la que tiene el valor de distancia minimo
    for(int i = 0; i < primitivasIntersectadas.size(); i++){
        if(distanciasPrimitivas[i] == minimaDistancia){
            // Cuando la encuentro, la guardo
            retorno.primitiva = primitivasIntersectadas[i];
            retorno.puntoInterseccion = puntoInterseccion;
            break;
        }
    }
    // Devuleve la primitiva intersectada
    return retorno;
}

Punto3D Escena::generarPuntoAleatorioEnPixel(mt19937 gen, Pixel pixel){
    // General altura y anchura aleatoria dentro del tamaño del pixel.
    //mt19937 gen(rd());

    uniform_real_distribution<float> distribucion_altura(pixel.getPuntoDchInf().gety(),
                                                         pixel.getPuntoIzqSup().gety());
    uniform_real_distribution<float> distribucion_anchura(pixel.getPuntoIzqSup().getx(),
                                                         pixel.getPuntoDchInf().getx());                 
    uniform_real_distribution<float> distribucion_profundidad(pixel.getPuntoIzqSup().getz(),
                                                         pixel.getPuntoDchInf().getz());

    float puntoAltura = distribucion_altura(gen);
    float puntoAnchura = distribucion_anchura(gen);
    float puntoProfundidad = distribucion_profundidad(gen);

    return Punto3D(puntoAnchura, puntoAltura, puntoProfundidad);
}

//------------------------------- FIN PRIVADAS -------------------------------//



//--------------------------------- PUBLICAS ---------------------------------//
ImagenPPM Escena::crearImagenPPM(){
    float valorMax = 0;
    float v;
    vector<RGB> pixeles;
    vector<Pixel> arrayPixeles = camara.getCuadriculaPixeles();
    for(auto p : arrayPixeles){
        //cout << "Color del pixel de la cuadricula en crearImagen: " << p.getColor() << endl;
        v = p.getColor().maximo();
        pixeles.push_back(p.getColor());
        if(v > valorMax){
            valorMax = v;
        }
    }
    string formato = "P3";
    string comentario = "";
    ImagenPPM imagen = ImagenPPM(formato, valorMax, comentario, camara.getTamPlanoImagenBase(), camara.getTamPlanoImagenAltura(), 255, formatoRGB, pixeles);
    return imagen;
}

void Escena::anyadirPrimitiva(Primitiva* primitiva){
    primitivas.push_back(primitiva);
}

void Escena::anyadirLuz(FuenteLuz* luz){
    luces.push_back(luz);
}



void Escena::lanzarRayosDesdeCamara(int nrayos){
    vector<Rayo> listaRayos;
    vector<Pixel> cuadriculaPixeles = camara.getCuadriculaPixeles();
    vector<Pixel> nuevaCuadricula;
    int numeroDeRebotes = 10;

    if(cuadriculaPixeles.empty()){
        throw runtime_error("Error: La cuadrícula de píxeles está vacía.");
    }
    random_device rd;
    RGB valorPixel = RGB();

    for(Pixel p : cuadriculaPixeles){ //Para cada pixel -> lanzar x rayos
        for(int i = 0; i < nrayos; i++) {  // generar x rayos a puntos aleatorios
            mt19937 gen(rd());
            Punto3D puntoAleatorio = generarPuntoAleatorioEnPixel(gen, p);
            Rayo rayoCamaraPixel = Rayo(camara.getOrigen(), puntoAleatorio);
            int reboteActual = 0;

            valorPixel = valorPixel + trazadoDeCaminos(rayoCamaraPixel, reboteActual, numeroDeRebotes);
        }
        nuevaCuadricula.push_back(Pixel(p.getPuntoIzqSup(), p.getPuntoDchInf(), valorPixel/nrayos));
        valorPixel = RGB();
    }
    camara.setCuadricutaPixeles(nuevaCuadricula);
}



RGB Escena::trazadoDeCaminos(Rayo rayo, int reboteActual, int numeroDeRebotes){
    RGB contribucionLuz;

    // Condicion de terminacion
    if(reboteActual > numeroDeRebotes){
        return RGB();
    }

    // Comprobar si el rayo intersecta con primitiva y obtener la interseccion
    // con la primitiva correspondiente
    InterseccionPrimitiva interseccion = intersectarRayo(rayo);
    if(interseccion.intersecta){
        contribucionLuz = contribucionLuz + estimacionSiguienteEvento(interseccion);
    }
    else { // Si no intersecta con nada, se omite el rayo
        return RGB();
    }
    BSDF color = BSDF(interseccion.primitiva->getColor()); // MODIFICAR CUANDO PONGAMOS Ks y Kt !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    tuple<Direccion, RGB> muestreo = color.muestreo(interseccion.puntoInterseccion, rayo.getDireccion(), interseccion.normal);
    RGB colorObtenido = get<1>(muestreo);
    if(colorObtenido.esNegro()){
        return RGB();
    }
    else{
        contribucionLuz = contribucionLuz + colorObtenido +
                          trazadoDeCaminos(Rayo(interseccion.puntoInterseccion,
                          get<0>(muestreo)), reboteActual++, numeroDeRebotes);
        return contribucionLuz;
    }


    // Para cada rayo que intersecta - Lanzar rayos de sombra
    // Es decir, trazar un rayo entre el punto de interseccion y cada
    // una de las luces puntuales y ver si hay alguna primitiva entre
    // ellos. Si lo hay -> el pixel esta en sombra, sino el pixel tiene color

}



RGB Escena::estimacionSiguienteEvento(InterseccionPrimitiva interseccion){
    //Se puede usar la ruleta rusa aqui
    if(interseccion.intersecta){
        RGB contribucion;
        for(auto l : luces){
            RGB contribucionDeLuz;
            // Seguramente aqui habra que comprobar si intersecta con una luz de area
            LuzDeArea* luzArea = static_cast<LuzDeArea*>(l);
            Rayo rayoInterseccionLuz = Rayo(interseccion.puntoInterseccion, l->getCentro());
            
            InterseccionPrimitiva inter = intersectarRayo(rayoInterseccionLuz);
            if(inter.intersecta){
                // Intersecta con primitiva -> el pixel esta a oscuras
            }
            else {
                // La intensidad de la luz en el punto x es:
                // I(x) = (I_0 / d^2) * e^(-alpha*d)
                // Intensidad en el punto = (intensidad de la fuente / distancia^2) * 2'71^(-coeficiente de difusion del medio * distancia)
                // alpha en el aire es 0.01/m
                RGB potInicialPorDistancia2 = RGB(l->getPotencia().getR() / pow(rayoInterseccionLuz.getDireccion().modulus(), 2), 
                                l->getPotencia().getG() / pow(rayoInterseccionLuz.getDireccion().modulus(), 2),
                                l->getPotencia().getB() / pow(rayoInterseccionLuz.getDireccion().modulus(), 2));

                if(luzArea != nullptr){ // Si estamos evaluando una luz de area
                    // Si metemos Efectos de Fresnel o texturas habra que cambiar esto:
                    BSDF bsdf = BSDF(inter.primitiva->getColor());
                    RGB evaluacionEnMaterial = bsdf.evaluacion(); 
                    float porPlano = abs(inter.normal.dot_product(rayoInterseccionLuz.getDireccion().normalize())) *
                                        abs(luzArea->getNormal().dot_product(rayoInterseccionLuz.getDireccion().normalize()*(-1)));
                    contribucionDeLuz = (potInicialPorDistancia2 * evaluacionEnMaterial) * porPlano;
                }
                else { // Si estamos evaluando una luz puntual
                    // Si metemos Efectos de Fresnel o texturas habra que cambiar esto:
                    BSDF bsdf = BSDF(inter.primitiva->getColor());
                    RGB evaluacionEnMaterial = bsdf.evaluacion(); 
                    float porPunto = abs(inter.normal.dot_product(rayoInterseccionLuz.getDireccion().normalize()));
                    contribucionDeLuz = potInicialPorDistancia2 * evaluacionEnMaterial;
                }

            }
            contribucion = contribucion + contribucionDeLuz;
        }
        return contribucion;
    }
    else {
        return RGB();
    }

}



//-------------------------------- IMPRESION ---------------------------------//
