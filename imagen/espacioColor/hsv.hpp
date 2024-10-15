#ifndef HSV_HPP
#define HSV_HPP

#include <iostream>

#include "espacioColor.hpp"
#include "rgb.hpp"
#include "hsl.hpp"

using namespace std;

class HSV : public EspacioColor {
private:
    float h, s, v;

public:
    HSV();
    HSV(float hue, float saturation, float value);
    HSV(RGB* color);
    HSV(HSL* color);

    float getH();
    float getS();
    float getV();

    void mostrarColor() const override;

    friend ostream& operator<<(ostream& os, const HSV& color);

};

#endif // HSV_HPP
