#include <iostream>
using namespace std;

#include "../rayTracing/camara.hpp"
#include "../geometria/primitivasGeometricas/esfera.hpp"
#include "../geometria/primitivasGeometricas/plano.hpp"
#include <math.h>

// g++ tests/camaratest.cpp rayTracing/camara.cpp geometria/punto3d.cpp geometria/direccion.cpp

int main() {

    Plano planoizq(Punto3D(1, 0, 0), Direccion(1, 0, 0), Color(1,0,0));
    Plano planoder(Punto3D(-1, 0, 0), Direccion(-1, 0, 0), Color(0,1,0));
    Plano planosuelo(Punto3D(0, 1, 0), Direccion(0, 1, 0), Color(1,1,1));
    Plano planotecho(Punto3D(0, -1, 0), Direccion(0, -1, 0), Color(1,1,1));
    Plano planoatras(Punto3D(0, 0, -1), Direccion(0, 0, -1), Color(1,1,1));

    Esfera esfera1(Punto3D(-0.5, -0.7, 0.25), 0.3, Color(1,0.5,0.5));
    Esfera esfera2(Punto3D(0.5, -0.7, -0.25), 0.3, Color(0.5,0.5,1));
    
    int tamanyo[2];
    tamanyo[0] = 8;
    tamanyo[1] = 8; 
    Camara camara(Punto3D(0, 0, -3.5), Direccion(0, 1, 0), Direccion(-1, 0, 0), Direccion(0, 0, 3), tamanyo);

    cout << camara << endl;
    camara.generarPuntos();

    return 0;
}