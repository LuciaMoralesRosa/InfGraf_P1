#pragma once

#include "fuenteLuz.hpp"


class LuzPuntual : public FuenteLuz {
    private:

    public:
        LuzPuntual(Punto3D c, RGB p) : FuenteLuz(c, p, 0) {};
        int getTipo() const override;
        ~LuzPuntual(){};
};