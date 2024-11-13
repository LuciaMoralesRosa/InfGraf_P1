#include "rayo.hpp"

Rayo::Rayo(Punto3D _origen, Direccion _direccion) : origen(_origen),
    direccion(_direccion.normalize()), color(RGB(0,0,0)), 
    interseccion() {}

Rayo::Rayo(Punto3D _porigen, Punto3D _pdestino) : origen(_porigen),  
    direccion((_pdestino-_porigen).normalize()), color(RGB(0,0,0)), 
    interseccion() {}

Punto3D Rayo::getOrigen() const {
    return origen;
}

Direccion Rayo::getDireccion() const {
    return direccion;
}

void Rayo::addInterseccion(Interseccion _interseccion) {
    if (interseccion.esNull() || interseccion.dis) {
        interseccion = _interseccion;
    }
}

void Rayo::printIntersecciones() const {
        cout << "    Distancia: " << interseccion.distancia 
            << ", Punto: " << interseccion.punto 
            << ", Normal: " << interseccion.normal 
            << ", Primitiva: " << /*(interseccion.primitiva ? interseccion.primitiva->getTipo() : "null") <<*/ endl;
}

// Print
ostream& operator<<(ostream& os, const Rayo& r) {
    os << "Origen: " << r.origen << ", Direccion: " << r.direccion;
    return os;
}