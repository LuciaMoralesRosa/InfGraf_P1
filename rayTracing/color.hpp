#ifndef COLOR_HPP
#define COLOR_HPP

#include <iostream>
using namespace std;

class Color{

    private:
        double r, g, b;

    public:

        Color(double red, double green, double blue);

        /**
         * @brief Sobrecarga del operador de inserción << para imprimir un objeto de tipo Rayo.
         * 
         * Esta función permite imprimir los valores de un objeto Rayo utilizando un flujo de salida estándar 
         * (por ejemplo, cout). La función toma una referencia al flujo de salida y una referencia constante 
         * a un objeto Rayo, y devuelve el mismo flujo de salida después de imprimir los valores de los miembros 
         * del objeto Rayo.
         * 
         * @param os Flujo de salida en el que se imprimirán los valores de Rayo.
         * @param c Referencia constante al objeto Color cuyos valores se desean imprimir.
         * @return ostream& El flujo de salida modificado con los valores de la Dirección.
         */
        friend ostream& operator<<(ostream& os, const Color& c);

};

#endif