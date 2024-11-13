#ifndef PIXEL_HPP
#define PIXEL_HPP

#include <iostream>
#include <vector>
#include "../imagen/espacioColor/rgb.hpp"
#include "../geometria/punto3d.hpp"
#include "rayo.hpp"
using namespace std;

class Pixel {
    private:
    Punto3D up_left;
    Punto3D down_right;
    RGB color;
    
    public:
    vector<Rayo> rayos;

        /**
         * @brief Constructor de Pixel
         * 
         * @param _up_left Esquina arriba a la izquierda del Pixel
         * @param _down_right Esquina arriba a la izquierda del Pixel
         * @param _color Color del pixel
         */
        Pixel(Punto3D _up_left, Punto3D _down_right, RGB _color);

        /**
         * @brief Constructor de Pixel
         * 
         * @param _up_left Esquina arriba a la izquierda del Pixel
         * @param _down_right Esquina arriba a la izquierda del Pixel
         */
        Pixel(Punto3D _up_left, Punto3D _down_right);

        Rayo generarRayoMitad(Punto3D porigen);
        RGB getColor() const;
        void setColor(RGB newcolor);

        Punto3D getPuntoIzqSup();
        Punto3D getPuntoDchInf();


        /**
         * @brief Sobrecarga del operador de inserción << para imprimir un objeto de tipo Rayo.
         * 
         * Esta función permite imprimir los valores de un objeto Rayo utilizando un flujo de salida estándar 
         * (por ejemplo, cout). La función toma una referencia al flujo de salida y una referencia constante 
         * a un objeto Rayo, y devuelve el mismo flujo de salida después de imprimir los valores de los miembros 
         * del objeto Rayo.
         * 
         * @param os Flujo de salida en el que se imprimirán los valores de Rayo.
         * @param p Referencia constante al objeto Pixel cuyos valores se desean imprimir.
         * @return ostream& El flujo de salida modificado con los valores de la Dirección.
         */
        friend ostream& operator<<(ostream& os, const Pixel& p);
            
};

#endif