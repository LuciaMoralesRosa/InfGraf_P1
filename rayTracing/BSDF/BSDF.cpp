#include "BSDF.hpp"

BSDF::BSDF(RGB _kd, RGB _ks, RGB _kt, RGB _ke) : kd(_kd), ks(_ks), kt(_kt), ke(_ke), indiceRefraccion(1) {
    // Calculo de probabilidades de cada componente:
    float prob_d = (kd.getB() + kd.getG() + kd.getR()) / 3.0f;
    float prob_s = (ks.getB() + ks.getG() + ks.getR()) / 3.0f;
    float prob_t = (kt.getB() + kt.getG() + kt.getR()) / 3.0f;  
    
    // Normalizacion de las probabilidades
    float total = (prob_d + prob_s + prob_t);
    pd = prob_d / total;
    ps = prob_s / total;
    pt = prob_t / total;
}

RGB BSDF::evaluacion(Direccion omega_o, Direccion normal){
    //cout << "Depurando: pd = " << pd << endl;
    //cout << "Depurando: ps = " << ps << endl;
    //cout << "Depurando: pt = " << pt << endl;

    if(!ke.esNegro()) {
        //cout << "Depurando: Es emisor" << endl;
        // Si es elemento emisor (es decir, una luz) -> terminara el camino
        return RGB_NULO;
    }

    // Decidir que tipo de material es:
    float aleatorio = generacionNumeroAleatorio();
    //cout << "Depurando: El numero aleatorio es: " << aleatorio << endl;

    // Evaluacion
    RGB color = RGB_NULO;
    if(aleatorio < pd){
        //cout << "Depurando: estoy en difuso" << endl;
        color = evaluacionDifusa() / pd;
    }
    else if(aleatorio < pd + ps) {
        // Especular reflectancia
        cout << "Depurando: estoy en especular " << endl;
        color = evaluacionEspecular(normal, omega_o) / ps; // Implementado
    }
    else if(aleatorio < pd + ps + pt) {
        cout << "Depurando: estoy en Refraccion " << endl;
        color = evaluacionRefraccion() / pt; // Implementado ??
    }
    return color;
}


tuple<Direccion, RGB> BSDF::muestreo(const Punto3D x, const Direccion omega_o, const Direccion normal){
    if(!ke.esNegro()) {
        // Si es elemento emisor (es decir, una luz) -> terminara el camino
        return tuple<Direccion, RGB>(DIRECCION_NULA, RGB_NULO);
    }

    // Decidir que tipo de material es:
    float aleatorio = generacionNumeroAleatorio();

    // Evaluacion
    RGB color;
    Direccion rebote;
    if(aleatorio < pd){
        // Si es difusa
        rebote = muestreoDifuso(); // Implementado
        color = evaluacionDifusa() / pd; // Implementado
    }
    else if(aleatorio < pd + ps) {
        // Especular reflectancia
        rebote = muestreoEspecular(normal, omega_o); // Implementado (faltaria fresnel)
        color = evaluacionEspecular(normal, omega_o) / ps; // Implementado
    }
    else if(aleatorio < pd + ps + pt) {
        rebote = muestreoRefraccion(normal, omega_o); // Implementado -> Ley de snell
        color = evaluacionRefraccion() / pt; // Implementado ??
    }
    else{
        // Ha caido en absorcion -> termina el recorrido
        tuple<Direccion, RGB> ret(DIRECCION_NULA, RGB_NULO);
        return ret;
    }
    return tuple<Direccion, RGB>(rebote, color);
}

Direccion BSDF::muestreoEspecular(Direccion normal, Direccion omega_o){
    if(indiceReflexion == 1) {
        //ley de reflexion perfecta
        return omega_o - (normal * (normal.dot_product(omega_o)) * 2);
    }
    else {
        // Leyes de fresnel para materiales dielectricos o metales
        return Direccion(0,0,0); // CAMBIAR MAS ADELANTE
    }
}

