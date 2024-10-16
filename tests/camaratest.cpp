#include <iostream>
using namespace std;

#include "../rayTracing/camara.hpp"
#include <math.h>

// g++ tests/camaratest.cpp rayTracing/camara.cpp geometria/punto3d.cpp geometria/direccion.cpp

int main() {
    
    Punto3D origen(0, 0, -3.5);
    Direccion left(-1, 0, 0);
    Direccion up(0, 1, 0);
    Direccion forward(0, 0, 3);
    int tamanyo[2];
    tamanyo[0] = 256;
    tamanyo[1] = 256; 
    Camara camara(origen, up, left, forward,tamanyo);

    cout << camara << endl;
    camara.generarPuntos();

    return 0;
}