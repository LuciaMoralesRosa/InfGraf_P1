#pragma once
//#ifndef RGB_HPP
//#define RGB_HPP

#include <iostream>
#include <memory.h>
#include <math.h>
#include <algorithm>  // Para std::max

#include "espacioColor.hpp"
#include "hsv.hpp"
#include "hsl.hpp"

using namespace std;

class HSL;  
class HSV;  

class RGB : public EspacioColor {
private:
    float r, g, b; // Componentes del color RGB

public:
    RGB() : r(0), g(0), b(0) {};
    RGB(float red, float green, float blue);
    RGB(const HSV color);
    RGB(const HSL color);

    void mostrarColor() const override;

    RGB normalizar(float maximoImagen = 255);
    float maximo() const;

    float getR() const ;
    float getG() const ;
    float getB() const ;

    // tonemapping
    RGB clamping(float valor = 1);
    RGB equalization(float valorMax, float resolucion);
    RGB equalizationClamping(float valorMax, float resolucion, float valor = 1);

    friend ostream& operator<<(ostream& os, const RGB& color);
    RGB operator*(const RGB& otro) const;
    RGB operator+(const RGB& otro) const;
    RGB operator/(const int& otro) const;
    RGB operator*(const float& otro) const;
    bool operator==(const RGB& otro) const;

    bool esNulo();
    bool esNegro();



};

//#endif // RGB_HPP
