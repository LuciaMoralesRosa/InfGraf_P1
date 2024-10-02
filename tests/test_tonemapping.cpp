#include <iostream>
#include "../imagen/formatoPPM.hpp"
#include "../imagen/toneMapping.hpp"


using namespace std;

// g++ test_tonemapping.cpp ../imagen/pixelRGB.cpp ../imagen/formatoPPM.cpp ../imagen/toneMapping.cpp -o test_tm

int main(){
    FormatoPPM imagenPPM;
    string ficheroEntrada = "ejemplo.ppm";
    imagenPPM.lecturaFichero(ficheroEntrada);

    
    FormatoPPM nuevaImagenPPM;
    nuevaImagenPPM = ToneMapping::corte(imagenPPM, 255);
    cout << endl << "Corte: " << endl;
    nuevaImagenPPM.print();

    nuevaImagenPPM = ToneMapping::lineal(imagenPPM);
    cout << endl << "Lineal: " << endl;
    nuevaImagenPPM.print();

    nuevaImagenPPM = ToneMapping::linealCorte(imagenPPM, 255);
    cout << endl << "Corte - Lineal: " << endl;
    nuevaImagenPPM.print();

    nuevaImagenPPM.escrituraFichero("ficheroSalida.ppm");

}