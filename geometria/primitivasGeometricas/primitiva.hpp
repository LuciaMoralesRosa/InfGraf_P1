#pragma once 

//#ifndef PRIMITIVA_HPP
//#define PRIMITIVA_HPP

#include <tuple>
#include "../punto3d.hpp"
#include "../../imagen/espacioColor/rgb.hpp"
#include "../../rayTracing/interseccion.hpp"
#include "../../rayTracing/rayo.hpp"


class Primitiva{

    private:
        RGB color;
        

    public:
        string tipo;

        Primitiva(RGB color_val, string _tipo) : color(color_val), tipo(_tipo) {};
        Primitiva(Primitiva* p) : color(p->color), tipo(p->tipo) {};

        RGB getColor() {
            return color;
        };

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
        virtual tuple<Interseccion, const Primitiva*> interseccionRayo(Rayo rayo) const = 0;

        virtual Direccion getNormal(Punto3D punto) const = 0;

};

//#endif