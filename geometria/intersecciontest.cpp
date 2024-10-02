#include <iostream>
using namespace std;

#include "rayo.hpp"
#include "esfera.hpp"
#include <math.h>

// g++ tests/intersecciontest.cpp geometria/rayo.cpp geometria/esfera.cpp geometria/punto3d.cpp geometria/direccion.cpp -o interseccion
// g++ intersecciontest.cpp rayo.cpp esfera.cpp punto3d.cpp direccion.cpp -o interseccion

int main() {
    Punto3D P0(0,0,0);  // Origen del rayo
    Direccion d(1,1,1);   // Dirección del rayo (normalizada)
    Rayo rayo(P0, d);
    Punto3D C(5,5,5);   // Centro de la esfera
    double r = 2.0;          // Radio de la esfera
    Esfera esfera(C, r);

    vector<Punto3D> intersecciones = esfera.interseccionRayo(rayo);

    for (int i = intersecciones.size(); i > 0; i--) {
        cout << intersecciones[i-1];
    }

    /*if (intersecta) {
        std::cout << "El rayo intersecta la esfera en t1 = " << t1 << " y t2 = " << t2 << std::endl;
    } else {
        std::cout << "El rayo no intersecta la esfera." << std::endl;
    }*/

    return 0;
}