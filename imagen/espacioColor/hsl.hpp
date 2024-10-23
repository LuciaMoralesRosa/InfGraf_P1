#pragma once
//#ifndef HSL_HPP
//#define HSL_HPP

#include <iostream>

#include "espacioColor.hpp"
#include "rgb.hpp"
#include "hsv.hpp"

using namespace std;

class HSL : public EspacioColor {
private:
    float h, s, l; // Componentes del color HSL

public:
    HSL();
    HSL(float hue, float saturation, float lightness);
    HSL(RGB* color);
    HSL(HSV* color);

    float getH();
    float getS();
    float getL();

    void mostrarColor() const override;

    friend ostream& operator<<(ostream& os, const HSL& color);
};

//#endif // HSL_HPP
