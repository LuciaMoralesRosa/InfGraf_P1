#include "escena.hpp"

//------------------------------- PRIVADAS -----------------------------------//
InterseccionPrimitiva Escena::intersectarRayo(Rayo rayo){
    vector<Primitiva*> primitivasIntersectadas;
    vector<float> distanciasPrimitivas;
    Punto3D puntoInter;
    InterseccionPrimitiva retorno;

    //Recorro todas las primitivas de mi escena y si intersecta con el rayo, la guardo
    for(const auto& pri : primitivas){
        if(pri == nullptr){
            throw runtime_error("El puntero 'pri' es nulo.");
        }  
        Interseccion inter = pri->interseccionRayo(rayo);
        if(inter.intersecta){
            primitivasIntersectadas.push_back(pri);
            float minDistancia = calcularMIN(inter.distancia);
            
            if (inter.distancia.size() != inter.puntoInterseccion.size()) {
                throw runtime_error("Los vectores distancia y puntoInterseccion no tienen el mismo tamaño.");   
            }
            
            for(int i = 0; i < inter.distancia.size(); i++){
                if(inter.distancia[i] == minDistancia){
                    puntoInter = inter.puntoInterseccion[i];
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
        retorno.intersecta = false;
        return retorno;
    }

    //Obtengo la distancia a la que se encuentra la primera primitiva (la visible)
    float minimaDistancia = calcularMIN(distanciasPrimitivas);

    // Recorro todo el vector de primitivas hasta que encuentro la que tiene el valor de distancia minimo
    for(int i = 0; i < primitivasIntersectadas.size(); i++){
        if(distanciasPrimitivas[i] == minimaDistancia){
            // Cuando la encuentro, la guardo
            retorno.primitiva = primitivasIntersectadas[i];
            retorno.puntoInterseccion = puntoInter;
            break;
        }
    }
    // Devuleve la primitiva intersectada
    return retorno;
}

Punto3D Escena::generarPuntoAleatorioEnPixel(mt19937 gen, Pixel pixel){
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
    cout << "Depurando: Array pixeles en crear imagen: " << arrayPixeles[5].getColor() << endl;
    for(auto p : arrayPixeles){
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

    cout << "Depurando: LanzarRayosDesdeCamara Inicio" << endl;

    if(cuadriculaPixeles.empty()){
        throw runtime_error("Error: La cuadrícula de píxeles está vacía.");
    }
    random_device rd;
    RGB valorPixel = RGB(0,0,0);

    cout << "Depurando: LanzarRayosDesdeCamara Antes del for" << endl;
    int depurando = 0;
    for(Pixel p : cuadriculaPixeles){ //Para cada pixel -> lanzar x rayos
        for(int i = 0; i < nrayos; i++) {  // generar x rayos a puntos aleatorios
            mt19937 gen(rd());
            Punto3D puntoAleatorio = generarPuntoAleatorioEnPixel(gen, p);
            Rayo rayoCamaraPixel = Rayo(camara.getOrigen(), puntoAleatorio);
            int reboteActual = 0;
            //cout << "Depurando: LanzarRayosDesdeCamara Antes de pathTracing con depurando = "  << depurando << endl;
            valorPixel = valorPixel + trazadoDeCaminos(rayoCamaraPixel, reboteActual, numeroDeRebotes);
            //cout << "Depurando: LanzarRayosDesdeCamara Despues de pathTracing con valor pixel = " << valorPixel << endl;
            depurando++;
        }
        //cout << "Depurando: LanzarRayosDesdeCamara Antes de insertar en la cuadricula" << endl;
        nuevaCuadricula.push_back(Pixel(p.getPuntoIzqSup(), p.getPuntoDchInf(), valorPixel/nrayos));
        valorPixel = RGB(0,0,0);
    }
    cout << "Depurando: LanzarRayosDesdeCamara Antes de setCuadricula" << endl;
    camara.setCuadricutaPixeles(nuevaCuadricula);
    cout << "Depurando: fin de lanzarRayosDesdeCamara" << endl;
}



RGB Escena::trazadoDeCaminos(Rayo rayo, int reboteActual, int numeroDeRebotes){
    RGB contribucionLuz = RGB(0,0,0);
    // Condicion de terminacion
    if(reboteActual > numeroDeRebotes){
        return RGB(0,0,0);
    }

    // Comprobar si el rayo intersecta con primitiva y obtener la interseccion
    // con la primitiva correspondiente
    InterseccionPrimitiva interseccion = intersectarRayo(rayo);
    if(interseccion.intersecta){
        cout << "Depurando: TrazadoDeCaminos Intersecta yey - Llamamos a estimacionSiguienteEvento" << endl;
        contribucionLuz = contribucionLuz + estimacionSiguienteEvento(interseccion);
    }
    else { // Si no intersecta con nada, se omite el rayo
        return RGB(0,0,0);
    }

    if (interseccion.primitiva == nullptr) {
        throw runtime_error("El puntero 'interseccion.primitiva' es nulo.");
    }

    BSDF color = BSDF(interseccion.primitiva->getColor());
    tuple<Direccion, RGB> muestreo = color.muestreo(interseccion.puntoInterseccion, rayo.getDireccion(), interseccion.normal);
    RGB colorObtenido = get<1>(muestreo);
    if(colorObtenido.esNegro()){
        return RGB(0,0,0);
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
        cout << "Depurando: EstimacionSigEvento intersecta" << endl;
        RGB contribucion = interseccion.primitiva->getColor();  //Modificado
        for(auto l : luces){
            cout << "Depurando: EstimacionSigEvento Para cada luz (esto deberia salir solo una vez) " << endl;
            RGB contribucionDeLuz = RGB(0,0,0);
            // Seguramente aqui habra que comprobar si intersecta con una luz de area
           
            Rayo rayoInterseccionLuz = Rayo(interseccion.puntoInterseccion, l->getCentro());
            
            InterseccionPrimitiva inter = intersectarRayo(rayoInterseccionLuz);
            if(inter.intersecta){
                // Intersecta con primitiva -> el pixel esta a oscuras
                cout << "Depurando: EstimacionSigEvento El rayo hacia la luz SI intersecta con una primitiva" << endl;
            }
            else {
                cout << "Depurando: EstimacionSigEvento El rayo hacia la luz no intersecta con una primitiva - Valor del pixel ahora" << contribucion << endl;

                // La intensidad de la luz en el punto x es:
                // I(x) = (I_0 / d^2) * e^(-alpha*d)
                // Intensidad en el punto = (intensidad de la fuente / distancia^2) * 2'71^(-coeficiente de difusion del medio * distancia)
                // alpha en el aire es 0.01/m
                RGB potInicialPorDistancia2 = RGB(l->getPotencia().getR() / pow(rayoInterseccionLuz.getDireccion().modulus(), 2), 
                                l->getPotencia().getG() / pow(rayoInterseccionLuz.getDireccion().modulus(), 2),
                                l->getPotencia().getB() / pow(rayoInterseccionLuz.getDireccion().modulus(), 2));
                cout << "Depurando: EstimacionSigEvento Despues de potInicialxDist2" << endl;

                if(l->getTipo() == AREA){ // Si estamos evaluando una luz de area
                    LuzDeArea* luzArea = static_cast<LuzDeArea*>(l);
                    cout << "Depurando: EstimacionSigEvento Es luz de area " << endl;

                    // Si metemos Efectos de Fresnel o texturas habra que cambiar esto:
                    BSDF bsdf = BSDF(inter.primitiva->getColor());
                    RGB evaluacionEnMaterial = bsdf.evaluacion(); 
                    float porPlano = abs(inter.normal.dot_product(rayoInterseccionLuz.getDireccion().normalize())) *
                                        abs(luzArea->getNormal().dot_product(rayoInterseccionLuz.getDireccion().normalize()*(-1)));
                    contribucionDeLuz = (potInicialPorDistancia2 * evaluacionEnMaterial) * porPlano;
                }
                else { // Si estamos evaluando una luz puntual
                    // Si metemos Efectos de Fresnel o texturas habra que cambiar esto:
                    LuzPuntual* luzPuntual = static_cast<LuzPuntual*>(l);
                    cout << "Depurando: EstimacionSigEvento luz puntual " << endl;

                    BSDF bsdf = BSDF(inter.primitiva->getColor());
                    RGB evaluacionEnMaterial = bsdf.evaluacion(); 
                    float porPunto = abs(inter.normal.dot_product(rayoInterseccionLuz.getDireccion().normalize()));
                    contribucionDeLuz = potInicialPorDistancia2 * evaluacionEnMaterial;
                }
                cout << "Depurando: EstimacionSigEvento Despues del if else" << endl;
            }
            contribucion = contribucion + contribucionDeLuz;
        }
        cout << "Depurando: EstimacionSigEvento Despues del for de luces - Valor del pixel: " << contribucion << endl;
        return contribucion;
    }
    else {
        return RGB(0,0,0);
    }
}



//-------------------------------- IMPRESION ---------------------------------//
