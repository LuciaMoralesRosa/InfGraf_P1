#ifndef TONEMAPPING_HPP
#define TONEMAPPING_HPP


#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <iomanip>
#include "formatoPPM.hpp"
#include <cmath>

using namespace std;

namespace ToneMapping{

    FormatoPPM corte(FormatoPPM img, float corte);
    PixelRGB corte(PixelRGB pixel, float corte);

    FormatoPPM lineal(FormatoPPM img);
    PixelRGB lineal(FormatoPPM img, PixelRGB pixel);
    
    FormatoPPM linealCorte(FormatoPPM img, float corte);
    PixelRGB linealCorte(FormatoPPM imagen, PixelRGB pixel, float corte);    
    
    FormatoPPM gamma(FormatoPPM img, float gamma);
    PixelRGB gamma(PixelRGB pixel, float gamma);
    
    FormatoPPM gammaCorte(FormatoPPM img, float gamma, float corte);
    PixelRGB gammaCorte(PixelRGB pixel, float gamma, float corte);
    
    FormatoPPM reinhard(FormatoPPM img);
    PixelRGB reinhard(PixelRGB pixel);
    
    FormatoPPM reinhardCorte(FormatoPPM img, float corte);
    PixelRGB reinhardCorte(PixelRGB pixel, float corte);

    float maximo(float a, float b, float c, float d);
}

#endif