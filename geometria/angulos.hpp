#ifndef ANGULOS_HPP
#define ANGULOS_HPP

#include <iostream>
#include <math.h>
using namespace std;

/**
 * @brief Convierte un ángulo de radianes a grados.
 * 
 * Esta función toma un ángulo en radianes y lo convierte a grados utilizando la fórmula:
 * grados = radianes * (180 / PI).
 * 
 * @param angulo Ángulo en radianes.
 * @return float Ángulo en grados.
 */
float radiansToGrades(float angulo);

/**
 * @brief Convierte un ángulo de grados a radianes.
 * 
 * Esta función toma un ángulo en grados y lo convierte a radianes utilizando la fórmula:
 * radianes = grados * (PI / 180).
 * 
 * @param angulo Ángulo en grados.
 * @return float Ángulo en radianes.
 */
float gradesToRadians(float angulo);



#endif