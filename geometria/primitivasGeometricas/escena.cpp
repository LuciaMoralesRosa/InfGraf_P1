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
        }
    }
}

    //for(const auto& pri : primitivas){  
    //    cout << "\tintersectando rayo con primitiva: " << pri->tipo << endl;      
    //    Interseccion inter = pri->interseccionRayo(rayo);
    //    if (inter.intersecta) {
    //        pixel.setColor(pri->getColor());
    //    }
    //}
RGB Escena::intersectarRayo(RGB colorPixel, Rayo rayo){

    vector<Primitiva*> primitivasIntersectadas;
    vector<float> distanciasPrimitivas;

    //Recorro todas las primitivas de mi escena y si intersecta con el rayo, la guardo
    for(const auto& pri : primitivas){  
        Interseccion inter = pri->interseccionRayo(rayo);
        if(inter.intersecta){
            primitivasIntersectadas.push_back(pri);
            float min = calcularMIN(inter.distancia);
            distanciasPrimitivas.push_back(min);
        }
    }

    //Tengo una lista de primitivas intersectadas por el rayo
    // Hay que ver que primitiva esta por delante
    if(primitivasIntersectadas.empty()){
        return colorPixel;
    }

    Primitiva* primitivaVisible;
    //Obtengo la distancia a la que se encuentra la primera primitiva (la visible)
    float minimaDistancia = calcularMIN(distanciasPrimitivas);

    // Recorro todo el vector de primitivas hasta que encuentro la que tiene el valor de distancia minimo
    for(int i = 0; i < primitivasIntersectadas.size(); i++){
        if(distanciasPrimitivas[i] == minimaDistancia){
            // Cuando la encuentro, la guardo
            primitivaVisible = primitivasIntersectadas[i];
            break;
        }
    }
    // Devulevo el color de la primitiva intersectada
    RGB resultado(primitivaVisible->getColor().getR(), primitivaVisible->getColor().getG(), primitivaVisible->getColor().getB());
    return resultado;
}