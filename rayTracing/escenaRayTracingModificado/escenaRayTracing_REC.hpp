#pragma once

#include <vector>
#include <cstdlib>
#include <algorithm>

#include "../../geometria/primitivasGeometricas/primitiva.hpp"
#include "../../geometria/punto3d.hpp"
#include "../../geometria/direccion.hpp"
#include "../rayo.hpp"
#include "../pixel.hpp"
#include "../../otros/metodosAuxiliares.hpp"
#include "../camara.hpp"
#include "../luces/fuenteLuz.hpp"
#include "../luces/luzDeArea.hpp"
#include "../BSDF/BSDF.hpp"
#include "../luces/tipoLuz.hpp"
#include "../luces/luzPuntual.hpp"

const float EPSILON = 1e-8;

struct InterseccionConcreta {
    // True si existe intersección
    bool intersecta;
    // Vector de distancia a través del rayo hasta la intersección
    float distancia;
    // Vector de puntos  de intersección
    Punto3D puntoInterseccion;
    // Normal de la intersección (normalized)
    Direccion normal;
    // Puntero a la primitiva intersectada
    RGB colorPrimitiva;
};

class EscenaRayTracingREC {
    private:
        Camara camara;
        vector<Primitiva*> primitivas;
        vector<FuenteLuz*> luces;

        //Intentos shadowRays
        //bool intento1esRayoDeSombra(Punto3D puntoInterseccion, Primitiva* p);
        //RGB intento2esRayoDeSombra(Punto3D puntoInterseccion, Interseccion interseccion);
        //RGB intento3(Interseccion interseccion, Punto3D puntoInterseccion);
        //RGB intento4(Punto3D puntoEv);

        // Para pathTracer recursivo
        RGB trazadoCaminos(Rayo rayoEntrada, int actual, int nRebotes);
        InterseccionConcreta intersectarRayo(Rayo rayo);


        // Otros
        Punto3D generarPuntoAleatorioEnPixel(mt19937 gen, Pixel pixel);
        Punto3D puntoInterseccionDadaDistancia(Interseccion i, float minDistancia);
        Direccion normalInterseccionDadaDistancia(Interseccion i, float minDistancia);
        //RGB intersectarRayo(RGB colorPixel, Rayo rayo);
        bool puntoEnSegmento(Punto3D A, Punto3D B, Punto3D X);

    public:
        EscenaRayTracingREC(Camara c, vector<Primitiva*> p, vector<FuenteLuz*> f) : 
            camara(c), primitivas(p), luces(f) {};

        ImagenPPM crearImagenPPM();

        void lanzarRayos(int rayosPorPixel);
        
        // Para pathTracing recursivo
        void lanzarRayos(int rayosPorPixel, int nRebotes);
};