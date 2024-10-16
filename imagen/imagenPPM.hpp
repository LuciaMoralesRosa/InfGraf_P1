#ifndef IMAGENPPM_HPP
#define IMAGENPPM_HPP

#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <cstring>
#include <iomanip>

#include "tipoEspacioColor.hpp"
#include "valorNoValido.hpp"
#include "rgb.hpp"

using namespace std;

class ImagenPPM{
    private:
    string formato;
    float valorMax;
    string comentario;
    int base;
    int altura;
    float resolucion;
    tipoEspacioColor espacioColor;

    vector<EspacioColor*> arrayPixeles;

    void normalizar();
    void imagenDesdeFichero(string fichero);


public:
    // Constructores
    ImagenPPM() : 
        formato(""), valorMax(0), comentario(""), base(0), altura(0),
        resolucion(0), espacioColor(formatoRGB), arrayPixeles() {}
        
    ImagenPPM(ImagenPPM imagen, tipoEspacioColor tipoEspacio);
    ImagenPPM(string fichero, tipoEspacioColor espacio = formatoRGB) :
        espacioColor(espacio) {} //Si no es RGB, hay que normalizar primero

    
    // Conversiones de espacio de color
    void convertirHSL();
    void convertirRGB();
    void convertirHSV();


    ImagenPPM normalizarImagen(ImagenPPM imagen);
    ImagenPPM lecturaFichero(string fichero);
    void escrituraFichero(string fichero);
    void escrituraFicheroPNG();

    //ToneMapping
    ImagenPPM clamping(float corte = 1);
    ImagenPPM equalization();
    ImagenPPM equalizationClamping(float corte = 1);

    friend ostream& operator<<(ostream& os, const ImagenPPM& imagen);


};

#endif