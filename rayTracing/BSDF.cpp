#include "BSDF.hpp"
BSDF BSDF::operator*(const BSDF& otro) const {
    return BSDF(r*otro.r, g*otro.g, b*otro.b);
}

RGB BSDF::operator*(const RGB& otro) const {
    return RGB(r*otro.getR(), g*otro.getG(), b*otro.getB());
}
