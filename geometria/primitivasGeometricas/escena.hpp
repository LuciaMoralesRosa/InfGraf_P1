#ifndef ESCENA_HPP
#define ESCENA_HPP

#include <vector>
#include "primitiva.hpp"
#include "../punto3d.hpp"
#include "../direccion.hpp"
#include "../../rayTracing/rayo.hpp"
#include "../../rayTracing/pixel.hpp"

class Escena {
    private:
        vector<Primitiva> primitivas;
        

    public:

        /**
         * @brief Constructor que crea unam escena
         */
        Escena();

        /**
         * @brief Añade una primitiva a la escena.
         *
         * @param primitiva Primitiva que añadir a la escena.
         */
        void anyadirPrimitiva(const Primitiva& primitiva);

        /**
         * @brief Intersecta un Pixel con la escena
         *
         * @param primitiva Primitiva que añadir a la escena.
         */
        void intersectarPixel(Pixel& pixel);

};

#endif