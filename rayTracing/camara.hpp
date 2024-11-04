#ifndef CAMARA_HPP
#define CAMARA_HPP

#include <iostream>
#include <math.h>
#include <vector>
#include <array>
#include <random>
#include "../geometria/direccion.hpp"
#include "../geometria/punto3d.hpp"
#include "../imagen/imagenPPM.hpp"
#include "../imagen/espacioColor/rgb.hpp"
#include "luces/fuenteLuz.hpp"

#include "pixel.hpp"
using namespace std;

class Camara {
    private:
        Direccion u, l, f;
        Punto3D origen;
        int tamPlanoImagen[2]; // Tamaño en píxeles del plano de visualización (b * a)
        float tamPixel[2]; // Tamaño de los pixeles de la imagen (b * a)
        vector<Pixel> cuadriculaPixeles;

        void crearCuadriculaPixeles();

        /**
         * @brief Constructor de Coordenada con las componentes individuales
         * 
         * @param origen_val Punto de origen de la cámara
         * @param u_val Dirección up
         * @param l_val Dirección left
         * @param f_val Dirección forward
         * @param tam_val Tamaño en píxeles de la camara //0->ancho 1->altura
         */


    public:

        Camara(Punto3D origen_val, Direccion u_val, Direccion l_val, Direccion f_val, array<int, 2> tam_val = {256, 256});

        // GETTERS
        vector<Pixel> getCuadriculaPixeles();
        int getTamPlanoImagenBase();
        int getTamPlanoImagenAltura();
        float getTamPixelBase();
        float getTamPixelAltura();
        Punto3D getOrigen();
        void setCuadricutaPixeles(vector<Pixel> cuadricula);





};
#endif