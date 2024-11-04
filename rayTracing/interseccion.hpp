#pragma once
#include "../geometria/punto3d.hpp"
#include "../geometria/primitivasGeometricas/primitiva.hpp"
#include <vector>

struct Interseccion{
    // True si existe intersección
    bool intersecta;
    // Vector de distancia a través del rayo hasta la intersección
    vector<float> distancia;
    // Vector de puntos  de intersección
    vector<Punto3D> puntoInterseccion;
    // Normal de la intersección (normalized)
    Direccion normal;

    //Primitiva* primitiva;
};