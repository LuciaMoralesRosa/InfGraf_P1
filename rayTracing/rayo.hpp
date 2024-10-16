#ifndef RAYO_HPP
#define RAYO_HPP

#include <iostream>
#include <math.h>
#include "punto3d.hpp"
#include "direccion.hpp"
using namespace std;

class Rayo {
    private:
    Punto3D origen;
    Direccion direccion;
    Direccion inverso;
    
    public:

        /**
         * @brief Constructor de Rayo
         * 
         * @param origin_val Punto de origen del Rayo
         * @param direction_val Dirección del Rayo
         */
        Rayo(Punto3D origen_val, Direccion direccion_val);


        /**
         * @brief Sobrecarga del operador de inserción << para imprimir un objeto de tipo Rayo.
         * 
         * Esta función permite imprimir los valores de un objeto Rayo utilizando un flujo de salida estándar 
         * (por ejemplo, cout). La función toma una referencia al flujo de salida y una referencia constante 
         * a un objeto Rayo, y devuelve el mismo flujo de salida después de imprimir los valores de los miembros 
         * del objeto Rayo.
         * 
         * @param os Flujo de salida en el que se imprimirán los valores de Rayo.
         * @param r Referencia constante al objeto Rayo cuyos valores se desean imprimir.
         * @return ostream& El flujo de salida modificado con los valores de la Dirección.
         */
        friend ostream& operator<<(ostream& os, const Rayo& r);

        Punto3D getOrigen() const;
        Direccion getDireccion() const;
        Direccion getInverso() const;

            
};

#endif