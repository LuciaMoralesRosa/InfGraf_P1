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

/// @brief Intersecta un rayo con todas las primitivas
/// @param rayo 
/// @return devuleve la Interseccion mas cercana (la importante)
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

/// @brief Calcula unicamente la luz directa de la escena
/// @param colorPixel 
/// @param rayo 
/// @return devuelve el color calculado con luz directa para el pixel
RGB EscenaRayTracing::intersectarRayo(RGB colorPixel, Rayo rayo) {    
    Interseccion inter = intersectar(rayo);
    RGB colorObtenido;

    if(inter.intersecta) {
        return siguienteEventoEstimado(rayo.getDireccion(), inter);
    }
    else {
        return RGB(0,0,0);
    }
    return colorPixel;
}


/// @brief Luz directa al punto
/// @param inter Intereccion a evaluar
/// @return devuelve el color de la primitiva si 
RGB EscenaRayTracing::siguienteEventoEstimado(Direccion dir, Interseccion inter) {
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
        if(distanciaLuz < 0.5) {
            //cout << "Depurando: Es menor a 0-001" << endl;
        }
        Interseccion interSombra = intersectar(rayoSombra);
        if(interSombra.intersecta) {
            if(interSombra.distancia < distanciaLuz){
                enSombra = true;
            }
        }
        if(!enSombra) {
            RGB potenciaLuz = luces[l]->getPotencia();
            Direccion luzPunto = (centroLuz-inter.puntoInterseccion).normalize();
            RGB potResultante = potenciaLuz / powf(distanciaLuz, 2.0f);
            //cout << "Depurando: Potencia resultante de la luz = " << potResultante << endl;
            float coseno = inter.normal.dot_product(luzPunto / luzPunto.modulus());
            //cout << "Depurando: Coseno = " << coseno << endl;
            BSDF bsdf(inter.colorPrimitiva);
            RGB fr = bsdf.evaluacion(luzPunto.normalize(), inter.normal.normalize());
            //cout << "Depurando: fr = " << fr << endl;
            RGB colorFinal = potResultante * fr * abs(coseno); 
            return colorFinal;
        }
        else {
            return RGB(0,0,0);
        }
    }
    cout << "Depurando: Se esta devolviendo el color de la primitiva" << endl;
    return inter.colorPrimitiva;
}


/*
RGB EscenaRayTracing::pathTracer(Rayo rayoEntrada, int actual, int maxRebotes) {
    if(actual == maxRebotes) {
        return RGB_NULO; // Terminacion
    }

    Interseccion interseccion = intersectar(rayoEntrada);
    if(!interseccion.intersecta){
        return RGB_NULO; // No intersecta con nada -> termino
    }

    RGB iluminacionDirecta = siguienteEventoEstimado(rayoEntrada.getDireccion(), interseccion);
    
    BSDF valoresPrimitiva(interseccion.colorPrimitiva);
    tuple<Direccion, RGB> tupla = valoresPrimitiva.muestreo(interseccion.puntoInterseccion, rayoEntrada.getDireccion(), interseccion.normal);
    Direccion dirRayoReflejado = get<0>(tupla);
    
    RGB fr = get<1>(tupla);
    if(fr.esNulo()) {
        return RGB_NULO; // Si no hay contribucion directa -> termino (ej Luz)
    }

    //cout << "Depurando: direccion del rayo = " << dirRayoReflejado << endl;
    
    if (dirRayoReflejado.esNula()){
        return iluminacionDirecta; // Si no sale rayo reflejado -> termino (ej Abs)
    }
    Rayo rayoSalida(interseccion.puntoInterseccion, dirRayoReflejado);
    RGB resPathTracer = pathTracer(rayoSalida, actual+1, maxRebotes);
    //cout << "Depurando: valor del pathTracer = " << resPathTracer << endl;
    
    if(resPathTracer.esNulo()) {
        return iluminacionDirecta;
    }

    //RGB iluminacionIndirecta = fr + resPathTracer;

//    RGB iluminacionIndirecta = iluminacionDirecta + resPathTracer;
    if(iluminacionIndirecta.esNulo()){
        return iluminacionDirecta;
    }

    if(resPathTracer.esNulo()){
        return iluminacionDirecta;
    }
 
    return iluminacionDirecta + iluminacionIndirecta;
    return resPathTracer + iluminacionDirecta;
   //return iluminacionDirecta;
}
*/

RGB EscenaRayTracing::pathTracer(Rayo rayoEntrada, int actual, int maxRebotes) {
    if(actual == maxRebotes) {
        return RGB_NULO; // Terminacion
    }

    Interseccion interseccion = intersectar(rayoEntrada);
    if(!interseccion.intersecta){
        return RGB_NULO; // No intersecta con nada -> termino
    }

    RGB iluminacionDirecta = siguienteEventoEstimado(rayoEntrada.getDireccion(), interseccion);
    
    BSDF valoresPrimitiva(interseccion.colorPrimitiva);
    tuple<Direccion, RGB> tupla = valoresPrimitiva.muestreo(interseccion.puntoInterseccion, rayoEntrada.getDireccion(), interseccion.normal.normalize());
    Direccion dirRayoReflejado = -get<0>(tupla).normalize();
    
    RGB fr = get<1>(tupla);
    if(fr.esNulo()) {
        return RGB_NULO; // Si no hay contribucion directa -> termino (ej Luz)
    }
    
    RGB li = pathTracer(Rayo(interseccion.puntoInterseccion, dirRayoReflejado), actual+1, maxRebotes);
    if(li.esNulo()) {
        return iluminacionDirecta;
    }
    float coseno = interseccion.normal.normalize().dot_product(dirRayoReflejado.normalize());
    RGB luzIndirecta = li * fr * coseno * 2 * M_PI;

    return luzIndirecta + iluminacionDirecta;
}

/*
RGB EscenaRayTracing::pathTracer(Rayo rayoEntrada, int actual, int maxRebotes) {
    if(actual == maxRebotes) {
        return RGB_NULO; // Terminacion
    }

    Interseccion interseccion = intersectar(rayoEntrada);
    if(!interseccion.intersecta){
        return RGB_NULO; // se han cumplido los rebores -> termino
    }

    RGB contribucion = siguienteEventoEstimado(rayoEntrada.getDireccion(), interseccion);
    BSDF bf(interseccion.colorPrimitiva);
    tuple<Direccion, RGB> tupla = bf.muestreo(interseccion.puntoInterseccion, rayoEntrada.getDireccion(), interseccion.normal);
    Direccion dirRayo = get<0>(tupla);
    RGB color = get<1>(tupla);

    if(color.esNegro() || color.esNulo()) {
        return RGB_NULO;
    }

    Rayo rayoSalida(interseccion.puntoInterseccion, dirRayo);
    RGB path = pathTracer(rayoSalida, actual+1, maxRebotes);
    if(path.esNulo()){
        return contribucion;
    }
    cout << "Depurando: estoy devolviendo contribucion" << endl;
    contribucion = contribucion + color*path;
    return contribucion;
}
*/

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

                // Pathtracer
                RGB colorObtenido = pathTracer(rayoAleatorio, 0, maxRebotes);
                if(colorObtenido.esNulo()) {
                    colorObtenido = RGB(0,0,0);
                }

                // Solo luz directa
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

