#include "pixel.hpp"

Pixel::Pixel(Punto3D _up_left, Punto3D _down_right, RGB _color) : up_left(_up_left), down_right(_down_right), color(_color), rayos(vector<Rayo>()) {}

Pixel::Pixel(Punto3D _up_left, Punto3D _down_right) : up_left(_up_left), down_right(_down_right), color(1,1,1), rayos(vector<Rayo>()) {}


Rayo Pixel::generarRayoMitad(Punto3D porigen) {
    Rayo ray(porigen, Punto3D(down_right.getx()+((up_left.getx()-down_right.getx())/2), down_right.gety()+((up_left.gety()-down_right.gety())/2), down_right.getz()+((up_left.getz()-down_right.getz())/2)));
    rayos.push_back(ray);
    return ray;
}


RGB Pixel::getColor() const{
    return color;
}

void Pixel::setColor(RGB newcolor){
    color = newcolor;
}

// Print
ostream& operator<<(ostream& os, const Pixel& p) {
    os << p.getColor();
    return os;
}