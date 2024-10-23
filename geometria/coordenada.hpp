#ifndef COORDENADA_HPP
#define COORDENADA_HPP

#include <iostream>
#include <math.h>
#include "angulos.hpp"
using namespace std;

class Coordenada {
    private:
    float x, y, z, is_point;
    
    public:

        /**
         * @brief Constructor de Coordenada con las componentes individuales
         * 
         * @param x_val 
         * @param y_val 
         * @param z_val 
         * @param is_point_val 
         */
        Coordenada(float x_val = 0, float y_val = 0, float z_val = 0, float is_point_val = 0);

        /**
         * @brief Constructor de coordenada con un vector
         * 
         * @param componentes Vector con las componentes de la Coordenada
         */
        Coordenada(float componentes[4]);

/*
        Coordenada translate(const float x_displacement, const float y_displacement, const float z_displacement) const;
        Coordenada scale(const float x_factor, const float y_factor, const float z_factor) const;
        Coordenada rotate_x_axis(const double angle) const;
        Coordenada rotate_y_axis(const double angle) const;
        Coordenada rotate_z_axis(const double angle) const;
        Coordenada change_basis(const Coordenada& o, const Coordenada& u, const Coordenada& v, const Coordenada& w) const;
        Coordenada multiply(const float matrix[4][4]) const;
        float dot_product(const float matrix[4]) const;
*/

        float getx() const;
        float gety() const;
        float getz() const;
        float getispoint() const;

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
        friend ostream& operator<<(ostream& os, const Coordenada& c);
            
};

#endif