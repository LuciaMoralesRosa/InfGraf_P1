#pragma once

#include "primitiva.hpp"
#include "..\..\rayTracing\interseccion.hpp"
#include "..\..\rayTracing\rayo.hpp"


class Triangulo : public Primitiva {
    private:
        Punto3D a, b, c;
        Direccion normal;

    public:
        Triangulo(Punto3D p1, Punto3D p2, Punto3D p3, Textura _textura);

        Punto3D getA();
        Punto3D getB(); 
        Punto3D getC(); 
        Direccion getNormal();

        /**
         * @brief Determina la intersección entre un rayo y el triángulo.
         *
         * Este método calcula si un rayo intersecta el triángulo y, de ser así,
         * proporciona el punto de intersección y la distancia desde el origen del
         * rayo hasta el punto de intersección.
         *
         * @param rayo El rayo que se está evaluando para la intersección.
         * @return Interseccion Un objeto que contiene información sobre la intersección
         *                      (si hubo intersección, distancia y punto de intersección).
         */
        Interseccion interseccionRayo(Rayo rayo) const override;
};