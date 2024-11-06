#pragma once

#include "../../geometria/punto3d.hpp"
#include "../../imagen/espacioColor/rgb.hpp"
#include "tipoLuz.hpp"


class FuenteLuz{
    private:
        Punto3D centro;
        RGB potencia;
        int tipo;

    public:
        FuenteLuz(Punto3D c, RGB p, int t) : centro(c), potencia(p), tipo(t) {};
        
        Punto3D getCentro();
        RGB getPotencia();
        virtual int getTipo() const  = 0;
};
