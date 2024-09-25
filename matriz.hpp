#ifndef MATRIZ_HPP
#define MATRIZ_HPP

#include <iostream>
#include <math.h>
#include "coordenadas.hpp"
using namespace std;

/**
 * Implementacion de la clase Matriz y sus operaciones
 */
class Matriz {
    
    private: 
        // Matriz 4x4
        float matrix[4][4];

    public:
        /**
         * @brief Constructor de Matriz
         * 
         * @param m Valor para la matriz
         */
        Matriz(float m[4][4]);

        //Operadores
        Matriz operator+(const Matriz& m) const;
        Matriz operator-(const Matriz& m) const;
        Matriz operator*(const Matriz& m) const;
        Matriz operator*(const int scalar) const;
        Matriz operator/(const int scalar) const;

        // Comparadores
        bool operator==(const Matriz& m) const;

        // Funciones

        /**
         * Calcula el determinante de una matriz 4x4
         * 
         * @return Devuelve el valor del determinante de la matriz
         */
        float det() const;

        /**
         * Calcula la matriz adjunta
         * 
         * @return Devuelve la matriz adjunta
         */
        Matriz adjunta() const;

        /**
         * Calcula la matriz traspuesta
         * 
         * @return Devuelve la matriz traspuesta
         */
        Matriz traspuesta() const;
 
        /**
         * Calcula la matriz inversa
         * 
         * @return Devueve la matriz traspuesta
         */
        Matriz inversa() const;

        Coordenadas producto4x1(Coordenadas coord) const;

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
        friend ostream& operator<<(ostream& os, const Matriz& m);

};

#endif