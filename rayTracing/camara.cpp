#include "camara.hpp"

//------------------------------- PRIVADAS -----------------------------------//
void Camara::crearCuadriculaPixeles(){
    Punto3D esquinaIzqSup = Punto3D(l.getx() + origen.getx(),
                                    u.gety() + origen.gety(),
                                    f.getz() + origen.getz());
    
    // Recorremos la cuadrícula en función del tamaño de la imagen
    for (int i = 0; i < tamPlanoImagen[1]; i++) {
        for (int j = 0; j < tamPlanoImagen[0]; j++) {
            // Calculamos la esquina superior izquierda del píxel actual
            Punto3D esquinaSupIzqPixel = Punto3D(
                esquinaIzqSup.getx() + j * tamPixel[0],
                esquinaIzqSup.gety() - i * tamPixel[1],
                esquinaIzqSup.getz()
            );

            // Calculamos la esquina inferior derecha del píxel actual
            Punto3D esquinaInfDerPixel = Punto3D(
                esquinaSupIzqPixel.getx() + tamPixel[0],
                esquinaSupIzqPixel.gety() - tamPixel[1],
                esquinaSupIzqPixel.getz()
            );
            
            // Creamos el objeto Pixel y lo agregamos a la cuadrícula
            Pixel pixel = Pixel(esquinaSupIzqPixel, esquinaInfDerPixel);
            cuadriculaPixeles.push_back(pixel);
        }
    }    
}
//------------------------------- FIN PRIVADAS -------------------------------//


//------------------------------ CONSTRUCTORES -------------------------------//
Camara::Camara(Punto3D origen_val, Direccion u_val, Direccion l_val,
               Direccion f_val, array<int, 2> tam_val){
    origen = origen_val;
    u = u_val;
    l = l_val;
    f = f_val;
    tamPlanoImagen[0] = tam_val[0];
    tamPlanoImagen[1] = tam_val[1];

    if (tam_val[0] == 0 || tam_val[1] == 0) {
        throw std::invalid_argument("El tamaño del plano de imagen no puede ser cero");
    }

    tamPixel[0] = l.modulus()*2 / tam_val[0];
    tamPixel[1] = u.modulus()*2 / tam_val[1];

    cuadriculaPixeles.reserve(tamPlanoImagen[0] * tamPlanoImagen[1]);
    crearCuadriculaPixeles();
}


//--------------------------------- GETTERS ----------------------------------//

vector<Pixel> Camara::getCuadriculaPixeles(){
    return cuadriculaPixeles;
}

int Camara::getTamPlanoImagenBase(){
    return tamPlanoImagen[0];
}

int Camara::getTamPlanoImagenAltura(){
    return tamPlanoImagen[1];
}

float Camara::getTamPixelBase(){
    return tamPixel[0];
}

float Camara::getTamPixelAltura(){
    return tamPixel[1];
}

Punto3D Camara::getOrigen(){
    return origen;
}
