#include "color.hpp"

Color::Color(double red, double green, double blue) : r(red), g(green), b(blue) {};

// Print
ostream& operator<<(ostream& os, const Color& c) {
    os << "(" << c.r << "," << c.g << c.b << ")";
    return os;
}