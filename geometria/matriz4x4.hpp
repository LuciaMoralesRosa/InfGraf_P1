#ifndef MATRIZ4X4_HPP
#define MATRIZ4X4_HPP

#include <iostream>
#include <math.h>
#include "direccion.hpp"
using namespace std;

/**
 * Implementacion de la clase Matriz y sus operaciones
 */
class Matriz4x4 {
    
    private: 
        // Matriz 4x4
        float matrix[4][4];

    public:
        /**
         * @brief Constructor de Matriz4x4
         * 
         * @param m Valor para la Matriz4x4
         */
        Matriz4x4(float m[4][4]);

        /**
         * @brief Constructor de Matriz4x4 a partir de 4 listas de floats.
         * 
         * Este constructor permite inicializar una matriz 4x4 utilizando 4 arreglos de tamaño 4,
         * donde cada arreglo representa una fila de la matriz.
         * 
         * @param fila1 Arreglo de 4 floats que representa la primera fila de la matriz.
         * @param fila2 Arreglo de 4 floats que representa la segunda fila de la matriz.
         * @param fila3 Arreglo de 4 floats que representa la tercera fila de la matriz.
         * @param fila4 Arreglo de 4 floats que representa la cuarta fila de la matriz.
         */
        Matriz4x4(float fila1[4], float fila2[4], float fila3[4], float fila4[4]);

        //Operadores
        Matriz4x4 operator+(const Matriz4x4& m) const;
        Matriz4x4 operator-(const Matriz4x4& m) const;
        Matriz4x4 operator*(const Matriz4x4& m) const;
        Matriz4x4 operator*(const int scalar) const;
        Direccion operator*(Direccion d) const;
        Matriz4x4 operator/(const int scalar) const;

        /**
         * @brief Operador de indexación constante que devuelve una referencia constante a una fila.
         * 
         * @param fila El índice de la fila que se desea acceder.
         * @return const float (&)[4] Una referencia constante a la fila solicitada.
         */
        const float (&operator[](int fila) const)[4];
        

        // Comparadores
        bool operator==(const Matriz4x4& m) const;

        // Funciones

        /**
         * Calcula el determinante de una matriz 4x4
         * 
         * @return Devuelve el valor del determinante de la matriz
         */
        float det() const;

        /**
         * Calcula la Matriz4x4 adjunta
         * 
         * @return Devuelve la matriz adjunta
         */
        Matriz4x4 adjunta() const;

        /**
         * Calcula la Matriz4x4 traspuesta
         * 
         * @return Devuelve la matriz traspuesta
         */
        Matriz4x4 traspuesta() const;
 
        /**
         * Calcula la Matriz4x4 inversa
         * 
         * @return Devueve la matriz traspuesta
         */
        Matriz4x4 inversa() const;

        /**
         * @brief Sobrecarga del operador de inserción << para imprimir un objeto de tipo Matriz4x4.
         * 
         * Esta función permite imprimir los valores de un objeto Matriz4x4 utilizando un flujo de salida estándar 
         * (por ejemplo, cout). La función toma una referencia al flujo de salida y una referencia constante 
         * a un objeto Matriz4x4, y devuelve el mismo flujo de salida después de imprimir los valores de los miembros 
         * del objeto Matriz4x4.
         * 
         * @param os Flujo de salida en el que se imprimirán los valores de Matriz4x4.
         * @param d Referencia constante al objeto Matriz4x4 cuyos valores se desean imprimir.
         * @return ostream& El flujo de salida modificado con los valores de la Dirección.
         */
        friend ostream& operator<<(ostream& os, const Matriz4x4& m);

};

#endif