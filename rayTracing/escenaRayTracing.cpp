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

/// @brief Intersecta un rayo con todas las primitivas (RAY TRACER)
/// @param rayo 
/// @return devuleve la interseccion mas cercana (la importante)
Interseccion EscenaRayTracing::intersectar(Rayo rayo){
    Interseccion inter;
    inter.intersecta = false;
    float menorDistancia = MAXIMA_DISTANCIA;
    
    for(int i = 0; i < primitivas.size(); i++){
        Interseccion interseccion = primitivas[i]->interseccionRayo(rayo);
        if(interseccion.intersecta) {
            if(interseccion.distancia < menorDistancia){
                inter.intersecta = true;
                menorDistancia = interseccion.distancia;
                inter.distancia = menorDistancia;
                inter.puntoInterseccion = Punto3D(rayo.getOrigen(), rayo.getDireccion(), menorDistancia);
                inter.normal = interseccion.normal;
                inter.colorPrimitiva = interseccion.colorPrimitiva;
            }
        }
    }
    return inter;
}

 // intersectarRayoIMPL (PathTracer version inicial)
// Interseccion rayo + rayos de sombra
RGB EscenaRayTracing::intersectarRayo(RGB colorPixel, Rayo rayo) {    
    Interseccion inter = intersectar(rayo);

    RGB colorObtenido;

    if(inter.intersecta) {
        //return intento3(inter, inter.puntoInterseccion);
        //siguienteEventoEstimado(inter);
        colorObtenido = lanzarRayosSombra(inter);
        return colorObtenido;
    }
    else {
        return RGB(0,0,0);
    }
    return colorPixel;
}


/// @brief Lanza rayos de sombra (NextEventEstimation version inicial)
/// @param inter Intereccion a evaluar
/// @return devuelve el color de la primitiva si 
RGB EscenaRayTracing::lanzarRayosSombra(Interseccion inter) {
    const float DESPLAZAMIENTO = 0.000001F;

    for(int l = 0; l < luces.size(); l++){
        Punto3D centroLuz = luces[l]->getCentro();
        Direccion normalDesplazada = inter.normal.normalize()*DESPLAZAMIENTO;
        Punto3D origenRayoSombra = sumaPuntoDireccion(inter.puntoInterseccion, normalDesplazada);
        Rayo rayoSombra = Rayo(origenRayoSombra, (centroLuz - origenRayoSombra).normalize());

        bool enSombra;

        if(rayoSombra.getDireccion().dot_product(inter.normal) < 0){
            enSombra = true;
        }

        float distanciaLuz = (centroLuz - inter.puntoInterseccion).modulus();
        Interseccion interSombra = intersectar(rayoSombra);
        if(interSombra.intersecta) {
            if(interSombra.distancia < distanciaLuz){
                enSombra = true;
            }
        }
        if(!enSombra) {
            
            Direccion luzPunto = (centroLuz-inter.puntoInterseccion);
            RGB potResultante = luces[l]->getPotencia() / pow(distanciaLuz,2);
            float coseno = inter.normal.dot_product(luzPunto / luzPunto.modulus());
            BSDF bsdf(inter.colorPrimitiva);
            RGB fr = bsdf.evaluacion(luzPunto, inter.normal);

            RGB colorFinal = potResultante * fr * abs(coseno); 
            return colorFinal;
            //return inter.colorPrimitiva;
        }
        else {
            return RGB(0,0,0);
        }
    }
}


RGB EscenaRayTracing::pathTracer(Rayo rayoEntrada, int actual, int maxRebotes) {
    if(actual == maxRebotes) {
        return RGB_NULO;
    }

    Interseccion interseccion = intersectar(rayoEntrada);
    if(!interseccion.intersecta){
        return RGB_NULO; // se han cumplido los rebores -> termino
    }

    RGB iluminacionDirecta = siguienteEventoEstimado(rayoEntrada.getDireccion(), interseccion);
    BSDF valoresPrimitiva(interseccion.colorPrimitiva);
    tuple<Direccion, RGB> tupla = valoresPrimitiva.muestreo(interseccion.puntoInterseccion, rayoEntrada.getDireccion(), interseccion.normal);
    Direccion dirRayoReflejado = get<0>(tupla);
    RGB fr = get<1>(tupla);
    if(fr.esNulo()) {
        return RGB_NULO; // Si no hay contribucion directa -> termino (ej Luz)
    }
    if (dirRayoReflejado.esNula()){
        return iluminacionDirecta; // Si no sale rayo reflejado -> termino (ej Abs)
    }
    Rayo rayoSalida(interseccion.puntoInterseccion, dirRayoReflejado);
    RGB iluminacionIndirecta = fr + pathTracer(rayoSalida, actual+1, maxRebotes);
    if(iluminacionIndirecta.esNulo()){
        return iluminacionDirecta;
    }

    return iluminacionDirecta + iluminacionIndirecta;
}

RGB EscenaRayTracing::siguienteEventoEstimado(Direccion dirRayo, Interseccion interseccion) {
    return lanzarRayosSombra(interseccion);
}

//------------------------------- PUBLICAS -----------------------------------//

void EscenaRayTracing::lanzarRayos(int rayosPorPixel, int maxRebotes) {
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

                RGB colorObtenido = pathTracer(rayoAleatorio, 0, maxRebotes);
                if(colorObtenido.esNulo()) {
                    colorObtenido = RGB(0,0,0);
                }

                //RGB colorObtenido = intersectarRayo(p.getColor(), rayoAleatorio);
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

