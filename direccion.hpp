#ifndef DIRECCION_HPP
#define DIRECCION_HPP

#include <iostream>
#include <math.h>
using namespace std;

class Direccion {
    private:
    float x, y, z; //Array de coordenadas
    
    public:

    //Constructor
    Direccion(float x_val = 0, float y_val = 0, float z_val = 0);

    //Operadores
    Direccion operator+(const Direccion& dir) const;

    Direccion operator-(const Direccion& dir) const;

    Direccion operator*(const int scalar) const;

    Direccion operator/(const int scalar) const;

    float dot_product(const Direccion& dir) const;

    Direccion vector_product(const Direccion& dir) const;

    float modulus() const;
    
    Direccion normalize() const;

    bool is_perpendicular(const Direccion& dir) const;

    // Comparadores
    bool operator==(const Direccion& otro) const;
    
    bool operator!=(const Direccion& otro) const;
    
    bool operator>(const Direccion& otro) const;

    bool operator<(const Direccion& otro) const;

    bool operator>=(const Direccion& otro) const;

    bool operator<=(const Direccion& otro) const;

    bool is_normalized() const;

    // Print
    friend ostream& operator<<(ostream& os, const Direccion& d);
        
};

#endif