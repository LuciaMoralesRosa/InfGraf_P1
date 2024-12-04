#ifndef TRANSFORMACIONES_HPP
#define TRANSFORMACIONES_HPP

#include <iostream>
#include <math.h>
#include "angulos.hpp"
#include "matriz4x4.hpp"
#include "coordenada.hpp"

using namespace std;

// Crear matriz de desplazamiento
Matriz4x4 matrizDesplamiento(float x, float y, float z);
Matriz4x4 matrizCambioBase(const Coordenada& o, const Coordenada& u, const Coordenada& v, const Coordenada& w);

/**
 * @brief Traslada la coordenada en un desplazamiento igual a sus parametros
 * 
 * @param c Coordenada a la que se aplica la trasnformacion
 * @param x Valor del desplazamiento en el eje x
 * @param y Valor del desplazamiento en el eje y
 * @param z Valor del desplazamiento en el eje z
 * @return Coordenada trasladada
 */
Coordenada translate(Coordenada c, const float x, const float y, const float z);

/**
* @brief Escala la coordenada en un valor igual a sus parametros
* 
* @param c Coordenada a la que se aplica la trasnformacion
* @param x Valor de escalado en el eje x
* @param y Valor de escalado en el eje y
* @param z Valor de escalado en el eje z
* @return Coordenada excalada
*/
Coordenada scale(Coordenada c, const float x, const float y, const float z);

/**
* @brief Rota la coordenada en el eje x los grados dados (NO RADIANES)
* 
* @param c Coordenada a la que se aplica la trasnformacion
* @param angulo Valor del angulo de rotacion
* @return Coordenada rotada "angulo"s grados a la derecha sobre el eje x
*/
Coordenada rotate_x(Coordenada c, const float angulo);

/**
* @brief Rota la coordenada en el eje y los grados dados (NO RADIANES)
* 
* @param c Coordenada a la que se aplica la trasnformacion
* @param angulo Valor del angulo de rotacion
* @return Coordenada rotada "angulo"s grados a la derecha sobre el eje y
*/
Coordenada rotate_y(Coordenada c, const float angulo);

/**
* @brief Rota la coordenada en el eje z los grados dados (NO RADIANES)
* 
* @param c Coordenada a la que se aplica la trasnformacion
* @param angulo Valor del angulo de rotacion
* @return Coordenada rotada "angulo"s grados a la derecha sobre el eje z
*/
Coordenada rotate_z(Coordenada c, const float angulo);

/**
* @brief Cambia el sistema de coordenadas de la instancia actual a una nueva base.
* 
* Esta función transforma las coordenadas de la instancia actual (representando un punto o un vector)
* a un nuevo sistema de coordenadas definido por el origen `o` y los vectores base `u`, `v` y `w`. 
* Se utiliza una matriz de cambio de base 4x4, donde los vectores de la nueva base se colocan en las 
* primeras tres columnas, y el origen `o` se coloca en la cuarta columna.
* 
* @param c Coordenada a la que se aplica la trasnformacion
* @param o Coordenada del origen del nuevo sistema de referencia.
* @param u Primer vector de la nueva base (eje X en el nuevo sistema).
* @param v Segundo vector de la nueva base (eje Y en el nuevo sistema).
* @param w Tercer vector de la nueva base (eje Z en el nuevo sistema).
* @return Coordenada El objeto Coordenada transformado al nuevo sistema de referencia.
*/
Coordenada change_basis(Coordenada c, const Coordenada& o, const Coordenada& u, const Coordenada& v, const Coordenada& w);

#endif