Direccion BSDF::muestreoRefraccion(Direccion omega_o, Direccion normal){
    Direccion Nrefr = normal;
    float NOmega = Nrefr.dot_product(omega_o);
    float cos_i;

    if(NOmega < -1){
        cos_i = -1;
    } 
    else if(1 < NOmega){
        cos_i = 1;
    }   
    else {
        cos_i = NOmega;
    }

    float n1 = indiceRefraccionMedio1; // Indice de refraccion del medio 1
    float n2 = indiceRefraccion; // Indice de refraccion del medio 2

    if(cos_i < 0) { // El rayo esta entrando al medio
        cos_i = -cos_i;
    }
    else { // El rayo sale del medio
        Nrefr = normal * -1;
        swap(n1, n2);
    }
    float relIndices = n1 / n2; // Relacion entre los indices

    float k = 1 - relIndices * relIndices * (1.0f - cos_i * cos_i);
    if(k < 0){
        return 0;
    }
    else {
        return omega_o * relIndices + Nrefr*(relIndices * cos_i - sqrtf(k));
    }
}  

Direccion BSDF::muestreoDifuso(){
    // Uso del algoritmo Angulo solido uniforme.

    // Calculo del angulo azimutal aleatorio entre 0 y 2pi
    float phi = 2.0f * M_PI * generacionNumeroAleatorio();

    // Altura z aleatoria entre 0 y 1
    float z = generacionNumeroAleatorio();

    // Radio en el plano XY
    float r = sqrt(1.0f - (z * z));

    // Coordenadas cartesianas
    float x = r * cos(phi);
    float y = r* sin(phi);


    //// Intento 2
    //float theta = acos(sqrt(1.0f, ))
    return Direccion(x, y, z);
}

RGB BSDF::evaluacionDifusa(){
    // Lambert
    return RGB(kd.getR() / M_PI, kd.getG() / M_PI, kd.getB() / M_PI);
}

RGB BSDF::evaluacionEspecular(Direccion normal, Direccion omega_o) {
    // Con la funcion de evaluacion de fresnel -> con simplificacion  Fresnel-Schlick
    float cosTheta = normal.dot_product(omega_o);
    float F = 0.04 + (1 - 0.04) * pow(1 - cosTheta, 5);
    return kd * F; // No estoy segura de si kd o ks (kd supuestamente es el color)
}

RGB BSDF::evaluacionRefraccion(){
    return kt; // Atenua el color por el indice refractante    
}

//Getters y setters:
RGB BSDF::getKd() const {
    return kd;
}

RGB BSDF::getKs() const {
    return ks;
}

RGB BSDF::getKt() const {
    return kt;
}







//Funciones deprecated ---------------------------------------------------------

RGB BSDF::evaluacionBRDF(const Punto3D x, const Direccion omega_i, const Direccion omega_o, const Direccion normal){    
    float cosTheta = max(0.0f, normal.dot_product(omega_i.normalize())); 
    //return kd * ((1.0f / M_PI) * cosTheta); // (1/π) para la BRDF difusa
    //cout << "Depurando en EvaluacionBRDF kd:" << kd << endl;
    //cout << "Depurando en EvaluacionBRDF operacion: " << kd * ((1.0f / M_PI)) << endl;

    return kd * ((1.0f / M_PI));
}

/*
tuple<Direccion, RGB> BSDF::muestreo(const Punto3D x, const Direccion omega_o, const Direccion normal) {
    // Muestreamos una dirección basada en la refracción
    Direccion direccionRefraccion = evaluacionRefraccion(x, omega_o, normal);

    // Calculamos la contribución de la luz en la dirección muestreada
    RGB contribucion = evaluacionBRDF(x, direccionRefraccion, omega_o, normal);
    // Retornamos la dirección y la contribución calculada
    return make_tuple(direccionRefraccion, contribucion);
}
*/

/*
RGB BSDF::operator*(const BSDF& otro) const {
    return RGB(RGB(kd.getR()*otro.getValor().getR(),
                kd.getG()*otro.getValor().getG(),
                kd.getB()*otro.getValor().getB()));
}

RGB BSDF::operator*(const RGB& otro) const {
    return RGB(kd.getR()*otro.getR(),
               kd.getG()*otro.getG(),
               kd.getB()*otro.getB());
}
*/
