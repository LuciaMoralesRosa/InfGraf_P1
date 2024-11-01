#include "luzDeArea.hpp"

Direccion LuzDeArea::getNormal(){
    return plano.getNormal(Punto3D());
}

float LuzDeArea::getDistancia(){
    return plano.getDistancia();
}

RGB LuzDeArea::getPotencia(){
    return plano.getColor();
}
