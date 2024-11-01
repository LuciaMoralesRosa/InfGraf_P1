#include "escena.hpp"

struct InterseccionPrimitiva {
    // True si existe intersección
    bool intersecta;
    // Vector de distancia a través del rayo hasta la intersección
    float distancia;
    // Vector de puntos  de intersección
    Punto3D puntoInterseccion;
    // Normal de la intersección (normalized)
    Direccion normal;
    // Puntero a la primitiva intersectada
    Primitiva* primitiva;
};

//------------------------------- PRIVADAS -----------------------------------//
InterseccionPrimitiva Escena::intersectarRayo(Rayo rayo){

    vector<Primitiva*> primitivasIntersectadas;
    vector<float> distanciasPrimitivas;
    vector<vector<Punto3D>> puntosInterseccion;
    returnInterseccionRayo ret;

    //Recorro todas las primitivas de mi escena y si intersecta con el rayo, la guardo
    for(const auto& pri : primitivas){  
        Interseccion inter = pri->interseccionRayo(rayo);
        if(inter.intersecta){
        // if(pri->tipo == "Esfera"){
        //     cout << "Ha intersectado la primitiva de tipo esfera" << endl;
        // }
            primitivasIntersectadas.push_back(pri);
            float min = calcularMIN(inter.distancia);
            distanciasPrimitivas.push_back(min);
            puntosInterseccion.push_back(inter.puntoInterseccion);
        }
    }

    //Tengo una lista de primitivas intersectadas por el rayo
    // Hay que ver que primitiva esta por delante
    if(primitivasIntersectadas.empty()){
        ret.primitiva = nullptr;
        ret.puntoInterseccion.push_back(Punto3D(0,0,0));
        return ret;
    }

    Primitiva* primitivaVisible;
    //Obtengo la distancia a la que se encuentra la primera primitiva (la visible)
    float minimaDistancia = calcularMIN(distanciasPrimitivas);

    // Recorro todo el vector de primitivas hasta que encuentro la que tiene el valor de distancia minimo
    for(int i = 0; i < primitivasIntersectadas.size(); i++){
        if(distanciasPrimitivas[i] == minimaDistancia){
            // Cuando la encuentro, la guardo
            ret.primitiva = primitivasIntersectadas[i];
            ret.puntoInterseccion = puntosInterseccion[i];
            break;
        }
    }
    // Devuleve la primitiva intersectada
    return ret;
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

/*
void Escena::lanzarRayosDesdeCamara(int rayosPorPixel){
    vector<Rayo> listaRayos;
    vector<Pixel> cuadriculaPixeles = camara.getCuadriculaPixeles();

    if(!cuadriculaPixeles.empty()){
        vector<Pixel> nuevaCuadricula;
        vector<float> red, green, blue;

        random_device rd;
        for(auto p : cuadriculaPixeles){
            for(int i = 0; i < rayosPorPixel; i++){
                mt19937 gen(rd());
                Punto3D puntoAleatorio = generarPuntoAleatorioEnPixel(gen, p);
                Rayo rayoAleatorio = Rayo(camara.getOrigen(), puntoAleatorio);
                
                intersectarRayo(rayoAleatorio);
                RGB colorObtenido;
                Direccion normalPrimitiva;
                if(inter.primitiva == nullptr){
                    colorObtenido = p.getColor();
                }
                else{
                    colorObtenido = inter.primitiva->getColor();
                    normalPrimitiva = inter.primitiva->getNormal(inter.puntoInterseccion[0]);
                }
                
                calcularLuzDirecta(rayoAleatorio, p, puntoAleatorio, inter.primitiva, normalPrimitiva);
                //Donde haya interseccion -> hay que buscar de donde viene la luz puntual
                //Calcular luz directa en el punto

                red.push_back(colorObtenido.getR());
                green.push_back(colorObtenido.getG());
                blue.push_back(colorObtenido.getB());
            }
            // Hacer media de cada componente y crear nuevo RGB
            RGB rgb(calcularMedia(red), calcularMedia(green), calcularMedia(blue));
            //cout << "color del pixel final: " << rgb << endl;
            p.setColor(rgb);
            nuevaCuadricula.push_back(p);
            red.clear();
            green.clear();
            blue.clear();
            //cout << endl;
        }
        cuadriculaPixeles = nuevaCuadricula;
    }
}
*/

void Escena::rayosDesdeCamara(int nrayos){
    vector<Rayo> listaRayos;
    vector<Pixel> cuadriculaPixeles = camara.getCuadriculaPixeles();

    if(cuadriculaPixeles.empty()){
        throw runtime_error("Error: La cuadrícula de píxeles está vacía.");
    }
    random_device rd;
    vector<Pixel> nuevaCuadricula;

    for(Pixel p : cuadriculaPixeles){ //Para cada pixel -> lanzar x rayos
        for(int i = 0; i < nrayos; i++) {  // generar x rayos a puntos aleatorios
            mt19937 gen(rd());
            Punto3D puntoAleatorio = generarPuntoAleatorioEnPixel(gen, p);
            Rayo rayoCamaraPixel = Rayo(camara.getOrigen(), puntoAleatorio);

            // Comprobar si el rayo intersecta con primitiva
            InterseccionPrimitiva interseccion = intersectarRayo(rayoCamaraPixel);


            // Para cada rayo que intersecta - Lanzar rayos de sombra
            // Es decir, trazar un rayo entre el punto de interseccion y cada
            // una de las luces puntuales y ver si hay alguna primitiva entre
            // ellos. Si lo hay -> el pixel esta en sombra, sino el pixel tiene color

            RGB contribucionLuz = estimacionSiguienteEvento(interseccion);
        }

    }



}


RGB Escena::estimacionSiguienteEvento(InterseccionPrimitiva interseccion){
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
                    BSDF bsdf = BSDF(inter.primitiva->getColor(), 1);
                    RGB evaluacionEnMaterial = bsdf.evaluacion(); 
                    float porPlano = abs(inter.normal.dot_product(rayoInterseccionLuz.getDireccion().normalize())) *
                                        abs(luzArea->getNormal().dot_product(rayoInterseccionLuz.getDireccion().normalize()*(-1)));
                    contribucionDeLuz = potInicialPorDistancia2 * evaluacionEnMaterial * porPlano;
                }
                else { // Si estamos evaluando una luz puntual
                    // Si metemos Efectos de Fresnel o texturas habra que cambiar esto:
                    BSDF bsdf = BSDF(inter.primitiva->getColor(), 1);
                    RGB evaluacionEnMaterial = bsdf.evaluacion(); 
                    float porPunto = abs(inter.normal.dot_product(rayoInterseccionLuz.getDireccion().normalize()));
                    contribucionDeLuz = potInicialPorDistancia2 * evaluacionEnMaterial;
                }

            }
            contribucion = contribucion + contribucionDeLuz;
        }
    }

}



//-------------------------------- IMPRESION ---------------------------------//
