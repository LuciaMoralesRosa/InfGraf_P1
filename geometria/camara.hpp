#ifndef CAMARA_HPP
#define CAMARA_HPP

#include <iostream>
#include <math.h>
using namespace std;

class Camara {
    private:
    float x, y, z, is_point; //Array de coordenadas
    
    public:

        /**
         * @brief Constructor de Coordenada con las componentes individuales
         * 
         * @param u_val Valor de la coordenada x
         * @param l_val Valor de la coordenada y
         * @param f_val Valor de la coordenada z
         * @param is_point_val Indica si es un punto (>0) o una direccion (0)
         */
        Camara(float x_val = 0, float y_val = 0, float z_val = 0, float is_point_val = 0);


        /*float getx() const;
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
        /*friend ostream& operator<<(ostream& os, const Camara& c);*/
            
};

#endif