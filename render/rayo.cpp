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

/// @brief Devuelve la intersección del rayo
/// @return Interseccion del rayo
Interseccion Rayo::getInterseccion() const {
    return interseccion;
}

void Rayo::addInterseccion(Interseccion _interseccion) {
    if (interseccion.esNull() || (_interseccion.getDistancia() < interseccion.getDistancia())) {
        //cout << "Actualizando: " << interseccion.esNull() << ", " << (_interseccion.getDistancia() < interseccion.getDistancia()) << endl;
        interseccion = _interseccion;
    }
}

// Print
ostream& operator<<(ostream& os, const Rayo& r) {
    os << "Origen: " << r.origen << ", Direccion: " << r.direccion << endl;
    return os;
}