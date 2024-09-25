#include "ppmimage.hpp"

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

// g++ ppmtest.cpp ppmimage.cpp -o test

int main() {
    string inputFilename, outputFilename;

    cout << "Introduce el nombre del archivo PPM de entrada: ";
    cin >> inputFilename;

    // Crear un objeto de la clase PPMImage que lea el archivo
    PPMImage image(inputFilename);

    // Imprimir los valores RGB en consola
    //image.print();

    // Modificar la imagen (en este caso, invertir los colores)
    //image.transformToLDR();

    image.print();

    // Solicitar nombre del archivo de salida
    cout << "Introduce el nombre del archivo PPM de salida: ";
    cin >> outputFilename;

    // Escribir la imagen modificada en el archivo de salida
    //image.writeToFile(outputFilename);

    cout << "Imagen modificada guardada en " << outputFilename << endl;

    return 0;
}