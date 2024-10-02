#include <iostream>
using namespace std;

#include "rayo.hpp"
#include "esfera.hpp"
#include <math.h>

// g++ main.cpp rayo.cpp esfera.cpp -o interseccion

int main() {
    Punto3D P0(0,0,0);  // Origen del rayo
    Direccion d(1,1,1);   // Dirección del rayo (normalizada)
    Rayo rayo(Punto3D P0, Direccion d);
    Punto3D C(5,5,5);   // Centro de la esfera
    double r = 2.0;          // Radio de la esfera
    Esfera esfera(C, r);

    vector<Punto3D> intersecciones = esfera.interseccionRayo(rayo);

    cout << intersecciones;

    /*if (intersecta) {
        std::cout << "El rayo intersecta la esfera en t1 = " << t1 << " y t2 = " << t2 << std::endl;
    } else {
        std::cout << "El rayo no intersecta la esfera." << std::endl;
    }*/

    return 0;
}