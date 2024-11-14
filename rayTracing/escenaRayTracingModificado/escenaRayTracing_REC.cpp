#include "EscenaRayTracing_REC.hpp"

//------------------------------- PRIVADAS -----------------------------------//
Punto3D EscenaRayTracingREC::generarPuntoAleatorioEnPixel(mt19937 gen, Pixel pixel){
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

Punto3D EscenaRayTracingREC::puntoInterseccionDadaDistancia(Interseccion i, float d){
    for(int j = 0; j < i.puntoInterseccion.size(); j++){
        if(i.distancia[j] == d) {
            return i.puntoInterseccion[j];
        }
    }
    return -1;
}

Direccion EscenaRayTracingREC::normalInterseccionDadaDistancia(Interseccion i, float d){
    for(int j = 0; j < i.normal.size(); j++){
        if(i.distancia[j] == d) {
            return i.normal[j];
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
// Interseccion rayo + rayos de sombra
RGB EscenaRayTracingREC::intersectarRayo(RGB colorPixel, Rayo rayo) {
    const float MAXIMA_DISTANCIA = 10000000.0F;
    const float DESPLAZAMIENTO = 0.000001F;

    vector<Interseccion> vectorIntersecciones;
    float menorDistancia = MAXIMA_DISTANCIA;
    int posInterseccion;
    Punto3D puntoMenorDistancia;
    Direccion normalMenorDistancia;
    RGB colorPrimitiva;
    Primitiva* primitivaEvaluada;

    // RayTracing -> Funciona bien
    for(int i = 0; i < primitivas.size(); i++){
        Interseccion interseccionPrimitiva = primitivas[i]->interseccionRayo(rayo);
        if(interseccionPrimitiva.intersecta) {
            vectorIntersecciones.push_back(interseccionPrimitiva);
            if(calcularMIN(interseccionPrimitiva.distancia) < menorDistancia){
                menorDistancia = calcularMIN(interseccionPrimitiva.distancia);
                puntoMenorDistancia = puntoInterseccionDadaDistancia(interseccionPrimitiva, menorDistancia);
                normalMenorDistancia = normalInterseccionDadaDistancia(interseccionPrimitiva, menorDistancia);
                posInterseccion = vectorIntersecciones.size()-1;
                colorPrimitiva = interseccionPrimitiva.colorPrimitiva;
                primitivaEvaluada = primitivas[i];
            }
        }
    }
}
*/


InterseccionConcreta EscenaRayTracingREC::intersectarRayo(Rayo rayo) {
    const float MAXIMA_DISTANCIA = 10000000.0F;

    vector<Interseccion> vectorIntersecciones;
    float menorDistancia = MAXIMA_DISTANCIA;
    int posInterseccion;
    Punto3D puntoMenorDistancia;
    Direccion normalMenorDistancia;
    RGB colorPrimitiva;
    Primitiva* primitivaEvaluada;
    bool intersecta;

    // RayTracing -> Funciona bien
    for(int i = 0; i < primitivas.size(); i++){
        Interseccion interseccionPrimitiva = primitivas[i]->interseccionRayo(rayo);
        if(interseccionPrimitiva.intersecta) {
            vectorIntersecciones.push_back(interseccionPrimitiva);
            if(calcularMIN(interseccionPrimitiva.distancia) < menorDistancia){
                intersecta = true;
                menorDistancia = calcularMIN(interseccionPrimitiva.distancia);
                puntoMenorDistancia = puntoInterseccionDadaDistancia(interseccionPrimitiva, menorDistancia);
                normalMenorDistancia = normalInterseccionDadaDistancia(interseccionPrimitiva, menorDistancia);
                posInterseccion = vectorIntersecciones.size()-1;
                colorPrimitiva = interseccionPrimitiva.colorPrimitiva;
                primitivaEvaluada = primitivas[i];
            }
        }
    }
    InterseccionConcreta ret;
    ret.intersecta = intersecta;
    if(intersecta){
        ret.colorPrimitiva = colorPrimitiva;
        ret.distancia = menorDistancia;
        ret.normal = normalMenorDistancia;
        ret.puntoInterseccion = puntoMenorDistancia;
    }
    else {
        ret.colorPrimitiva = RGB_NULO;
        ret.distancia = -1;
        ret.normal = DIRECCION_NULA;
        ret.puntoInterseccion = Punto3D();
    }
    return ret;
}


bool EscenaRayTracingREC::puntoEnSegmento(Punto3D A, Punto3D B, Punto3D X) {
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

// Lanzar rayos con Recursividdad
void EscenaRayTracingREC::lanzarRayos(int rayosPorPixel, int nRebotes) {
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
                //RGB colorObtenido = intersectarRayo(p.getColor(), rayoAleatorio);
                RGB colorObtenido = trazadoCaminos(rayoAleatorio, 0, nRebotes);
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

RGB EscenaRayTracingREC::trazadoCaminos(Rayo rayoEntrada, int actual, int nRebotes) {
    if(actual == nRebotes) {
        return RGB_NULO;
    }

    tuple<Direccion, RGB> see;
    RGB colorSee;
    Direccion dirSee_wi;
    InterseccionConcreta interseccion = intersectarRayo(rayoEntrada);
    if(interseccion.intersecta) {
        see = siguienteEventoEstimado();
        colorSee = get<1>(see);
        dirSee_wi = get<0>(see);
    }
    else{
        return RGB_NULO;
    }

    RGB contribucionPT = trazadoCaminos(Rayo(interseccion.puntoInterseccion, dirSee_wi), actual+1, nRebotes);
    if(contribucionPT.esNulo()){
        return colorSee;
    }
    else {
        return colorSee + contribucionPT;
    }

}

tuple<Direccion, RGB> siguienteEventoEstimado(){
    // Toda la parte de calcular la contribucion de color
    // Ver si esta en sombra y calcular la luz y direccion de rebote con muestreo(...)
}

/* Lanzar rayos original
void EscenaRayTracingREC::lanzarRayos(int rayosPorPixel) {
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
*/

ImagenPPM EscenaRayTracingREC::crearImagenPPM(){
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




/*
distanciaMinima = 10000000.0F
Desplazamiento = 0.00001F
for(primitivas.size){
    if(pri->interseccion(rayoCamara).intersecta){
        vectorIntersecciones.push_back(interseccion)
        if(interseccion.distancia < distanciaMinima) {
            distanciaMinima = interseccion.distancia
            posicionMinima = vectorIntersecciones.size()-1
        }
    }
}

if(!vectorIntersecciones.empty()) {
    for(luces) {
        rayoSombra = Rayo(vectorIntersecciones[posicionMinima].punto + (vectorIntersecciones[posMinima].normal.normalizar()*DESPLAZAMIENTO),
                          luces[l].centro - (vectorIntersecciones[posMin].punto + (vectorIntersecciones[posMinima].normal.normalizar()* Desplazamiento)))
        distanciaLuz = (luces[l].centro - vectorIntersecciones[posMin].punto).modulo()

        bool sombra = false;

        if(rayoSombra.direccion*vectorIntersecciones[posMin].normal < 0) {
            sombra = true
        }

        for(m < primitivas.size && !sombra; m++){
            if(primitivas[m]->interseccion(rayoSombra, interseccionConRayo)) {
                if(interseccionConRayo.distancia < distanciaLuz) {
                    sombra = true;
                }    
            }
        }
        if(!sombra) {
            mediaColor[0] += (luces[l]->potencia[0]/pow(distanciaLuz, 2)) * (vectorIntersecciones[posMinima].color[0]/PI) * abs(vectorIntersecciones[posMin].normal*((luces[l]->centro-vectorIntersecciones[posMin].punto)/distanciaLuz));
        }
    }
}

//calcular media de los colores / nRayos
Comprobar que ninguno supera el maximo de la imagen

*/
