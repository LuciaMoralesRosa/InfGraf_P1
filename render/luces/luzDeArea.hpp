#pragma once

#include "../../geometria/primitivasGeometricas/plano.hpp"
#include "fuenteLuz.hpp"

using namespace std;

class LuzDeArea : public FuenteLuz {
    protected: 
        Plano plano;

    public: 
        LuzDeArea(Plano pl, Punto3D c, RGB p) : plano(pl), FuenteLuz(c, p, 1) {};

        Direccion getNormal();
        float getDistancia();

        int getTipo() const override;
        ~LuzDeArea(){};
};