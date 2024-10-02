#include "plano.hpp"


Plano::Plano(Punto3D p, Direccion n){
    punto = p;
    normal = n.normalize();
}

float Plano::interseccionRayo(Rayo rayo){
    Punto3D o = rayo.getOrigen();
    Direccion d = rayo.getDireccion();

    return ((-1) * normal.dot_product(o-punto)) / normal.dot_product(d);
}