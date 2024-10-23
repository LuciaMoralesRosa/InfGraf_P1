#include "escena.hpp"


Escena::Escena() : primitivas(vector<Primitiva*>()) {}

void Escena::anyadirPrimitiva(Primitiva* primitiva) {
    primitivas.push_back(primitiva);
}

void Escena::intersectarPixel(Pixel& pixel) {
    for (const auto& pri : primitivas) {
        Interseccion inter = pri->interseccionRayo(pixel.rayos.back());
        cout << inter.intersecta << endl;
    }
}

