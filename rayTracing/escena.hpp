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



class Escena {
    private:
        vector<Primitiva*> primitivas;
        Camara camara;
        vector<FuenteLuz*> luces;

        // METODOS PRIVADOS
        Punto3D generarPuntoAleatorioEnPixel(mt19937 gen, Pixel pixel);

        InterseccionPrimitiva intersectarRayo(Rayo rayo);
        RGB estimacionSiguienteEvento(InterseccionPrimitiva interseccion);


    public:

        // CONSTRUCTORES
        Escena();
        Escena(vector<Primitiva*> p, Camara c, vector<FuenteLuz*> l) : primitivas(p), camara(c), luces(l) {};

        // OTROS METODOS
        void anyadirPrimitiva(Primitiva* primitiva);
        void lanzarRayosDesdeCamara(int rayosPorPixel);
        ImagenPPM crearImagenPPM();
        void rayosDesdeCamara(int nrayos);


        // PRINT
        friend ostream& operator<<(ostream& os, const Camara& c);

};