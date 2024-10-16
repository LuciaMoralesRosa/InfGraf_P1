#ifndef RGB_HPP
#define RGB_HPP

#include <iostream>
#include <memory.h>
#include <math.h>


#include "espacioColor.hpp"
#include "hsv.hpp"
#include "hsl.hpp"

using namespace std;

class RGB : public EspacioColor {
private:
    float r, g, b; // Componentes del color RGB

public:
    RGB();
    RGB(float red, float green, float blue);
    RGB(HSV* color);
    RGB(HSL* color);

    void mostrarColor() const override;

    RGB normalizar(float maximoImagen = 255);

    float getR();
    float getG();
    float getB();

    // tonemapping
    RGB clamping(float valor = 1);
    RGB equalization(float valorMax, float resolucion);
    RGB equalizationClamping(float valorMax, float resolucion, float valor = 1);

    friend ostream& operator<<(ostream& os, const RGB& color);

};

#endif // RGB_HPP
