#include <iostream>
using namespace std;

#include "transformaciones.hpp"
#include <math.h>

// g++ test_transformaciones.cpp angulos.cpp punto3d.cpp direccion.cpp coordenada.cpp matriz4x4.cpp transformaciones.cpp -o test_transformaciones


int main(){
    Coordenada c(1, 1, 1, 1);

    cout << "Coordenada original: " << c << endl << "----------------------"  << endl << endl;
    cout << "Trasladada (1, 1, 1): " << endl << translate(c, 1, 1, 1) << endl << endl;

    cout << "Escalada (1, 1, 1): " << endl << scale(c, 1, 2, 1) << endl << endl;

    cout << "Rotacion X (90): " << endl << rotate_x(c, 90) << endl << endl;
    cout << "Rotacion Y (90): " << endl << rotate_y(c, 90) << endl << endl;
    cout << "Rotacion Z (90): " << endl << rotate_z(c, 90) << endl << endl;
    cout << "Cambio de base: " << endl << change_basis(c, Coordenada(1,1,1,1), Coordenada(1,1,1,0), Coordenada(1,1,1,0), Coordenada(1,1,1,0)) << endl<<endl;

}