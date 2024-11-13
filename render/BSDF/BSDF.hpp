#pragma once 

#include <tuple>

#include "../../imagen/espacioColor/rgb.hpp"
#include "../../geometria/direccion.hpp"
#include "../../geometria/punto3d.hpp"
#include "../../otros/metodosAuxiliares.hpp"
#include "../../otros/constantes.hpp"

using namespace std;

class BSDF{
    private:
        RGB kd, ks, kt;
        RGB ke; // Componente de emision (para las luces de area)
        float pd, ps, pt;
        float indiceRefraccion;
        float indiceRefraccionMedio1 = 1;


        float indiceReflexion; // Indice especular

        // METODOS PRIVADOS

        //Direccion evaluacionDifusa(Punto3D x, Direccion omega_o, Direccion normal); 
        RGB evaluacionDifusa();  
        RGB evaluacionRefraccion(Punto3D x, Direccion omega_o, Direccion omega_i, Direccion normal);
        RGB evaluacionEspecular(Direccion normal, Direccion omega_o);

        Direccion muestreoEspecular(Direccion normal, Direccion omega_o);
        Direccion muestreoRefraccion(Direccion omega_o, Direccion normal);
        Direccion muestreoDifuso();

        
        // Metodos privados deprecated
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
        //Direccion evaluacionRefraccion(Punto3D x, Direccion omega_o, Direccion normal);    
        RGB evaluacion(Punto3D x, Direccion omega_i, Direccion omega_o, Direccion normal);

        //Ruleta rusa para mas adelante??

    public:
        // CONSTRUCTORES
        BSDF(RGB _kd, RGB _ks = RGB(0,0,0), RGB _kt = RGB(0,0,0), RGB _ke = RGB(0,0,0));

        // METODOS
        tuple<Direccion, RGB> muestreo(const Punto3D x, const Direccion omega_o, const Direccion normal);

        // GETTERS Y SETTERS
        RGB getKd() const;
        RGB getKs() const;
        RGB getKt() const;

        // Metodos publicos deprecated
        RGB evaluacionBRDF(const Punto3D x, const Direccion omega_i, const Direccion omega_o, const Direccion normal);
        RGB evaluacion(Punto3D x, Direccion omega_i, Direccion omega_o, Direccion normal, const float u, const float v);

        // OPERADORES
        //RGB operator*(const BSDF& otro) const;
        //RGB operator*(const RGB& otro) const;

};