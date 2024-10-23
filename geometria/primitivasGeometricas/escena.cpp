#include "escena.hpp"


Escena::Escena() {}

void Escena::anyadirPrimitiva(const Primitiva& primitiva) {
    primitivas.push_back(primitiva);
}

void Escena::intersectarPixel(Pixel& pixel) {
    for (const auto& pri : primitivas) {
        pri.interseccionRayo();
    }
}

