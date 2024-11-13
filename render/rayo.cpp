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

Interseccion Rayo::getInterseccion() const {
    return interseccion;
}

void Rayo::addInterseccion(Interseccion _interseccion) {
    if (interseccion.esNull() || (_interseccion.getDistancia() < interseccion.getDistancia())) {
        interseccion = _interseccion;
    }
}

// Print
ostream& operator<<(ostream& os, const Rayo& r) {
    os << "Origen: " << r.origen << ", Direccion: " << r.direccion;
    return os;
}