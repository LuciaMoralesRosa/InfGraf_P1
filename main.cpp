#include <iostream>
using namespace std;
#include "punto3d.hpp"
#include "direccion.hpp"
#include <math.h>
// g++ main.cpp punto3d.cpp direccion.cpp -o programa


int main() {
    // Crear dos puntos
    Punto3D p1(3.0, 4.0, 2.0);
    Punto3D p2(1.0, 2.0, -1.0);

    // Sumar los puntos usando el operador +
    Punto3D p3 = p1 + p2;

    // Comparar los puntos usando el operador ==
    if (p1 == p2) {
        cout << "Los puntos p1 y p2 son iguales" << endl;
    } else {
        cout << "Los puntos p1 y p2 son diferentes" << endl;
    }

    // Imprimir los puntos usando el operador <<
    cout << "p1: " << p1 << endl;
    cout << "p2: " << p2 << endl;
    cout << "p3 (p1 + p2): " << p3 << endl;

    // Crear dos puntos
    Direccion d1(3.0, 4.0, 2.0);
    Direccion d2(1.0, 2.0, -1.0);

    // Sumar los puntos usando el operador +
    Direccion d3 = d1 + d2;
    Direccion d4(1.0, 2.0, -1.0);

    // Comparar los puntos usando el operador ==
    if (d1 == d2) {
        cout << "Las direcciones d1 y d2 son iguales" << endl;
    } else {
        cout << "Las direcciones d1 y d2 son diferentes" << endl;
    }
    if (d2 == d4) {
        cout << "Las direcciones d2 y d4 son iguales" << endl;
    } else {
        cout << "Las direcciones d2 y d4 son diferentes" << endl;
    }

    Direccion d5 = d1 * 2;
    Direccion d6 = d1 / 2;
    Direccion d7 = d5.dot_product(d6);
    //Direccion d8 = d5.vector_product(d6);

    Direccion d10 = Direccion(-3,4,0);
    cout << d10.modulus() <<endl;
    Direccion d9 = d10.normalize();
    cout << d9.modulus() <<endl;
    if (d9.is_normalized()) {
        cout << "d9 es normal" << endl;
    }

    // Imprimir las direcciones usando el operador <<
    //cout << "d1: " << d1 << endl;
    //cout << "d2: " << d2 << endl;
    //cout << "d3 (d1 + d2): " << d3 << endl;
    //cout << "d5 (d1 * 2): " << d5 << endl;
    //cout << "d6 (d1 / 2): " << d6 << endl;
    //cout << "d7 (d5 . d6): " << d7 << endl;
    //cout << "d8 (d5 x d6): " << d8 << endl;
    cout << "d9 (normalized): " << d9 << endl;

    return 0;
}