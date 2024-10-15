#include <iostream>
using namespace std;

#include "rayo.hpp"
#include "esfera.hpp"
#include <math.h>

// g++ tests/intersecciontest.cpp geometria/rayo.cpp geometria/esfera.cpp geometria/punto3d.cpp geometria/direccion.cpp -o interseccion
// g++ intersecciontest.cpp rayo.cpp esfera.cpp punto3d.cpp direccion.cpp -o interseccion

int main() {
    
    float x1, y1, z1;
    cout << "Introduzca las coordenadas del origen del rayo: " << endl;
    cin >> x1 >> y1 >> z1;
    Punto3D P0(x1,y1,z1);  // Origen del rayo
    cout << "Introduzca la dirección del rayo: " << endl;
    cin >> x1 >> y1 >> z1;
    Direccion d(x1,y1,z1);   // Dirección del rayo
    Rayo rayo(P0, d);

    cout << "Introduzca las coordenadas del centro de la esfera: " << endl;
    cin >> x1 >> y1 >> z1;
    Punto3D C(x1,y1,z1);   // Centro de la esfera
    cout << "Introduzca el radio la esfera: " << endl;
    double r = 0;          // Radio de la esfera
    cin >> r;
    Esfera esfera(C, r);

    vector<float> intersecciones = esfera.interseccionRayo(rayo);

    for (int i = intersecciones.size(); i > 0; i--) {
        cout << intersecciones[i-1] << endl;
    }

    /*if (intersecta) {
        std::cout << "El rayo intersecta la esfera en t1 = " << t1 << " y t2 = " << t2 << std::endl;
    } else {
        std::cout << "El rayo no intersecta la esfera." << std::endl;
    }*/

    return 0;
}