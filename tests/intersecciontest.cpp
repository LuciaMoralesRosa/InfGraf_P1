#include <iostream>
using namespace std;

#include "rayo.hpp"
#include "esfera.hpp"
#include <math.h>

// g++ main.cpp rayo.cpp esfera.cpp -o interseccion

int main() {
    Rayo rayo 
    Vector3 P0 = {0, 0, 0};  // Origen del rayo
    Vector3 d = {1, 1, 1};   // Dirección del rayo (normalizada)
    Vector3 C = {5, 5, 5};   // Centro de la esfera
    double r = 2.0;          // Radio de la esfera

    auto [intersecta, t1, t2] = intersectRaySphere(P0, d, C, r);

    if (intersecta) {
        std::cout << "El rayo intersecta la esfera en t1 = " << t1 << " y t2 = " << t2 << std::endl;
    } else {
        std::cout << "El rayo no intersecta la esfera." << std::endl;
    }

    return 0;
}