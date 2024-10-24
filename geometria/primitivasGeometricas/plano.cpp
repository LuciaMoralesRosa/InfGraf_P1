#include "plano.hpp"


Plano::Plano(Punto3D _p, Direccion _n, RGB _color) : Primitiva(_color) {
    punto = _p;
    normal = _n.normalize();
}

Plano::Plano(Direccion n, float distancia, RGB color) : Primitiva(color){
    normal = n;
    Punto3D p(n.getx() * distancia, n.gety() * distancia, n.getz() * distancia);
    punto = p;
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


// Print
ostream& operator<<(ostream& os, const Plano& plano) {
    os << "Plano";
    return os;
}