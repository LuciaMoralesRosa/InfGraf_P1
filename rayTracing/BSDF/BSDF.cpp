#include "BSDF.hpp"

RGB BSDF::getValor() const {
    return valor;
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
    return RGB(coeficienteDifusion / M_PI, coeficienteDifusion / M_PI, coeficienteDifusion / M_PI);
}

RGB BSDF::evaluacion(Punto3D x, Direccion omega_i, Direccion omega_o, Direccion normal, const float u, const float v){
    float r, g, b;
    return RGB(coeficienteDifusion / M_PI, coeficienteDifusion / M_PI, coeficienteDifusion / M_PI);
}


RGB BSDF::operator*(const BSDF& otro) const {
    return RGB(RGB(valor.getR()*otro.getValor().getR(),
                valor.getG()*otro.getValor().getG(),
                valor.getB()*otro.getValor().getB()));
}

RGB BSDF::operator*(const RGB& otro) const {
    return RGB(valor.getR()*otro.getR(),
               valor.getG()*otro.getG(),
               valor.getB()*otro.getB());
}
