#pragma once
#include "../geometria/punto3d.hpp"
#include "../geometria/primitivasGeometricas/primitiva.hpp"
#include <vector>

struct Interseccion{
    // True si existe intersección
    bool intersecta;
    // Vector de distancia a través del rayo hasta la intersección
    float distancia;
    // Vector de puntos  de intersección
    Punto3D puntoInterseccion;
    // Normal de la intersección (normalized)
    Direccion normal;
    // Color de la primitiva
    RGB colorPrimitiva;
};