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

namespace ToneMaping{

    FormatoPPM corte(FormatoPPM img, float corte);
    FormatoPPM lineal(FormatoPPM img);
    FormatoPPM linealCorte(FormatoPPM img, float corte);
    FormatoPPM gamma(FormatoPPM img, float gamma);
    FormatoPPM gammaCorte(FormatoPPM img, float gamma, float corte);
    FormatoPPM reinhard(FormatoPPM img);
    FormatoPPM reinhardCorte(FormatoPPM img, float corte);

    float maximo(float a, float b, float c, float d);
}

#endif