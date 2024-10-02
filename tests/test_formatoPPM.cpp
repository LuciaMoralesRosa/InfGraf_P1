#include <iostream>
#include "../imagen/formatoPPM.hpp"

using namespace std;

// g++ test_formatoPPM.cpp ../imagen/pixelRGB.cpp ../imagen/formatoPPM.cpp -o test_formatoPPM

int main(){
    FormatoPPM formato;
    string ficheroEntrada;
    string ficheroSalida = "ficheroSalida.ppm";

    cout << "Nombre del fichero: " << endl;
    //cin >> ficheroEntrada;
    ficheroEntrada = "ejemplo.ppm";

    cout << "Leyendo fichero... " << endl;
    formato.lecturaFichero(ficheroEntrada);

    cout << "Imprimiendo fichero..." << endl;
    formato.print();

    cout << "Escribiendo fichero..." << endl;
    formato.escrituraFichero(ficheroSalida);
}