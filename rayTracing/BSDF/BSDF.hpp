#pragma once 

#include "../../imagen/espacioColor/rgb.hpp"
#include "../../geometria/direccion.hpp"
#include "../../geometria/punto3d.hpp"
#include <tuple>

using namespace std;

class BSDF{
    private:
        RGB kd, ks, kt;
        float indiceRefraccion;

        // METODOS PRIVADOS
        Direccion evaluacionDifusa(Punto3D x, Direccion omega_o, Direccion normal);    
        Direccion evaluacionEspecular(Punto3D x, Direccion omega_o, Direccion normal); 



        /**
         * @brief Calcula la direccion del rayo refractado
         * 
         * @param x 
         * @param omega_o Direccion del rayo incidente
         * @param normal Normal a la superfice en el punto de incidenica del rayo
         * 
         * @return Direccion que representa el rayo refractado
         */
        Direccion evaluacionRefraccion(Punto3D x, Direccion omega_o, Direccion normal);    

        //Ruleta rusa para mas adelante??

    public:
        // CONSTRUCTORES
        BSDF(RGB _kd, RGB _ks, RGB _kt) : kd(_kd), ks(_ks), kt(_kt) {};
        BSDF(RGB _kd) : kd(_kd), indiceRefraccion(1) {};


        // METODOSç
        RGB evaluacionBRDF(const Punto3D x, const Direccion omega_i, const Direccion omega_o, const Direccion normal);
        tuple<Direccion, RGB> muestreo(const Punto3D x, const Direccion omega_o, const Direccion normal);


        RGB evaluacion();
        RGB evaluacion(Punto3D x, Direccion omega_i, Direccion omega_o, Direccion normal, const float u, const float v);
        
        // GETTERS Y SETTERS
        RGB getValor() const;

        // OPERADORES
        RGB operator*(const BSDF& otro) const;
        RGB operator*(const RGB& otro) const;

};