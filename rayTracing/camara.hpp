#ifndef CAMARA_HPP
#define CAMARA_HPP

#include <iostream>
#include <math.h>
#include <vector>
#include "../geometria/direccion.hpp"
#include "../geometria/punto3d.hpp"
using namespace std;

class Camara {
    private:
    Direccion u, l, f;
    Punto3D origen;
    int tamanyo[2]; // Tamaño en píxeles del plano de visualización
    
    public:

        /**
         * @brief Constructor de Coordenada con las componentes individuales
         * 
         * @param origen_val Punto de origen de la cámara
         * @param u_val Dirección up
         * @param l_val Dirección left
         * @param f_val Dirección forward
         * @param tam_val Tamaño en píxeles del plano
         */
        Camara(Punto3D origen_val, Direccion u_val, Direccion l_val, Direccion f_val, int tam_val[2]);

        vector<Punto3D> generarPuntos();

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
        friend ostream& operator<<(ostream& os, const Camara& c);
            
};

#endif