#include "plano.hpp"


Plano::Plano(Punto3D p, Direccion n){
    punto = p;
    normal = n.normalize();
}

vector<float> Plano::interseccionRayo(Rayo rayo) const {
    Punto3D o = rayo.getOrigen();
    Direccion d = rayo.getDireccion();

    vector<float> resultado;
    float distancia = ((-1) * normal.dot_product(o-punto)) / normal.dot_product(d);

    if(distancia > 0) {
        // Lo añade al vector si el plano se encuentra delante del origen del rayo
        resultado.push_back(distancia);
    }

    return resultado;
}