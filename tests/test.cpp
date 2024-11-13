#include <iostream>
using namespace std;

#include "../render/render.hpp"
#include "../geometria/primitivasGeometricas/esfera.hpp"
//#include "../geometria/primitivasGeometricas/plano.hpp"
#include "../render/rayo.hpp"
#include <math.h>

// g++ -std=c++11 .\tests\test.cpp .\render\rayo.cpp

int main() {
    cout << "Test" << endl;
    Material plastico(0.5,0.5,0);
    Rayo rayo(Punto3D(0,0,0), Punto3D(1,1,1));
    vector<Rayo*> rayos;
    rayos.push_back(&rayo);

    Esfera esfera(Punto3D(0.5,0.5,0.5), (float)0.5, Textura(RGB(1,0,0), plastico));
    vector<Primitiva*> primitivas;
    primitivas.push_back(&esfera);
    esfera.interseccionRayo(rayo);
    Interseccion i = rayo.getInterseccion();
    cout << i << endl;

    return 0;
}