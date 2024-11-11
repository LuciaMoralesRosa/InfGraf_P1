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
