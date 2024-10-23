#pragma once
//#ifndef HSV_HPP
//#define HSV_HPP

#include <iostream>

#include "espacioColor.hpp"
#include "rgb.hpp"
#include "hsl.hpp"

using namespace std;

class HSL;  
class RGB;  

class HSV : public EspacioColor {
private:
    float h, s, v;

public:
    HSV();
    HSV(float hue, float saturation, float value);
    HSV(const RGB color);
    HSV(const HSL color);

    float getH() const;
    float getS() const;
    float getV() const;

    void mostrarColor() const override;

    friend ostream& operator<<(ostream& os, const HSV& color);

};

//#endif // HSV_HPP
