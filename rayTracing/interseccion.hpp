#pragma once
#include "..\geometria\punto3d.hpp"
#include <vector>

struct Interseccion{
    bool intersecta;
    vector<float> distancia;
    vector<Punto3D> puntoInterseccion;
    Direccion normal;

};