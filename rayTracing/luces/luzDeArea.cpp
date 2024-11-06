#include "luzDeArea.hpp"

Direccion LuzDeArea::getNormal(){
    return plano.getNormal(Punto3D());
}

float LuzDeArea::getDistancia(){
    return plano.getDistancia();
}

TipoLuz LuzDeArea::getTipo() const {
    return AREA;
}
