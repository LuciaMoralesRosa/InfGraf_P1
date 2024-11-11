#pragma once

#include <vector>
#include "../geometria/primitivasGeometricas/primitiva.hpp"
#include "../geometria/punto3d.hpp"
#include "../geometria/direccion.hpp"
#include "rayo.hpp"
#include "pixel.hpp"
#include "../otros/metodosAuxiliares.hpp"
#include "camara.hpp"
#include "luces/fuenteLuz.hpp"
#include "luces/luzDeArea.hpp"
#include "BSDF/BSDF.hpp"
#include "luces/tipoLuz.hpp"
#include "luces/luzPuntual.hpp"

struct InterseccionPrimitiva {
    // True si existe intersección
    bool intersecta;
    // Vector de distancia a través del rayo hasta la intersección
    float distancia;
    // Vector de puntos  de intersección
    Punto3D puntoInterseccion;
    // Normal de la intersección (normalized)
    Direccion normal;
    // Puntero a la primitiva intersectada
    Primitiva* primitiva;
};

class EscenaRayTracing {
    private:
        Camara camara;
        vector<Primitiva*> primitivas;
        vector<FuenteLuz*> luces;

        Punto3D generarPuntoAleatorioEnPixel(mt19937 gen, Pixel pixel);
        RGB intersectarRayo(RGB colorPixel, Rayo rayo);

    public:
        EscenaRayTracing(Camara c, vector<Primitiva*> p, vector<FuenteLuz*> f) : 
            camara(c), primitivas(p), luces(f) {};

        ImagenPPM crearImagenPPM();
        void lanzarRayos(int rayosPorPixel);
};