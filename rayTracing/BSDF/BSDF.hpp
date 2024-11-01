#pragma once 

#include "../../imagen/espacioColor/rgb.hpp"
#include "../../geometria/direccion.hpp"
#include "../../geometria/punto3d.hpp"


using namespace std;

class BSDF{
    private:
        RGB valor;

        float coeficienteDifusion;
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
        BSDF(RGB v, float kd) : valor(v), coeficienteDifusion(kd) {};

        // METODOS
        RGB evaluacion();
        RGB evaluacion(Punto3D x, Direccion omega_i, Direccion omega_o, Direccion normal, const float u, const float v);
        tuple<Direccion, RGB> sample(const Direccion omega_o, const Punto3D x, const Direccion normal, const float u, const float v);
        
        // GETTERS Y SETTERS
        RGB getValor() const;

        // OPERADORES
        RGB operator*(const BSDF& otro) const;
        RGB operator*(const RGB& otro) const;

};