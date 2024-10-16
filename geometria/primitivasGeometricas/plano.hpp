#ifndef PLANO_HPP
#define PLANO_HPP

#include <vector>
#include "primitiva.hpp"
#include "punto3d.hpp"
#include "direccion.hpp"
#include "rayo.hpp"

class Plano : public Primitiva {
    private:
        Punto3D punto;
        Direccion normal;

    public:

        /**
         * @brief Constructor que crea un plano a partir de un punto y una dirección (normal).
         *
         * Este constructor define un plano utilizando un punto en el plano y una 
         * dirección que actúa como la normal del plano. El punto especifica una 
         * posición en el plano, mientras que la dirección define su orientación.
         *
         * @param p Un punto en el plano.
         * @param n La dirección que representa la normal del plano. Se asume que la 
         *          dirección está normalizada o se normalizará internamente.
         */
        Plano(Punto3D p, Direccion n);

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
        Interseccion interseccionRayo(Rayo rayo) const override;

};

#endif