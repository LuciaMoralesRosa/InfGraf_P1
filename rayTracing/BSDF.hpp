#pragma once 

#include "../imagen/espacioColor/rgb.hpp"
using namespace std;

class BSDF{
    float r;
    float g;
    float b;

    public:
        BSDF(float _r, float _g, float _b) : r(_r), g(_g), b(_b) {};

        BSDF operator*(const BSDF& otro) const;
        RGB operator*(const RGB& otro) const;

};