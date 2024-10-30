#include "escena.hpp"


Escena::Escena() : primitivas(vector<Primitiva*>()) {}

void Escena::anyadirPrimitiva(Primitiva* primitiva) {
    primitivas.push_back(primitiva);
}

void Escena::intersectarPixel(Pixel& pixel) {
    for (const auto& pri : primitivas) {
        Interseccion inter = pri->interseccionRayo(pixel.rayos.back());
        if (inter.intersecta) {
            pixel.setColor(pri->getColor());
            cout << "intersectado" << pixel.getColor() << endl;
        }
    }
}

void Escena::intersectarRayo(Pixel& pixel, Rayo rayo){
    for(const auto& pri : primitivas){        
        Interseccion inter = pri->interseccionRayo(rayo);
        if (inter.intersecta) {
            pixel.setColor(pri->getColor());
        }
    }
}