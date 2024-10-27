#include <iostream>
#include "../imagen/imagenPPM.hpp"
#include "../imagen/espacioColor/rgb.hpp"
#include "../imagen/espacioColor/hsl.hpp"
#include "../imagen/espacioColor/hsv.hpp"


using namespace std;

// g++ test_imagenPPM.cpp ../imagen/espacioColor/rgb.cpp ../imagen/espacioColor/hsl.cpp ../imagen/espacioColor/hsv.cpp ../imagen/imagenPPM.cpp -o test_ppm

int main(){
    ImagenPPM imagen;
    string ficheroEntrada;
    string ficheroSalida = "ficheroSalidaPPM.ppm";

    cout << "Nombre del fichero: " << endl;

    ficheroEntrada = "forest_path.ppm";

    cout << "Leyendo fichero... " << endl;
    imagen.lecturaFichero(ficheroEntrada); //ok


    cout << "Escribiendo fichero..." << endl;

    //imagen.equalizationClamping(0.5); 
    imagen.equalization();
    imagen.escrituraFichero("ficheroEqualizationClamp.ppm"); //ok



}