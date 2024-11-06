#pragma once

#include "../../geometria/primitivasGeometricas/plano.hpp"
#include "fuenteLuz.hpp"

using namespace std;

class LuzDeArea : public FuenteLuz {
    protected: 
        Plano plano;

    public: 
        LuzDeArea(Plano p, Punto3D c, RGB pot) : plano(p), FuenteLuz(c, pot, AREA){};

        Direccion getNormal();
        float getDistancia();

        TipoLuz getTipo() const override;
        ~LuzDeArea();
};