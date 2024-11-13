#pragma once
#include "../geometria/punto3d.hpp"
//#include "../geometria/primitivasGeometricas/primitiva.hpp"
#include <vector>

/**
 * @brief Intersección de un rayo con una primitiva
 */
class Interseccion{
    private:
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
        Interseccion(float _distancia, Punto3D _punto, Direccion _normal);
        /**
         * @brief Constructor de Interseccion no inicializada
         * 
         * @param _distancia Distancia desde el rayo hasta la interseccion
         * @param _punto Punto en el que intersecta
         * @param _normal Normal del punto intersectado
         */
        Interseccion();

        bool esNull();

        float getDistancia();

        Punto3D getPunto();
        
        Direccion getNormal();
        /**
         * @brief Sobrecarga del operador de inserción << para imprimir un objeto de tipo Interseccion.
         * 
         * Esta función permite imprimir los valores de un objeto Interseccion utilizando un flujo de salida estándar 
         * (por ejemplo, cout). La función toma una referencia al flujo de salida y una referencia constante 
         * a un objeto Interseccion, y devuelve el mismo flujo de salida después de imprimir los valores de los miembros 
         * del objeto Interseccion.
         * 
         * @param os Flujo de salida en el que se imprimirán los valores de Interseccion.
         * @param i Referencia constante al objeto Interseccion cuyos valores se desean imprimir.
         * @return ostream& El flujo de salida modificado con los valores de la Interseccion.
         */
        friend ostream& operator<<(ostream& os, const Interseccion& i);

};