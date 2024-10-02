#ifndef ESFERA_HPP
#define ESFERA_HPP

#include <iostream>
#include <math.h>
#include <vector>
#include "punto3d.hpp"
#include "rayo.hpp"
using namespace std;

/**
 * Implementacion de la clase Esfera
 */
class Esfera {
    private:
        // Punto central de la esfera
        Punto3D c;

        // Valor del radio de la esfera
        float r;

        //Ciudad en el planeta
        Punto3D ciudad;

    public:
        /**
         * @brief Constructor de Esfera
         * 
         * @param _c Punto que indica el centro de la esfera
         * @param _r Valor que indica el radio de la esfera
         */
        Esfera(Punto3D _c, float _r);

        /**
         * @brief Añade un punto en la superficie de una esfera
         * 
         * @param azimut Valor que determina el angulo en el plano x
         * @param altitud Valor que determina el angulo en el plano y
         * @return Punto en la superficie de la esfera donde se encuentra la ciudad
         * 
         * @details Los valores se deben introducir en GRADOS, no en radianes.
         */
        Punto3D anyadirPunto(float azimut, float altitud);

        /**
         * @brief Devuelve > 1 si el punto esta dentro de la esfera
         * 
         * @param punto Punto del que determinar si se encuentra dentro o fuera de la esfera
         * @return ---
         * 
         */
        /*float dentroDeEsfera(Punto3D punto);*/

        vector<Punto3D> interseccionRayo(Rayo rayo);
};


#endif