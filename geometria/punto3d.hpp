#ifndef PUNTO3D_HPP
#define PUNTO3D_HPP

#include <iostream>
#include <math.h>
#include "direccion.hpp"
using namespace std;

class Punto3D {
    
    private: 
        // Coordenadas del punto en el espacio
        float x, y, z;

    public:
        /**
         * @brief Constructor de Punto3D
         * 
         * @param x_val Valor para la coordenada x del punto
         * @param z_val Valor para la coordenada z del punto
         * @param y_val Valor para la coordenada y del punto
         */
        Punto3D(float x_val = 0, float y_val = 0, float z_val = 0);

        // Operadores
        Punto3D operator+(const Punto3D& otro) const;
        Direccion operator-(const Punto3D& otro) const;
        Punto3D operator*(const float scalar) const;
        Punto3D operator/(const float scalar) const;

        // Comparadores
        bool operator==(const Punto3D& otro) const;    
        bool operator!=(const Punto3D& otro) const;
        bool operator>(const Punto3D& otro) const;
        bool operator<(const Punto3D& otro) const;
        bool operator>=(const Punto3D& otro) const;
        bool operator<=(const Punto3D& otro) const;

        /**
         * @brief Permite obtener la coordenada x del punto
         * 
         * @return Devuelve la coordenada x del punto
         */
        float getx();

        /**
         * @brief Permite obtener la coordenada y del punto
         * 
         * @return Devuelve la coordenada y del punto
         */
        float gety();

        /**
         * @brief Permite obtener la coordenada z del punto
         * 
         * @return Devuelve la coordenada z del punto
         */
        float getz();

        /**
         * @brief Sobrecarga del operador de inserción << para imprimir un objeto de tipo Matriz.
         * 
         * Esta función permite imprimir los valores de un objeto Matriz utilizando un flujo de salida estándar 
         * (por ejemplo, cout). La función toma una referencia al flujo de salida y una referencia constante 
         * a un objeto Matriz, y devuelve el mismo flujo de salida después de imprimir los valores de los miembros 
         * del objeto Matriz.
         * 
         * @param os Flujo de salida en el que se imprimirán los valores de Matriz.
         * @param d Referencia constante al objeto Matriz cuyos valores se desean imprimir.
         * @return ostream& El flujo de salida modificado con los valores de la Dirección.
         */
        friend ostream& operator<<(ostream& os, const Punto3D& p);
};

#endif