
#include <iostream>
#include "../geometria/punto3d.hpp"
#include "../geometria/direccion.hpp"
#include "../geometria/primitivasGeometricas/plano.hpp"
#include "../geometria/primitivasGeometricas/esfera.hpp"
#include "../geometria/primitivasGeometricas/escena.hpp"
#include "../imagen/espacioColor/rgb.hpp"
#include "../imagen/imagenPPM.hpp"
#include "../rayTracing/camara.hpp"

//g++ test_camara.cpp ../geometria/punto3d.cpp ../geometria/direccion.cpp ../imagen/espacioColor/rgb.cpp ../geometria/primitivasGeometricas/plano.cpp ../geometria/primitivasGeometricas/esfera.cpp ../geometria/primitivasGeometricas/escena.cpp ../imagen/imagenPPM.cpp ../rayTracing/camara.cpp -o testCamara
// g++ test_camara.cpp ../geometria/punto3d.cpp ../geometria/direccion.cpp ../imagen/espacioColor/rgb.cpp ../geometria/primitivasGeometricas/plano.cpp ../geometria/primitivasGeometricas/esfera.cpp ../geometria/primitivasGeometricas/escena.cpp ../imagen/imagenPPM.cpp ../rayTracing/camara.cpp ../imagen/espacioColor/hsv.cpp ../imagen/espacioColor/hsl.cpp ../rayTracing/rayo.cpp ../rayTracing/pixel.cpp -o testCamara



int main(){

    cout << "Creacion de primitivas..." << endl;
    Plano planoizq(Punto3D(1, 0, 0), 1, RGB(1,0,0));
    Plano planoder(Punto3D(-1, 0, 0), 1, RGB(0,1,0));
    Plano planosuelo(Punto3D(0, 1, 0), 1, RGB(1,1,1));
    Plano planotecho(Punto3D(0, -1, 0), 1, RGB(1,1,1));
    Plano planoatras(Punto3D(0, 0, -1), 1, RGB(1,1,1));

    Esfera esfera1(Punto3D(-0.5, -0.7, 0.25), 0.3, RGB(1,0.5,0.5));
    Esfera esfera2(Punto3D(0.5, -0.7, -0.25), 0.3, RGB(0.5,0.5,1));

    cout << "Creacion de la camara..." << endl;
    Camara camara(Punto3D(0,0,3.5), Direccion(0,1,0), Direccion(-1,0,0), Direccion(0,0,3));

    cout << "Creacion de la escena..." << endl;
    Escena escena;
    escena.anyadirPrimitiva(&esfera1);
    escena.anyadirPrimitiva(&esfera2);
    escena.anyadirPrimitiva(&planoizq);
    escena.anyadirPrimitiva(&planoder);
    escena.anyadirPrimitiva(&planosuelo);
    escena.anyadirPrimitiva(&planotecho);
    escena.anyadirPrimitiva(&planoatras);

    cout << "Generando imagen..." << endl;
    camara.generarImagen(256,256);

    cout << "Lanzando rayos..." << endl;
    camara.lanzarRayos(64);

    cout << "Creando imagen..." << endl;
    ImagenPPM imagenGenerada = camara.crearImagenPPM();
    cout << imagenGenerada;
    //imagenGenerada.escrituraFichero("FicheroCamaraTest.ppm");

}