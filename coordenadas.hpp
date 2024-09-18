#ifndef COORDENADAS_HPP
#define COORDENADAS_HPP

#include <iostream>
#include <math.h>
//#include "matriz.hpp"
using namespace std;

class Coordenadas {
    private:
    float x, y, z, is_point; //Array de coordenadas
    
    public:

    //Constructor
    Coordenadas(float x_val = 0, float y_val = 0, float z_val = 0, float is_point_val = 0);

    //Operadores
    Coordenadas translate(const float x_displacement, const float y_displacement, const float z_displacement) const;

    Coordenadas scale(const float x_displacement, const float y_displacement, const float z_displacement) const;

    Coordenadas rotate_x_axis(const double angle) const;

    Coordenadas rotate_y_axis(const double angle) const;

    Coordenadas rotate_z_axis(const double angle) const;

    Coordenadas change_basis(const Coordenadas& o, const Coordenadas& u, const Coordenadas& v, const Coordenadas& w) const;

    Coordenadas multiply(const float matrix[4][4]) const;

    float dot_product(const float matrix[4]) const;

    // Print
    friend ostream& operator<<(ostream& os, const Coordenadas& c);
        
};

#endif