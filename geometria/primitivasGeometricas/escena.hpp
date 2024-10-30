#ifndef ESCENA_HPP
#define ESCENA_HPP

#include <vector>
#include "primitiva.hpp"
#include "../punto3d.hpp"
#include "../direccion.hpp"
#include "../../rayTracing/rayo.hpp"
#include "../../rayTracing/pixel.hpp"
#include "../../otros/metodosAuxiliares.hpp"

struct returnInterseccionRayo{
    Primitiva* primitiva;
    vector<Punto3D> puntoInterseccion;
};


class Escena {
    private:
        vector<Primitiva*> primitivas;

    public:

        /**
         * @brief Constructor que crea una escena
         */
        Escena();

        /**
         * @brief Añade una primitiva a la escena.
         *
         * @param primitiva Primitiva que añadir a la escena.
         */
        void anyadirPrimitiva(Primitiva* primitiva);

        /**
         * @brief Intersecta un Pixel con la escena
         *
         * @param primitiva Primitiva que añadir a la escena.
         */
        void intersectarPixel(Pixel& pixel);
        returnInterseccionRayo intersectarRayo(Rayo rayo);

        //DEPURANDO
        string getTiposPrimitiva(){
            string ret = "";
            for(auto p : primitivas){
                ret = ret + ", " + p->tipo;
            }
            return ret;
        };

};

#endif