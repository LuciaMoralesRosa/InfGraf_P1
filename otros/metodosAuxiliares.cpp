#include "metodosAuxiliares.hpp"

float calcularMAX(vector<float> vector){
    float max = vector[0];
    for(float f: vector){
        if(f > max){
            max = f;
        }
    }
    return max;
}

float calcularMIN(vector<float> vector){
    float min = vector[0];
    for(float f: vector){
        if(f < min){
            min = f;
        }
    }
    return min;
}

float calcularMedia(vector<float> vector){
    float suma = 0;
    for(float f: vector){
        suma = suma + f;
    }
    return suma/vector.size();
}

bool algunPuntoEsMenor(vector<float> vector, float distancia){
    for(int distanciaPunto = 0; distanciaPunto < vector.size(); distanciaPunto++){
        if(distanciaPunto <= distancia) {
            return true;
        }
    }
    return false;
}


Punto3D sumaPuntoDireccion(Punto3D punto, Direccion direccion){
    float x = punto.getx() + direccion.getx();
    float y = punto.gety() + direccion.gety();
    float z = punto.getz() + direccion.getz();

    return Punto3D(x, y, z);    
}
float generacionNumeroAleatorio() {
    // Inicializa el motor y la distribución una sola vez, y los reutiliza en cada llamada.
    static std::mt19937 motor(static_cast<unsigned int>(time(nullptr)));
    static std::uniform_real_distribution<float> distribucion(0.0, 1.0);
    
    // Genera y retorna el número aleatorio.
    return distribucion(motor);
}