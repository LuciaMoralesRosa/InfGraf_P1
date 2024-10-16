#pragma once 

//#ifndef PRIMITIVA_HPP
//#define PRIMITIVA_HPP

#include "../punto3d.hpp"
#include "../../rayTracing/color.hpp"
#include "..\..\rayTracing\interseccion.hpp"


class Primitiva{

    private:
        Color color;

    public:

        Primitiva(Color color_val) : color(color_val) {};

        /**
         * @brief Calcula la intersección de un rayo con la primitiva.
         *
         * Este método virtual puro debe ser implementado por las clases 
         * derivadas para determinar los puntos de intersección entre un 
         * rayo y la primitiva geométrica.
         *
         * @param rayo El rayo que se utilizará para calcular la intersección.
         * @return Un vector de flotantes que representa los puntos de 
         *         intersección. El contenido y el tamaño del vector dependen 
         *         de la implementación específica y pueden incluir múltiples 
         *         puntos de intersección o estar vacío si no hay intersección.
         */
        virtual Interseccion interseccionRayo(Rayo rayo) const = 0;

};

//#endif