#include "luzDeArea.hpp"

Direccion LuzDeArea::getNormal(){
    return plano.getNormal(Punto3D());
}

float LuzDeArea::getDistancia(){
    return plano.getDistancia();
}

int LuzDeArea::getTipo() const {
    return 1;
}
