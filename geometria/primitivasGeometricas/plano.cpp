#include "plano.hpp"


/*Plano::Plano(Punto3D _p, Direccion _n, RGB _color) : Primitiva(_color, "Plano") {
    punto = _p;
    normal = _n.normalize();
}*/

Plano::Plano(Direccion n, float dist, Textura _textura) : Primitiva(_textura, "Plano"){
    normal = n;
    distancia = dist;
}


Interseccion Plano::interseccionRayo(Rayo rayo) const {
    Interseccion resultado;
    resultado.intersecta = false;

    Punto3D o = rayo.getOrigen();
    Direccion d = rayo.getDireccion().normalize();
    float dist = (-(distancia + normal.dot_product(o-Punto3D(0,0,0)))) / normal.dot_product(d);

    if(dist > 0) {
        resultado.intersecta = true;
        resultado.distancia = dist;
        resultado.puntoInterseccion = Punto3D(o, d, dist);
        resultado.normal = this->normal.normalize();
        resultado.colorPrimitiva = getColor();
    }
    else {
        resultado.distancia = 0;
        resultado.puntoInterseccion = Punto3D();
    }

    return resultado;
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