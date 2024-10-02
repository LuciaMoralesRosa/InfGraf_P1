#ifndef GEOMETRIA_HPP
#define GEOMETRIA_HPP

#include <iostream>
#include <vector>
#include "rayo.hpp"
using namespace std;

class Geometria {
    private:
    
    public:

        /**
         * @brief Constructor de Geometria
         * 
         * @param origin_val Punto de origen del Rayo
         * @param direction_val Dirección del Rayo
         */
        /*Geometria(Punto3D origen_val, Direccion direccion_val);*/


        /**
         * @brief Sobrecarga del operador de inserción << para imprimir un objeto de tipo Geometria.
         * 
         * Esta función permite imprimir los valores de un objeto Geometria utilizando un flujo de salida estándar 
         * (por ejemplo, cout). La función toma una referencia al flujo de salida y una referencia constante 
         * a un objeto Geometria, y devuelve el mismo flujo de salida después de imprimir los valores de los miembros 
         * del objeto Geometria.
         * 
         * @param os Flujo de salida en el que se imprimirán los valores de Geometria.
         * @param g Referencia constante al objeto Geometria cuyos valores se desean imprimir.
         * @return ostream& El flujo de salida modificado con los valores de la Dirección.
         */
        /*friend ostream& operator<<(ostream& os, const Geometria& g);*/

        virtual vector<Punto3D> interseccionRayo(Rayo rayo) const = 0;
            
};

#endif