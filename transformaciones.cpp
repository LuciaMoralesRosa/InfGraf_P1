#include "transformaciones.hpp"


// Matrices para las transformaciones
Matriz4x4 matrizDesplamiento(float x, float y, float z){
    float m[4][4] = {{1, 0, 0, x},
                     {0, 1, 0, y},
                     {0, 0, 1, z},
                     {0, 0, 0, 1}};          
    return Matriz4x4(m);
}

Matriz4x4 matrizEscalado(const float x, const float y, const float z){
    float m[4][4] = {{x, 0, 0, 0},
                     {0, y, 0, 0},
                     {0, 0, z, 0},
                     {0, 0, 0, 1}};          
    return Matriz4x4(m);
}

Matriz4x4 matrizRotacion_x(const float angulo){
    float radians = gradesToRadians(angulo);
    float m[4][4] = {{1, 0, 0, 0},
                     {0, (float)cos(radians), -(float)sin(radians), 0},
                     {0, (float)sin(radians), (float)cos(radians), 0},
                     {0, 0, 0, 1}};          
    return Matriz4x4(m);
}

Matriz4x4 matrizRotacion_y(const float angulo){
    float radians = gradesToRadians(angulo);
    float m[4][4] = {{(float)cos(radians), 0, (float)sin(radians), 0},
                     {0, 1, 0, 0},
                     {-(float)sin(radians), 0, (float)cos(radians), 0},
                     {0, 0, 0, 1}};          
    return Matriz4x4(m);
}

Matriz4x4 matrizRotacion_z(const float angulo){
    float radians = gradesToRadians(angulo);
    float m[4][4] = {{(float)cos(radians), -(float)sin(radians), 0, 0},
                     {(float)sin(radians), (float)cos(radians), 0, 0},
                     {0, 0, 1, 0},
                     {0, 0, 0, 1}};          
    return Matriz4x4(m);
}

Matriz4x4 matrizCambioBase(const Coordenada& o, const Coordenada& u, const Coordenada& v, const Coordenada& w){
    float m[4][4] = {{u.getx(), v.getx(), w.getx(), o.getx()},
                     {u.gety(), v.gety(), w.gety(), o.gety()},
                     {u.getz(), v.getz(), w.getz(), o.getz()},
                     {u.getispoint(), v.getispoint(), w.getispoint(), o.getispoint()}};    
    return Matriz4x4(m);
}

/**
 * @brief Multiplica una matriz 4x4 por un objeto Coordenada.
 * 
 * Esta función toma una matriz de transformación 4x4 y un objeto de Coordenada, realiza la multiplicación de la matriz por el vector columna que representa las Coordenada (x, y, z, is_point), y devuelve un nuevo objeto `Coordenada` que contiene el resultado de la multiplicación.
 * 
 * @param m La matriz 4x4 utilizada para la multiplicación.
 * @param coordenada El objeto `Coordenada` que se multiplica por la matriz. Sus valores x, y, z y is_point se usan como el vector columna.
 * @return Coordenada Un nuevo objeto `Coordenada` que contiene el resultado de la multiplicación de la matriz por el vector.
 */
Coordenada productoMatrizCoordenada(Matriz4x4& m, Coordenada& c){
    float r[4] = {0, 0, 0, 0};
    for(int i = 0; i < 4; i++){
            r[i] = m[i][0]*c.getx() +
                    m[i][1]*c.gety() +
                    m[i][2]*c.getz() +
                    m[i][3]*c.getispoint();
    }
    return Coordenada(r);
}


//Publicas

Coordenada translate(Coordenada c, const float x, const float y, const float z) {
    Matriz4x4 transformacion = matrizDesplamiento(x, y, z);
    return Coordenada(productoMatrizCoordenada(transformacion, c));
}

Coordenada scale(Coordenada c, const float x, const float y, const float z) {
    Matriz4x4 transformacion = matrizEscalado(x, y, z);
    return Coordenada(productoMatrizCoordenada(transformacion, c));
}

Coordenada rotate_x(Coordenada c, const float angulo) {
    Matriz4x4 transformacion = matrizRotacion_x(angulo);
    return Coordenada(productoMatrizCoordenada(transformacion, c));
}

Coordenada rotate_y(Coordenada c, const float angulo) {
    Matriz4x4 transformacion = matrizRotacion_y(angulo);
    return Coordenada(productoMatrizCoordenada(transformacion, c));
}

Coordenada rotate_z(Coordenada c, const float angulo) {
    Matriz4x4 transformacion = matrizRotacion_z(angulo);
    return Coordenada(productoMatrizCoordenada(transformacion, c));
}

Coordenada change_basis(Coordenada c, const Coordenada& o, const Coordenada& u, const Coordenada& v, const Coordenada& w) {
    Matriz4x4 transformacion = matrizCambioBase(o, u, v, w);
    return Coordenada(productoMatrizCoordenada(transformacion, c));
}



