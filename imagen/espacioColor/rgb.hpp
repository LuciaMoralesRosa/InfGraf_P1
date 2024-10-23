#pragma once
//#ifndef RGB_HPP
//#define RGB_HPP

#include <iostream>
#include <memory.h>
#include <math.h>


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
    RGB();
    RGB(float red, float green, float blue);
    RGB(const HSV color);
    RGB(const HSL color);

    void mostrarColor() const override;

    RGB normalizar(float maximoImagen = 255);

    float getR() const ;
    float getG() const ;
    float getB() const ;

    // tonemapping
    RGB clamping(float valor = 1);
    RGB equalization(float valorMax, float resolucion);
    RGB equalizationClamping(float valorMax, float resolucion, float valor = 1);

    friend ostream& operator<<(ostream& os, const RGB& color);

};

//#endif // RGB_HPP
