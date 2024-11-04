#pragma once

#include "../../geometria/punto3d.hpp"
#include "../../imagen/espacioColor/rgb.hpp"

class FuenteLuz{
    private:
        Punto3D centro;
        RGB potencia;

    public:
        FuenteLuz(Punto3D c, RGB p) : centro(c), potencia(p) {};
        
        Punto3D getCentro();
        RGB getPotencia();

        

};
