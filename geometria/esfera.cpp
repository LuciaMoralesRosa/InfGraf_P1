#include "esfera.hpp"

Esfera::Esfera(Punto3D _c, float _r) : c(_c), r(_r){ }

Punto3D Esfera::anyadirPunto(float azimut, float altitud){
    ciudad = Punto3D(c.getx() + r * (float)sin(azimut * M_PI/180.0f),
                   c.gety() + r * (float)cos(azimut * M_PI/180.0f) * (float)sin(altitud * M_PI/180.0f),
                   c.getz() + r * (float)cos(azimut * M_PI/180.0f) * (float)cos(altitud * M_PI/180.0f)); 
    return  ciudad;
}


