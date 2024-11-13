#pragma once

#include <tuple>
#include "../imagen/espacioColor/rgb.hpp"
#include "materiales/material.hpp"

// Color y material de una primitiva
class Textura {

    private:
        RGB color;
        Material material;
        

    public:
        /**
         * @brief Constructor de Textura
         * 
         * @param _color Color de la textura
         * @param _material Material de la textura
         */
        Textura(RGB _color, Material _material) : color(_color), material(_material) {};

        /**
         * @brief Devuelve el color de la textura
         * 
         * @return Color de la textura
         */
        RGB getColor() const {
            return color;
        };

        /**
         * @brief Devuelve el material de la textura
         * 
         * @return Material de la textura
         */
        Material getMaterial() {
            return material;
        };

};