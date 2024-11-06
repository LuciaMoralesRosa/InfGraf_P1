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

class Escena {
    private:
        vector<Primitiva*> primitivas;
        Camara camara;
        vector<FuenteLuz*> luces;

        // METODOS PRIVADOS
        Punto3D generarPuntoAleatorioEnPixel(mt19937 gen, Pixel pixel);

        InterseccionPrimitiva intersectarRayo(Rayo rayo);
        RGB estimacionSiguienteEvento(InterseccionPrimitiva interseccion);
        RGB trazadoDeCaminos(Rayo rayo, int reboteActual, int numeroDeRebotes);


    public:

        // CONSTRUCTORES
        Escena();
        Escena(vector<Primitiva*> p, Camara c, vector<FuenteLuz*> l) : primitivas(p), camara(c), luces(l) {};

        // OTROS METODOS
        void anyadirPrimitiva(Primitiva* primitiva);
        void anyadirLuz(FuenteLuz* luz);

        void lanzarRayosDesdeCamara(int nrayos);
        ImagenPPM crearImagenPPM();


        // PRINT
        friend ostream& operator<<(ostream& os, const Camara& c);

};