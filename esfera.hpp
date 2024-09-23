#ifndef ESFERA_HPP
#define ESFERA_HPP

#include <iostream>
#include <math.h>
#include "punto3d.hpp"
using namespace std;

class Esfera{
    private:
    Punto3D c;
    float r;
    public:
    Esfera(Punto3D _c, float _r);

    Punto3D anyadirPunto(float azimut, float altitud);

};


#endif