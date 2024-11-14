

#include <iostream>
#include "../geometria/punto3d.hpp"
#include "../geometria/direccion.hpp"
#include "../geometria/primitivasGeometricas/plano.hpp"
#include "../geometria/primitivasGeometricas/esfera.hpp"
#include "../geometria/primitivasGeometricas/esfera.hpp"
#include "../geometria/primitivasGeometricas/primitiva.hpp"
#include "../rayTracing/escenaRayTracing.hpp"
#include "../imagen/espacioColor/rgb.hpp"
#include "../imagen/imagenPPM.hpp"
#include "../rayTracing/camara.hpp"
#include "../rayTracing/luces/fuenteLuz.hpp"


/* Compilacion para escenaRayTracing
g++ test_BSDF.cpp ../rayTracing/BSDF/BSDF.cpp ../rayTracing/luces/fuenteLuz.cpp ../rayTracing/luces/luzPuntual.cpp  ../rayTracing/luces/luzDeArea.cpp ../geometria/punto3d.cpp ../geometria/direccion.cpp ../otros/metodosAuxiliares.cpp ../imagen/espacioColor/rgb.cpp ../geometria/primitivasGeometricas/plano.cpp ../geometria/primitivasGeometricas/esfera.cpp ../imagen/imagenPPM.cpp ../rayTracing/camara.cpp ../imagen/espacioColor/hsv.cpp ../imagen/espacioColor/hsl.cpp ../rayTracing/rayo.cpp ../rayTracing/pixel.cpp ../rayTracing/escenaRayTracing.cpp -o testBSDF
*/

int main(){
    cout << "Test BSDF -----------" << endl;

    cout << "Creacion de bsdf difuso" << endl;
    BSDF test_difuso(RGB(1, 0, 1));

    cout << "Test de evaluacion lambert" << endl;
    RGB color = test_difuso.evaluacion(Direccion(0,0,0), Direccion(0,0,0));
    cout << "El color obtenido tras la evaluacion es: " << color << endl;


    cout << "Finalizacion del test..." << endl;
}

