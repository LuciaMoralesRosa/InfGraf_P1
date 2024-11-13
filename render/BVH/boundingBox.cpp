#include "boundingBox.hpp"

Punto3D BoundingBox::getPuntoMin(){
    return puntoMin;
}

Punto3D BoundingBox::getPuntoMax(){
    return puntoMax;
}

void BoundingBox::growToInclude(BoundingBox box){
    puntoMin = puntoMin.restarPuntos(box.puntoMin);
    puntoMax = puntoMax.restarPuntos(box.puntoMax);
    
    extend = puntoMax.restarPuntos(puntoMin);
}

Punto3D BoundingBox::obtenerCentro() {
    return (puntoMax + puntoMin) * 0.5f; 
}

//tnear -> distancia a la que el rayo entra en la caja
//tfar -> distancia a la que el rayo sale de la caja
bool BoundingBox::intersecta(Rayo rayo, float tentrada, float tsalida){
    float tmin = (puntoMin.getx() - rayo.getOrigen().getx()) * rayo.getInverso().getx();
    float tmax = (puntoMax.getx() - rayo.getOrigen().getx()) * rayo.getInverso().getx();

    if(tmin > tmax) {
        float aux = tmin;
        tmax = tmin;
        tmin = aux;
    }

    
}