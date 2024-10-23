#include <iostream>
using namespace std;

#include "../rayTracing/camara.hpp"
#include "../geometria/primitivasGeometricas/esfera.hpp"
#include "../geometria/primitivasGeometricas/plano.hpp"
#include "../geometria/primitivasGeometricas/escena.hpp"
#include <math.h>

// g++ tests/camaratest.cpp rayTracing/camara.cpp rayTracing/color.cpp rayTracing/pixel.cpp geometria/punto3d.cpp geometria/direccion.cpp

int main() {

    //Plano planoizq(Punto3D(1, 0, 0), Direccion(1, 0, 0), RGB(1,0,0));
    //Plano planoder(Punto3D(-1, 0, 0), Direccion(-1, 0, 0), RGB(0,1,0));
    //Plano planosuelo(Punto3D(0, 1, 0), Direccion(0, 1, 0), RGB(1,1,1));
    //Plano planotecho(Punto3D(0, -1, 0), Direccion(0, -1, 0), RGB(1,1,1));
    //Plano planoatras(Punto3D(0, 0, -1), Direccion(0, 0, -1), RGB(1,1,1));

    Esfera esfera1(Punto3D(-0.5, -0.7, 0.25), 0.3, RGB(1,0.5,0.5));
    Esfera esfera2(Punto3D(0.5, -0.7, -0.25), 0.3, RGB(0.5,0.5,1));
    
    int tamanyo[2];
    tamanyo[0] = 8;
    tamanyo[1] = 8;
    Camara camara(Punto3D(0, 0, -3.5), Direccion(0, 1, 0), Direccion(-1, 0, 0), Direccion(0, 0, 3), tamanyo);

    Escena escena;
    escena.anyadirPrimitiva(&esfera1);
    escena.anyadirPrimitiva(&esfera2);

    //cout << camara << endl;
    vector<Pixel> pixs = camara.generarPixeles();
    for(auto pix : pixs) {
        escena.intersectarPixel(pix);
    }
    /*for(int i = 0; i < pixs.size(); i++) {
        std::cout << pixs[i] << endl;
    }*/

    return 0;
}