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

/// @brief Genera un numero aleatorio entre 0 y 1
/// @return float aleatorio entre 0 y 1
float generacionNumeroAleatorio() {
    // Inicializa el motor y la distribución una sola vez, y los reutiliza en cada llamada.
    static std::mt19937 motor(static_cast<unsigned int>(time(nullptr)));
    static std::uniform_real_distribution<float> distribucion(0.0f, 1.0f);
    
    // Genera y retorna el número aleatorio.
    return distribucion(motor);
}

/*
Direccion muestreoCoseno(const Direccion& u, const Direccion& v, const Direccion& normal, const Punto3D& origen){
    float theta = acos(sqrt(1.0f - generacionNumeroAleatorio()));
    float phi = 2.0f * M_PI * generacionNumeroAleatorio();
    Matriz4x4 T = matrizCambioBase(Coordenada(origen), Coordenada(u), Coordenada(v), Coordenada(normal));
    Direccion wi = T * Direccion(sinf(theta) * cosf(phi), sinf(theta) * sinf(phi), cosf(theta));
    return wi;
}
*/