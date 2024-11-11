#include "escenaRayTracing.hpp"

//------------------------------- PRIVADAS -----------------------------------//
Punto3D EscenaRayTracing::generarPuntoAleatorioEnPixel(mt19937 gen, Pixel pixel){
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

Punto3D EscenaRayTracing::puntoInterseccionDadaDistancia(Interseccion i, float d){
    for(int j = 0; j < i.puntoInterseccion.size(); j++){
        if(i.distancia[j] == d) {
            return i.puntoInterseccion[j];
        }
    }
    return -1;
}

bool puntoSobreRayo(const Punto3D& O, const Punto3D& L, const Punto3D& P) {
    // Vectores OP y OL
    Direccion OP = P - O;
    Direccion OL = L - O;

    Direccion productoX = OP.vector_product(OL);
    if(productoX.modulus() != 0) {
        return false; // No son paralelos
    }

    Direccion OP_unitario = Direccion(OP.getx()/OP.modulus(), OP.gety()/OP.modulus(), OP.getz()/OP.modulus());
    Direccion OL_unitario = Direccion(OL.getx()/OL.modulus(), OL.gety()/OL.modulus(), OL.getz()/OL.modulus());

    if(OP_unitario != OL_unitario){
        return false;
    }

    float distanciaOP = OP.modulus();
    float distanciaOL = OL.modulus();

    if (distanciaOP <= distanciaOL) {
        return true; // P está sobre el rayo
    }

    return false; // P está fuera del rayo (más allá de L)
}

/*
bool EscenaRayTracing::esRayoDeSombra(Punto3D puntoInterseccion, Primitiva* p) {
    for (const auto& l : luces) {
        cout << "Depurando: Para la primitiva de color: " << p->getColor()<< endl;
        Rayo rayoDeSombra = Rayo(puntoInterseccion, l->getCentro());
        float dPuntoLuz = (puntoInterseccion - l->getCentro()).modulus();
        bool haIntersectado = false;

        // Comprobamos si alguna primitiva bloquea el rayo hacia esta luz
        int Depurando = 0;
        for (const auto& pri : primitivas) {
            Interseccion inter = pri->interseccionRayo(rayoDeSombra);
            if (inter.intersecta){
                for(int i = 0; i < inter.puntoInterseccion.size(); i++){
                    if(puntoInterseccion != i){
                        if(puntoSobreRayo(puntoInterseccion, l->getCentro(), inter.puntoInterseccion[i])) {
                            if(Depurando < 10){
                                cout << "Depurando: Punto de choque con primitiva de color: " << inter.colorPrimitiva << endl;
                            }
                            Depurando++;
                            // Si algun punto de interseccion esta sobre el rayo
                            // entre el origen del rayo de sombra y la luz ->
                            // esta a la sombra
                            haIntersectado = true;
                            break; // Salimos del bucle de primitivas para esta luz
                        }
                        else {
                            //cout << "Depurando - No ha intersectado con ninguna prim -> punto de luz" << endl;
                        }
                    }
                }
            }
        }

        if (!haIntersectado) {
            //cout << "Depurando - El punto esta en luz directa" << endl;
            return false; // El punto está en luz directa de al menos una luz
        }
    }
    // Si todas las luces están bloqueadas, el punto está en sombra
    return true;
}
*/

/*
RGB EscenaRayTracing::esRayoDeSombra(Punto3D puntoInterseccion, Interseccion interseccion){
    for(auto l : luces){
        Direccion direccionRayo = l->getCentro() - puntoInterseccion;
        Rayo rayo = Rayo(puntoInterseccion, direccionRayo.normalize());
        Interseccion inter;

        inter.intersecta = false;
        float distancia = rayo.getDireccion().modulus();

        for(auto p : primitivas) {
            Interseccion i = p->interseccionRayo(rayo);
            if(i.intersecta){
                for(int j = 0; j < i.distancia.size(); j++){
                    if(i.distancia[j] < distancia && i.distancia[j] > 0){
                        // El punto esta en luz
                        //RGB colorEnLuz = l->getPotencia() / (rayo.getDireccion().dot_product(rayo.getDireccion()));
                        //float colorGeometria = abs(interseccion.normal.dot_product(rayo.getDireccion().normalize()));
                        //return colorEnLuz * colorGeometria;
                        return interseccion.colorPrimitiva;
                    }
                }
            }
        }
    }
    return RGB(0,0,0);
}
*/

RGB EscenaRayTracing::intersectarRayo(RGB colorPixel, Rayo rayo){
    
    vector<Interseccion> interseccionesPrimitivas;
    vector<float> vectorDistancias;
    vector<Punto3D> vectorPuntosIntersectados;
    vector<Primitiva*> primitivasIntersectadas;

    for(const auto& pri : primitivas){
        Interseccion i = pri->interseccionRayo(rayo);
        if(i.intersecta){
            interseccionesPrimitivas.push_back(i);
            float minDistancia = calcularMIN(i.distancia);
            vectorDistancias.push_back(minDistancia);
            Punto3D p = puntoInterseccionDadaDistancia(i, minDistancia);
            vectorPuntosIntersectados.push_back(p);
            primitivasIntersectadas.push_back(pri);
        }
    }

    if(interseccionesPrimitivas.empty()){
        return colorPixel;
    }

    Primitiva* primitivaVisible;
    Interseccion interseccion;
    Punto3D puntoInterseccion;
    float menorDistancia = calcularMIN(vectorDistancias);
    
    for(int i = 0; i < interseccionesPrimitivas.size(); i++){
        for(int j = 0; j < interseccionesPrimitivas[i].distancia.size(); j++){
            if(interseccionesPrimitivas[i].distancia[j] == menorDistancia) {
                primitivaVisible = primitivasIntersectadas[i];
                interseccion = interseccionesPrimitivas[i];
                puntoInterseccion = vectorPuntosIntersectados[j];
            }
        }
    }

    // ShadowRays
    bool puntoEnSombra = false;

    if(interseccion.intersecta){
        for(auto l : luces) {
            if(l->getTipo() == 0) { // Es luz puntual
                // Crear rayo desde la interseccion y la luz
                Rayo rayoSombra = Rayo(l->getCentro(), puntoInterseccion);

                // Ver si el rayo intersecta con alguna primitiva
                // ENTRE EL ORIGEN Y LA LUZ !!!
                for(auto p : primitivas) {
                    Interseccion interSombra = p->interseccionRayo(rayoSombra);

                    if(interSombra.intersecta) {
                        // El rayo ha intersectado con una primitiva

                        // Hay que comprobar que el punto causante de la
                        // interseccion no soy yo, ie, el punto a evaluar si esta o no en sombra

                        for(int i = 0; i < interSombra.puntoInterseccion.size(); i++){
                            // Me aseguro de que no soy yo
                            if(interSombra.puntoInterseccion[i] != puntoInterseccion){
                                // Si no soy yo -> entonces es posible que me este haciendo sombra.
                                // Debo asegurarme de que esta entre la luz y yo

                                if(puntoEnSegmento(puntoInterseccion, l->getCentro(), interSombra.puntoInterseccion[i])){
                                    // El punto esta en el segmento -> hace sombra
                                    puntoEnSombra = true;

                                    // Me guardo otros datos de interes
                                    
                                }
                            }
                        }
                    }
                }
            }

        }
        if(puntoEnSombra){
            return RGB(0,0,0);
        }
        else {
            return interseccion.colorPrimitiva;
        }
    }
    return colorPixel;
}


bool EscenaRayTracing::puntoEnSegmento(Punto3D A, Punto3D B, Punto3D X) {
    float xxax = X.getx() - A.getx();
    float bxax = B.getx() - A.getx();
    float valor1 = xxax/bxax;
    float xyay = X.gety() - A.gety();
    float byay = B.gety() - A.gety();
    float valor2 = xyay/byay;
    float xzaz = X.getz() - A.getz();
    float bzaz = B.getz() - A.getz();
    float valor3 = xzaz/bzaz;

    bool estaEnRecta = (valor1 == valor2) && (valor2 == valor3);
    bool estaEnSegmento = (0 < valor1) && (valor1 < 1);

    if(estaEnRecta && estaEnSegmento){
        return true;
    }

    return false;
}

//------------------------------- PUBLICAS -----------------------------------//

void EscenaRayTracing::lanzarRayos(int rayosPorPixel) {
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
                RGB colorObtenido = intersectarRayo(p.getColor(), rayoAleatorio);
                red.push_back(colorObtenido.getR());
                green.push_back(colorObtenido.getG());
                blue.push_back(colorObtenido.getB());
            }
            // Hacer media de cada componente y crear nuevo RGB
            RGB rgb(calcularMedia(red), calcularMedia(green), calcularMedia(blue));
            p.setColor(rgb);
            nuevaCuadricula.push_back(p);
            red.clear();
            green.clear();
            blue.clear();
        }
        cuadriculaPixeles = nuevaCuadricula;
        camara.setCuadricutaPixeles(cuadriculaPixeles);
    }
}

ImagenPPM EscenaRayTracing::crearImagenPPM(){
    float valorMax = 0;
    float v;
    vector<RGB> pixeles;
    vector<Pixel> arrayPixeles = camara.getCuadriculaPixeles();
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