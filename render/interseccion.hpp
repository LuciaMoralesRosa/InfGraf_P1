#pragma once
#include "../geometria/punto3d.hpp"
//#include "../geometria/primitivasGeometricas/primitiva.hpp"
#include <vector>

/**
 * @brief Intersección de un rayo con una primitiva
 */
class Interseccion{
    /**
     * @brief Si la interseccion se ha inicializado
     */
    bool inicializado;
    /**
     * @brief Distancia desde el origen del rayo hasta el punto de intersección
     */
    float distancia;
    /**
     * @brief Punto en el que se produce la intersección
     */
    Punto3D punto;
    /**
     * @brief Normal generada en el punto que ha intersectado
     */
    Direccion normal;
    /**
     * @brief Primitiva en la que se ha generado esta intersección
     */
    //Primitiva* primitiva;
    public:
        /**
         * @brief Constructor de Interseccion inicializada
         * 
         * @param _distancia Distancia desde el rayo hasta la interseccion
         * @param _punto Punto en el que intersecta
         * @param _normal Normal del punto intersectado
         */
        Interseccion(float _distancia, Punto3D _punto, Direccion _normal) 
            : distancia(_distancia), punto(_punto), normal(_normal), 
            inicializado(true) {};
        /**
         * @brief Constructor de Interseccion no inicializada
         * 
         * @param _distancia Distancia desde el rayo hasta la interseccion
         * @param _punto Punto en el que intersecta
         * @param _normal Normal del punto intersectado
         */
        Interseccion() 
            : distancia(0), punto(Punto3D(0,0,0)), normal(Direccion(0,0,0)), 
            inicializado(false) {};

        bool esNull() {
            return !inicializado;
        };

};