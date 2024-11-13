#include "plano.hpp"


/*Plano::Plano(Punto3D _p, Direccion _n, RGB _color) : Primitiva(_color, "Plano") {
    punto = _p;
    normal = _n.normalize();
}*/

Plano::Plano(Direccion n, float dist, Textura _textura) : Primitiva(_textura, "Plano"){
    normal = n;
    distancia = dist;
}


bool Plano::interseccionRayo(Rayo &rayo) const {

    Punto3D oRayo = rayo.getOrigen();
    Direccion dRayo = rayo.getDireccion().normalize();


    float denominador = normal.dot_product(dRayo); 
    if (denominador != 0) { // Si == 0 es paralelo
        float distInterseccion = (-(distancia + normal.dot_product(oRayo-Punto3D(0,0,0)))) / denominador;

        if(distInterseccion > 0) {
            // Lo añade al vector si el plano se encuentra delante del origen del rayo
            Punto3D puntoInterseccion(oRayo, dRayo, distInterseccion);
            Interseccion interseccion(distInterseccion, puntoInterseccion, normal.normalize());
            //interseccion.primitiva = (Primitiva*)this;
            return true;
        }
    }
    return false;
}

Direccion Plano::getNormal(Punto3D x) const {
    return normal;
}

float Plano::getDistancia() {
    return distancia;
}

// Print
ostream& operator<<(ostream& os, const Plano& plano) {
    os << "Plano";
    return os;
}