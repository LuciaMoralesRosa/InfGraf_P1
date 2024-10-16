#include "plano.hpp"


Plano::Plano(Punto3D p, Direccion n){
    punto = p;
    normal = n.normalize();
}

Interseccion Plano::interseccionRayo(Rayo rayo) const {
    Interseccion resultado;
    resultado.intersecta = false;

    Punto3D o = rayo.getOrigen();
    Direccion d = rayo.getDireccion();

    float distancia = ((-1) * normal.dot_product(o-punto)) / normal.dot_product(d);

    if(distancia > 0) {
        // Lo añade al vector si el plano se encuentra delante del origen del rayo
        resultado.distancia.push_back(distancia);
        resultado.intersecta = true;
        Punto3D puntoInterseccion(o, d, distancia);
        resultado.puntoInterseccion.push_back(puntoInterseccion);
        resultado.normal = this->normal;
    }

    return resultado;
}