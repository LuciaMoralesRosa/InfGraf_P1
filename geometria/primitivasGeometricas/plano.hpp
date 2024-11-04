#ifndef PLANO_HPP
#define PLANO_HPP

#include <vector>
#include "primitiva.hpp"
#include "../punto3d.hpp"
#include "../direccion.hpp"
#include "../../rayTracing/rayo.hpp"

class Plano : public Primitiva {
    private:
        Direccion normal;
        float distancia;

    public:

        /**
         * @brief Constructor que crea un plano a partir de un punto y una dirección (normal).
         *
         * Este constructor define un plano utilizando un punto en el plano y una 
         * dirección que actúa como la normal del plano. El punto especifica una 
         * posición en el plano, mientras que la dirección define su orientación.
         *
         * @param _p Un punto en el plano.
         * @param _n La dirección que representa la normal del plano. Se asume que la 
         *          dirección está normalizada o se normalizará internamente.
         */
        //Plano(Punto3D _p, Direccion _n, RGB _color);

        Plano(Direccion normal, float dist, RGB color);

        /**
         * @brief Calcula la intersección de un rayo con un plano.
         *
         * Esta función determina la distancia desde el origen del rayo hasta el punto 
         * de intersección con el plano. Utiliza la ecuación paramétrica del rayo y 
         * la ecuación del plano para encontrar la distancia, que puede ser negativa 
         * si la intersección ocurre detrás del origen del rayo.
         *
         * @param rayo El rayo con el que se calcula la intersección. Este objeto debe 
         *        tener métodos getOrigen() que devuelve un Punto3D y getDireccion() 
         *        que devuelve una Dirección.
         * @return La distancia desde el origen del rayo hasta la intersección con 
         *         el plano. Si no hay intersección, se devuelve un vector vacio.
         */
        tuple<Interseccion, const Primitiva*> interseccionRayo(Rayo rayo) const override;

        Direccion getNormal(Punto3D x) const override;
        float getDistancia();

        /**
         * @brief Sobrecarga del operador de inserción << para imprimir un objeto de tipo Matriz.
         * 
         * Esta función permite imprimir los valores de un objeto Matriz utilizando un flujo de salida estándar 
         * (por ejemplo, cout). La función toma una referencia al flujo de salida y una referencia constante 
         * a un objeto Matriz, y devuelve el mismo flujo de salida después de imprimir los valores de los miembros 
         * del objeto Matriz.
         * 
         * @param os Flujo de salida en el que se imprimirán los valores de Matriz.
         * @param plano Referencia constante al objeto Esfera cuyos valores se desean imprimir.
         * @return ostream& El flujo de salida modificado con los valores de la Dirección.
         */
        friend ostream& operator<<(ostream& os, const Plano& plano);
};

#endif