#pragma once 

//#ifndef PRIMITIVA_HPP
//#define PRIMITIVA_HPP

#include "../punto3d.hpp"
#include "../../imagen/espacioColor/rgb.hpp"
#include "..\..\rayTracing\interseccion.hpp"
#include "../../rayTracing/rayo.hpp"


class Primitiva{

    private:
        RGB color;

    public:

        Primitiva(RGB color_val) : color(color_val) {};

        /**
         * @brief Calcula la intersección de un rayo con la primitiva.
         *
         * Este método virtual puro debe ser implementado por las clases 
         * derivadas para determinar los puntos de intersección entre un 
         * rayo y la primitiva geométrica.
         *
         * @param rayo El rayo que se utilizará para calcular la intersección.
         * @return Una intersección
         */
        virtual Interseccion interseccionRayo(Rayo rayo) const = 0;

};

//#endif