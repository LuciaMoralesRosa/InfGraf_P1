#pragma once

#include <iostream>
#include <math.h>
#include "../geometria/punto3d.hpp"
#include "../geometria/direccion.hpp"
#include "../imagen/espacioColor/rgb.hpp"
#include "interseccion.hpp"
using namespace std;

class Rayo {
    private:
    /**
     * @brief Origen del Rayo
     */
    Punto3D origen;
    /**
     * @brief Direccion del Rayo
     */
    Direccion direccion;
    /**
     * @brief Color del Rayo
     */
    RGB color;
    /**
     * @brief Lista de intersecciones del rayo con una escena
     */
    Interseccion interseccion;
    
    public:

        /**
         * @brief Constructor de Rayo dado el origen y la dirección
         * 
         * @param _origen Punto de origen del Rayo
         * @param _direccion Dirección del Rayo
         */
        Rayo(Punto3D _origen, Direccion _direccion);

        /**
         * @brief Constructor de Rayo dado dos puntos
         * 
         * @param _porigen Punto de origen del Rayo
         * @param _pdestino Punto hacia el que va el Rayo
         */
        Rayo(Punto3D _porigen, Punto3D _pdestino);

        /**
         * @brief Devuelve el origen del Rayo
         * 
         * @return Origen del Rayo
         */
        Punto3D getOrigen() const;

        /**
         * @brief Devuelve la dirección del Rayo
         * 
         * @return Dirección del Rayo
         */
        Direccion getDireccion() const;
        /**
         * @brief Añade una intersección al vector de intersecciones
         * 
         * @param interseccion Interseccion que añadir
         */
        void addInterseccion(Interseccion interseccion);

        /**
         * @brief Imprime información sobre las intersecciones del rayo
         */
        void printIntersecciones() const;

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
            
};
