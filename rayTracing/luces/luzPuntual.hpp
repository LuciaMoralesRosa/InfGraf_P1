#pragma once

#include "fuenteLuz.hpp"
#include "tipoLuz.hpp"


class LuzPuntual : public FuenteLuz {
    private:

    public:
        LuzPuntual(Punto3D c, RGB p) : FuenteLuz(c, p, PUNTUAL) {};
        TipoLuz getTipo() const override;
        ~LuzPuntual();
};