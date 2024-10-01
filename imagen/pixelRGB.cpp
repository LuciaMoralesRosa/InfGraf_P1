#include "pixelRGB.hpp"

PixelRGB::PixelRGB(float _r, float _g, float _b) : r(_r), g(_g), b(_b){}

PixelRGB PixelRGB::operator+(const PixelRGB& pixel) const {
    return PixelRGB(r + pixel.r, g + pixel.g, b + pixel.b);
}
PixelRGB PixelRGB::operator-(const PixelRGB& pixel) const{
    return PixelRGB(r - pixel.r, g - pixel.g, b - pixel.b);
}

PixelRGB PixelRGB::operator*(const PixelRGB& pixel) const{
    return PixelRGB(r * pixel.r, g * pixel.g, b * pixel.b);
}

PixelRGB PixelRGB::operator/(const PixelRGB& pixel) const{
    return PixelRGB(r / pixel.r, g / pixel.g, b / pixel.b);
}

PixelRGB PixelRGB::operator+(const float valor) const{
    return PixelRGB(r + valor, g + valor, b + valor);
}

PixelRGB PixelRGB::operator-(const float valor) const{
    return PixelRGB(r - valor, g - valor, b - valor);
}

PixelRGB PixelRGB::operator*(const float valor) const{
    return PixelRGB(r * valor, g * valor, b * valor);
}

PixelRGB PixelRGB::operator/(const float valor) const{
    return PixelRGB(r / valor, g / valor, b / valor);
}


// Getters y setters
float PixelRGB::getRed() const{
    return r;
}

float PixelRGB::getGreen() const{
    return g;
}

float PixelRGB::getBlue() const{
    return b;
}


void PixelRGB::setRed(float valor){
    r = valor;
}

void PixelRGB::setGreen(float valor){
    g = valor;
}

void PixelRGB::setBlue(float valor){
    b = valor;
}

ostream& operator<<(ostream& os, const PixelRGB& pixel){
    os << "[" << pixel.r << ", " << pixel.g << ", " << pixel.b << "]";
    return os;
}