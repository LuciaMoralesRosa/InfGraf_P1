#ifndef ESFERA_HPP
#define ESFERA_HPP

#define _USE_MATH_DEFINES
#define M_PI           3.14159265358979323846  /* pi */

#include <iostream>
#include <math.h>
#include <vector>

#include "primitiva.hpp"
#include "../punto3d.hpp"
#include "../../rayTracing/rayo.hpp"
using namespace std;

/**
 * Implementacion de la clase Esfera
 */
class Esfera : public Primitiva {
    private:
        // Punto central de la esfera
        Punto3D c;

        // Valor del radio de la esfera
        float r;

        //Ciudad en el planeta
        Punto3D ciudad;

    public:
        /**
         * @brief Constructor de Esfera
         * 
         * @param _c Punto que indica el centro de la esfera
         * @param _r Valor que indica el radio de la esfera
         * @param _color Color de la esfera
         */
        Esfera(Punto3D _c, float _r, RGB _color);

        /**
         * @brief Añade un punto en la superficie de una esfera
         * 
         * @param azimut Valor que determina el angulo en el plano x
         * @param altitud Valor que determina el angulo en el plano y
         * @return Punto en la superficie de la esfera donde se encuentra la ciudad
         * 
         * @details Los valores se deben introducir en GRADOS, no en radianes.
         */
        Punto3D anyadirPunto(float azimut, float altitud);

        /**
         * @brief Calcula la intersección de un rayo con la esfera.
         *
         * Este método determina los puntos de intersección entre un rayo 
         * y la esfera utilizando la ecuación cuadrática. Devuelve un 
         * vector con las distancias a los puntos de intersección, que 
         * pueden ser uno o dos.
         *
         * @param rayo El rayo que se utilizará para calcular la intersección.
         * @return Un vector de flotantes que representa las distancias a los puntos 
         *         de intersección. Puede contener cero, uno o dos valores.
         */
        Interseccion interseccionRayo(Rayo rayo) const override;

        /**
         * @brief Sobrecarga del operador de inserción << para imprimir un objeto de tipo Matriz.
         * 
         * Esta función permite imprimir los valores de un objeto Matriz utilizando un flujo de salida estándar 
         * (por ejemplo, cout). La función toma una referencia al flujo de salida y una referencia constante 
         * a un objeto Matriz, y devuelve el mismo flujo de salida después de imprimir los valores de los miembros 
         * del objeto Matriz.
         * 
         * @param os Flujo de salida en el que se imprimirán los valores de Matriz.
         * @param esfera Referencia constante al objeto Esfera cuyos valores se desean imprimir.
         * @return ostream& El flujo de salida modificado con los valores de la Dirección.
         */
        friend ostream& operator<<(ostream& os, const Esfera& esfera);
};


#endif