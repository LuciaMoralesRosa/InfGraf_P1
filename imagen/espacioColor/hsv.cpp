#include "hsv.hpp"

// Constructor
HSV::HSV(float hue, float saturation, float value) : h(hue), s(saturation), v(value) {}

HSV::HSV(const RGB& color){
    float r = color.getR();
    float g = color.getG();
    float b = color.getB();

    // Encuentra el valor máximo y mínimo
    float cmax = max(r, max(g, b));
    float cmin = min(r, min(g, b));
    float delta = cmax - cmin;

    // Calcula el valor V (valor)
    float v = cmax;

    // Calcula la saturación S
    float s = (cmax == 0) ? 0 : delta / cmax;

    // Calcula el tono H
    float h = 0;
    if (delta != 0) {
        if (cmax == r) {
            h = 60.0f * fmod(((g - b) / delta), 6.0f);
        } else if (cmax == g) {
            h = 60.0f * (((b - r) / delta) + 2.0f);
        } else if (cmax == b) {
            h = 60.0f * (((r - g) / delta) + 4.0f);
        }
    }

    // Ajustar si el tono es negativo
    if (h < 0) {
        h += 360.0f;
    }
}

HSV::HSV(const HSL& color){
    float s_hsl = color.getS();
    float l = color.getL();
    h = color.getH();

    v = l + s_hsl * min(l, 1 - l);
    
    if(v == 0){
        s = 0;
    }
    else {
        s = 2*(v - l) / 2;
    }

}

float HSV::getH() const{
    return h;
}

float HSV::getS() const{
    return s;
}

float HSV::getV() const{
    return v;
}


// Implementación del método mostrarColor
void HSV::mostrarColor() const {
    cout << "HSV(" << h << ", " << s << ", " << v << ")" << endl;
}

ostream& operator<<(ostream& os, const HSV& color) {
    os << "HSV(" << color.h << ", " << color.s << ", " << color.v << ")";
    return os;
}