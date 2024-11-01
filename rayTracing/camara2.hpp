#ifndef CAMARA_HPP
#define CAMARA_HPP

#include <iostream>
#include <math.h>
#include <vector>
#include <array>
#include <random>
#include "../geometria/direccion.hpp"
#include "../geometria/punto3d.hpp"
#include "../geometria/primitivasGeometricas/escena.hpp"
#include "../imagen/imagenPPM.hpp"
#include "../imagen/espacioColor/rgb.hpp"
#include "fuenteLuz.hpp"

#include "pixel.hpp"
using namespace std;

class Camara2 {
    private:
    Direccion u, l, f;
    Punto3D origen;
    int tamPlanoImagen[2]; // Tamaño en píxeles del plano de visualización (b * a)
    float tamPixel[2]; // Tamaño de los pixeles de la imagen (b * a)
    vector<Pixel> cuadriculaPixeles;
    //ImagenPPM imagenEscena;
    Escena escena;
    vector<FuenteLuz> listaLuces;

    void crearCuadriculaPixeles();
    Punto3D generarPuntoAleatorioEnPixel(mt19937 gen, Pixel pixel);

    
    public:
        void calcularLuzDirecta(Rayo rayo, Pixel p, Punto3D x);
        /**
         * @brief Constructor de Coordenada con las componentes individuales
         * 
         * @param origen_val Punto de origen de la cámara
         * @param u_val Dirección up
         * @param l_val Dirección left
         * @param f_val Dirección forward
         * @param tam_val Tamaño en píxeles de la camara //0->ancho 1->altura
         */
        Camara2(Punto3D origen_val, Direccion u_val, Direccion l_val, Direccion f_val, array<int, 2> tam_val = {256, 256});

        vector<Pixel> generarPixeles();
        void anyadirPrimitiva(Primitiva* primitiva);

        void asignarEscena(Escena e);
        void lanzarRayos(int rayosPorPixel);


        ImagenPPM crearImagenPPM();

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
        friend ostream& operator<<(ostream& os, const Camara2& c);
            
};

#endif