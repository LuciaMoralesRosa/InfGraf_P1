#ifndef PUNTO3D_HPP
#define PUNTO3D_HPP

#include <iostream>
#include <math.h>
using namespace std;

class Punto3D {
    
    private: float x, y, z;

    public:
    // Constructor
    Punto3D(float x_val = 0, float y_val = 0, float z_val = 0);

    // Operadores
    Punto3D operator+(const Punto3D& otro) const;

    Punto3D operator-(const Punto3D& otro) const;

    Punto3D operator*(const float scalar) const;

    Punto3D operator/(const float scalar) const;

    // Comparadores
    bool operator==(const Punto3D& otro) const;
    
    bool operator!=(const Punto3D& otro) const;
    
    bool operator>(const Punto3D& otro) const;

    bool operator<(const Punto3D& otro) const;

    bool operator>=(const Punto3D& otro) const;

    bool operator<=(const Punto3D& otro) const;

    // Print
    friend ostream& operator<<(ostream& os, const Punto3D& p);
};

#endif