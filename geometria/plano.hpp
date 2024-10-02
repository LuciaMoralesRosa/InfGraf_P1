#ifndef PLANO_HPP
#define PLANO_HPP

#include <vector>
#include "punto3d.hpp"
#include "direccion.hpp"
#include "rayo.hpp"

class Plano{
    private:
        Punto3D punto;
        Direccion normal;

    public:
        Plano(Punto3D p, Direccion n);

        float interseccionRayo(Rayo rayo);

};

#endif