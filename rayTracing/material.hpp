#pragma once

#include <tuple>
#include "../imagen/espacioColor/rgb.hpp"


class Material {

    private:
        double coef_difuso, coef_especular, coef_refraccion, coef_absorpcion;
        

    public:
        /**
         * @brief Constructor de Material
         * 
         * @param _coef_difuso Coeficiente de difusión del material
         * @param _coef_especular Coeficiente especular del material
         * @param _coef_refraccion Coeficiente de refracción del material
         * @param _coef_absorpcion Coeficiente de absorpcion del material
         */
        Material(double _coef_difuso, double _coef_especular, double _coef_refraccion, double _coef_absorpcion = 0) : coef_difuso(_coef_difuso), coef_especular(_coef_especular), coef_refraccion(_coef_refraccion), coef_absorpcion(_coef_absorpcion) {};

};