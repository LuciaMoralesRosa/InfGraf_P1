#include "hsl.hpp"

// Constructor
HSL::HSL(float hue, float saturation, float lightness) : h(hue), s(saturation), l(lightness) {}

HSL::HSL(const RGB color){
    float r = color.getR();
    float g = color.getG();
    float b = color.getB();

    float cMax = max(r, max(g, b));
    float cMin = min(r, min(g, b));
    float delta = cMax - cMin;

    // Calcular la luminosidad (L)
    l = (cMax + cMin) / 2.0f;

    // Calcular la saturación (S)
    if (delta != 0) {
        if (l < 0.5f) {
            s = delta / (cMax + cMin);
        } else {
            s = delta / (2.0f - cMax - cMin);
        }
    }
    else{
        s = 0;
    }

    // Calcular el matiz (H)
    if (delta != 0) {
        if (cMax == r) {
            h = 60.0f * fmod((g - b) / delta, 6);
        } else if (cMax == g) {
            h = 60.0f * ((b - r) / delta + 2);
        } else if (cMax == b) {
            h = 60.0f * ((r - g) / delta + 4);
        }
        else {
            h = 0;
        }
    }
    else {
        h = 0;
    }

    // Ajustar el matiz para que esté en el rango [0, 360]
    if (h < 0) {
        h += 360.0f;
    }
}

HSL::HSL(const HSV color){
    float s_hsv = color.getS();
    float v = color.getV();

    h = color.getH();
    l = v * (1 - (s_hsv / 2));
    if(l == 0 || l == 1){
        s = 0;
    } 
    else{
        s = (v - l) / min(l, 1 - l);
    }

}

float HSL::getH() const{
    return h;
}

float HSL::getS() const{
    return s;
}

float HSL::getL() const{
    return l;
}



// Implementación del método mostrarColor
void HSL::mostrarColor() const {
    cout << "HSL(" << h << ", " << s << ", " << l << ")" << endl;
}

ostream& operator<<(ostream& os, const HSL& color) {
    os << "HSL(" << color.h << ", " << color.s << ", " << color.l << ")";
    return os;
}
