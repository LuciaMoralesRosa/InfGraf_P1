#include "BSDF.hpp"

RGB BSDF::getValor() const {
    return kd;
}

// Ley de Snell
Direccion BSDF::evaluacionRefraccion(Punto3D x, Direccion omega_o, Direccion normal){
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

    float n1 = 1; // Indice de refraccion del medio 1
    float n2 = indiceRefraccion; // Indice de refraccion del medio 2

    if(cos_i < 0) { // El rayo esta entrando al medio
        cos_i = -cos_i;
    }
    else { // El rayo sale del medio
        Nrefr = normal * -1;
        swap(n1, n2);
    }
    float relIndices = n1 / n2; // Relacion entre los indices

    float k = 1 - relIndices * relIndices * (1- cos_i * cos_i);
    if(k < 0){
        return 0;
    }
    else {
        return omega_o * relIndices + Nrefr*(relIndices * cos_i - sqrtf(k));
    }
}    

RGB BSDF::evaluacion(){
    return RGB(kd.getR() / M_PI, kd.getG() / M_PI, kd.getB() / M_PI);
}

RGB BSDF::evaluacion(Punto3D x, Direccion omega_i, Direccion omega_o, Direccion normal, const float u, const float v){
    float r, g, b;
    return RGB(kd.getR() / M_PI, kd.getG() / M_PI, kd.getB() / M_PI);
}

RGB BSDF::evaluacionBRDF(const Punto3D x, const Direccion omega_i, const Direccion omega_o, const Direccion normal){    
    float cosTheta = max(0.0f, normal.dot_product(omega_i.normalize())); 
    //return kd * ((1.0f / M_PI) * cosTheta); // (1/π) para la BRDF difusa
    //cout << "Depurando en EvaluacionBRDF kd:" << kd << endl;
    //cout << "Depurando en EvaluacionBRDF operacion: " << kd * ((1.0f / M_PI)) << endl;

    return kd * ((1.0f / M_PI));
}

tuple<Direccion, RGB> BSDF::muestreo(const Punto3D x, const Direccion omega_o, const Direccion normal) {
    // Muestreamos una dirección basada en la refracción
    Direccion direccionRefraccion = evaluacionRefraccion(x, omega_o, normal);

    // Calculamos la contribución de la luz en la dirección muestreada
    RGB contribucion = evaluacionBRDF(x, direccionRefraccion, omega_o, normal);
    // Retornamos la dirección y la contribución calculada
    return {direccionRefraccion, contribucion};
}

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
