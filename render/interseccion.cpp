#include "interseccion.hpp"

Interseccion::Interseccion(float _distancia, Punto3D _punto, Direccion _normal) 
    : distancia(_distancia), punto(_punto), normal(_normal), 
    inicializado(true) {};

Interseccion::Interseccion() 
    : distancia(0), punto(Punto3D(0,0,0)), normal(Direccion(0,0,0)), 
    inicializado(false) {};

bool Interseccion::esNull() {
    return !inicializado;
};

float Interseccion::getDistancia() {
    return distancia;
};

Punto3D Interseccion::getPunto() {
    return punto;
};

Direccion Interseccion::getNormal() {
    return normal;
};
// Print
ostream& operator<<(ostream& os, const Interseccion& i) {
    os << "    Distancia: " << i.distancia 
        << ", Punto: " << i.punto 
        << ", Normal: " << i.normal 
        << ", Primitiva: " /*<< (interseccion.primitiva ? interseccion.primitiva->getTipo() : "null") <<*/ ;
    return os;
}