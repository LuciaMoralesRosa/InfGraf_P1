#include "rayo.hpp"
    
//Constructor
Rayo::Rayo(Punto3D origen_val, Direccion direccion_val) : origen(origen_val),
    direccion(direccion_val), inverso(1/direccion_val.getx(), 1/direccion_val.gety(), 1/direccion_val.getz()) {}

Punto3D Rayo::getOrigen() const {
    return origen;
}

Direccion Rayo::getDireccion() const {
    return direccion;
}

Direccion Rayo::getInverso() const{
    return inverso;
}
// Print
ostream& operator<<(ostream& os, const Rayo& r) {
    os << "Origen: " << r.origen << ", Direccion: " << r.direccion;
    return os;
}