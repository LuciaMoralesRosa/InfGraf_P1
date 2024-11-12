#pragma once 

//#ifndef PRIMITIVA_HPP
//#define PRIMITIVA_HPP

#include <tuple>
#include <string>
#include "../punto3d.hpp"
#include "../../imagen/espacioColor/rgb.hpp"
#include "../../rayTracing/interseccion.hpp"
#include "../../rayTracing/rayo.hpp"
#include "../../rayTracing/textura.hpp"

using namespace std;

class Primitiva{

    private:
        Textura textura;
        string tipo;
        

    public:
        Primitiva(Textura textura_val, string t) : textura(textura_val), tipo(t) {};
        Primitiva(Primitiva* p) : textura(p->textura) {};

        RGB getColor() const {
            return textura.getColor();
        };

        string getTipo() const {
            return tipo;
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
        virtual Interseccion interseccionRayo(Rayo rayo) const = 0;

        virtual Direccion getNormal(Punto3D punto) const = 0;

};

//#endif