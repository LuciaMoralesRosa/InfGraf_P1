#pragma once

#include<limits>
#include "punto3d.hpp"
#include "rayo.hpp"


using namespace std;

class BoundingBox{

    private:
        Punto3D puntoMin; //Punto minimo de la BoundingBox
        Punto3D puntoMax; //Punto maximo de la BoundingBox
        Punto3D extend;

    public:

        /**
         * @brief Construye un BoundingBox sin inicializar
         * 
         */
        BoundingBox() {} 
        BoundingBox() : puntoMin(numeric_limits<float>::infinity(), numeric_limits<float>::infinity(), numeric_limits<float>::infinity()),
                        puntoMax(-numeric_limits<float>::infinity(), -numeric_limits<float>::infinity(), -numeric_limits<float>::infinity()),
                        extend(puntoMax.getx() - puntoMin.getx(), puntoMax.gety() - puntoMin.gety(), puntoMax.getz() - puntoMin.getz()) {}
        BoundingBox(Punto3D min, Punto3D max) : puntoMin(min), puntoMax(max),
                        extend(max.getx() - min.getx(), max.gety() - min.gety(), max.getz() - min.getz()) {}

        BoundingBox(Punto3D p) : BoundingBox(p, p) {}

        void growToInclude(Punto3D punto) {
            Punto3D nuevoMin(min(puntoMin.getx(), punto.getx()), min(puntoMin.gety(), punto.gety()), min(puntoMin.getz(), punto.getz()));
            puntoMin = nuevoMin;

            Punto3D nuevoMax(min(puntoMax.getx(), punto.getx()), max(puntoMax.gety(), punto.gety()), max(puntoMax.getz(), punto.getz()));
            puntoMax = nuevoMax;
            extend = puntoMax.getx() - puntoMin.getx(), puntoMax.gety() - puntoMin.gety(), puntoMax.getz() - puntoMin.getz();
        }


        void growToInclude(BoundingBox box);

        Punto3D getPuntoMin();
        Punto3D getPuntoMax();

        
        Punto3D obtenerCentro();
        bool intersecta(Rayo rayo, float tentrada, float tsalida);


};