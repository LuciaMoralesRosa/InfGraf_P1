#ifndef COORDENADAS_HPP
#define COORDENADAS_HPP

#include <iostream>
#include <math.h>
#include "angulos.hpp"
#include "matriz.hpp"
using namespace std;

class Coordenadas {
    private:
    float x, y, z, is_point; //Array de coordenadas
    
    public:

        /**
         * @brief Constructor de Matriz
         * 
         * @param x_val Valor de la coordenada x
         * @param y_val Valor de la coordenada y
         * @param z_val Valor de la coordenada z
         * @param is_point_val Indica si es un punto (>0) o una direccion (0)
         */
        Coordenadas(float x_val = 0, float y_val = 0, float z_val = 0, float is_point_val = 0);

        /**
         * Traslada la coordenada en un desplazamiento igual a sus parametros
         * 
         * @param x_displacement Valor del desplazamiento en el eje x
         * @param y_displacement Valor del desplazamiento en el eje y
         * @param z_displacement Valor del desplazamiento en el eje z
         * @return Coordenada trasladada
         */
        Coordenadas translate(const float x_displacement, const float y_displacement, const float z_displacement) const;

        /**
         * Escala la coordenada en un valor igual a sus parametros
         * 
         * @param x_factor Valor del desplazamiento en el eje x
         * @param y_factor Valor del desplazamiento en el eje y
         * @param z_factor Valor del desplazamiento en el eje z
         * @return Coordenada excalada
         */
        Coordenadas scale(const float x_factor, const float y_factor, const float z_factor) const;

        /**
         * Rota la coordenada en el eje x los grados dados (NO RADIANES)
         * 
         * @param angle Valor del angulo de rotacion
         * @return Coordenada rotada
         */
        Coordenadas rotate_x_axis(const double angle) const;

        /**
         * Rota la coordenada en el eje y los grados dados (NO RADIANES)
         * 
         * @param angle Valor del angulo de rotacion
         * @return Coordenada rotada
         */
        Coordenadas rotate_y_axis(const double angle) const;

        /**
         * Rota la coordenada en el eje z los grados dados (NO RADIANES)
         * 
         * @param angle Valor del angulo de rotacion
         * @return Coordenada rotada
         */
        Coordenadas rotate_z_axis(const double angle) const;

        /**
         * @brief Cambia el sistema de coordenadas de la instancia actual a una nueva base.
         * 
         * Esta función transforma las coordenadas de la instancia actual (representando un punto o un vector)
         * a un nuevo sistema de coordenadas definido por el origen `o` y los vectores base `u`, `v` y `w`. 
         * Se utiliza una matriz de cambio de base 4x4, donde los vectores de la nueva base se colocan en las 
         * primeras tres columnas, y el origen `o` se coloca en la cuarta columna.
         * 
         * @param o Coordenadas del origen del nuevo sistema de referencia.
         * @param u Primer vector de la nueva base (eje X en el nuevo sistema).
         * @param v Segundo vector de la nueva base (eje Y en el nuevo sistema).
         * @param w Tercer vector de la nueva base (eje Z en el nuevo sistema).
         * @return Coordenadas El objeto Coordenadas transformado al nuevo sistema de referencia.
         */
        Coordenadas change_basis(const Coordenadas& o, const Coordenadas& u, const Coordenadas& v, const Coordenadas& w) const;
        Coordenadas multiply(const float matrix[4][4]) const;
        float dot_product(const float matrix[4]) const;

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
        friend ostream& operator<<(ostream& os, const Coordenadas& c);
            
};

#endif