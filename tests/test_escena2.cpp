

#include <iostream>
#include "../geometria/punto3d.hpp"
#include "../geometria/direccion.hpp"
#include "../geometria/primitivasGeometricas/plano.hpp"
#include "../geometria/primitivasGeometricas/esfera.hpp"
#include "../geometria/primitivasGeometricas/esfera.hpp"
#include "../geometria/primitivasGeometricas/primitiva.hpp"
#include "../rayTracing/escena.hpp"
#include "../imagen/espacioColor/rgb.hpp"
#include "../imagen/imagenPPM.hpp"
#include "../rayTracing/camara.hpp"
#include "../rayTracing/luces/fuenteLuz.hpp"


/* Compilacion:
g++ test_escena.cpp ../rayTracing/BSDF/BSDF.cpp ../rayTracing/luces/fuenteLuz.cpp ../rayTracing/luces/luzDeArea.cpp ../geometria/punto3d.cpp ../geometria/direccion.cpp ../otros/metodosAuxiliares.cpp ../imagen/espacioColor/rgb.cpp ../geometria/primitivasGeometricas/plano.cpp ../geometria/primitivasGeometricas/esfera.cpp ../imagen/imagenPPM.cpp ../rayTracing/camara.cpp ../imagen/espacioColor/hsv.cpp ../imagen/espacioColor/hsl.cpp ../rayTracing/rayo.cpp ../rayTracing/pixel.cpp ../rayTracing/escena.cpp -o testEscena
*/


int main(){

    cout << "Creacion de primitivas..." << endl;
    RGB rojo(1,0,0);
    RGB amarillo(1,1,0);
    RGB verde(0,1,0);
    RGB cian(0,1,1);
    RGB azul(0,0,1);
    RGB magenta(1,0,1);
    RGB rosa(1,0.5,0.5);
    RGB azulado(0.5,0.5,1);
    Material difuso(1,0,0);
    Material especular(0,1,0);
    Material refractor(0,0,1);
    Material plastico(0.5,0.5,0);
    
    Plano planoizq  (Direccion( 1,  0,  0), 1, Textura(rojo, difuso));
    Plano planoder  (Direccion(-1,  0,  0), 1, Textura(amarillo, difuso));
    Plano planosuelo(Direccion( 0,  1,  0), 1, Textura(magenta, difuso));
    Plano planotecho(Direccion( 0, -1,  0), 1, Textura(cian, difuso));
    Plano planoatras(Direccion( 0,  0, -1), 1, Textura(verde, difuso));

    FuenteLuz luz(Punto3D(0, 0.5, 0), RGB(1, 1, 1));

    Esfera esfera1(Punto3D(-0.2, -0.7, 0.25), 0.3, Textura(rosa, difuso));
    Esfera esfera2(Punto3D(0.0, -0.7, -0.25), 0.3, Textura(azulado, difuso));

    cout << "Creacion de la camara..." << endl;
    Camara camara(Punto3D(0,0,-3.5), Direccion(0,1,0), Direccion(-1,0,0), Direccion(0,0,3));

    cout << "Creacion de la escena..." << endl;

    vector<Primitiva*> primitivas;
    vector<FuenteLuz*> luces;
    
    luces.push_back(&luz);
    primitivas.push_back(&esfera1);
    //primitivas.push_back(&esfera2);
    //primitivas.push_back(&planoizq);
    //primitivas.push_back(&planoder);
    //primitivas.push_back(&planosuelo);
    //primitivas.push_back(&planotecho);
    //primitivas.push_back(&planoatras);
    
    Escena escena = Escena(primitivas, camara, luces);

    cout << "Lanzando rayos..." << endl;
    escena.lanzarRayosDesdeCamara(1);

    // Esto sabemos que funciona porque es igual que el que habia en la camara
    cout << "Creando imagen..." << endl;
    ImagenPPM imagenGenerada = escena.crearImagenPPM();

    cout << "Escribiendo fichero..." << endl;
    imagenGenerada.escrituraFichero("EscenaTest.ppm");
    cout << " -- Terminacion correcta del test -- " << endl;
}