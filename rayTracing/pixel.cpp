#include "pixel.hpp"

Pixel::Pixel(Punto3D _up_left, Punto3D _down_right, RGB _color) : up_left(_up_left), down_right(_down_right), color(_color) {}

Pixel::Pixel(Punto3D _up_left, Punto3D _down_right) : up_left(_up_left), down_right(_down_right), color(1,1,1) {}

RGB Pixel::getColor(){
    return color;
}

// Print
ostream& operator<<(ostream& os, const Pixel& p) {
    os << p.color;
    return os;
}