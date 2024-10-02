#include <iostream>
#include "../imagen/formatoPPM.hpp"
#include "../imagen/toneMapping.hpp"


using namespace std;

// g++ test_tonemapping.cpp ../imagen/pixelRGB.cpp ../imagen/formatoPPM.cpp ../imagen/toneMapping.cpp -o test_tm


void test_corte(FormatoPPM imagen, string ficheroEntrada){
    FormatoPPM nuevaImagenPPM;
    nuevaImagenPPM = ToneMapping::corte(imagen, 150);
    nuevaImagenPPM.escrituraFichero("imagenesGeneradasTest/" + ficheroEntrada + "_corte" + ".ppm");
}

void test_lineal(FormatoPPM imagen, string ficheroEntrada){
    FormatoPPM nuevaImagenPPM;
    nuevaImagenPPM = ToneMapping::lineal(imagen);
    nuevaImagenPPM.escrituraFichero("imagenesGeneradasTest/" + ficheroEntrada + "_lineal" + ".ppm");
}


void test_linealCorte(FormatoPPM imagen, string ficheroEntrada){
    FormatoPPM nuevaImagenPPM;
    nuevaImagenPPM = ToneMapping::linealCorte(imagen, 255);
    nuevaImagenPPM.escrituraFichero("imagenesGeneradasTest/" + ficheroEntrada + "_linealCorte" + ".ppm");
}


void test_gamma(FormatoPPM imagen, string ficheroEntrada){
    FormatoPPM nuevaImagenPPM;
    nuevaImagenPPM = ToneMapping::gamma(imagen, 10);
    nuevaImagenPPM.escrituraFichero("imagenesGeneradasTest/" + ficheroEntrada + "_gamma" + ".ppm");
}

void test_gammaCorte(FormatoPPM imagen, string ficheroEntrada){
    FormatoPPM nuevaImagenPPM;
    nuevaImagenPPM = ToneMapping::gammaCorte(imagen, 20, 120);
    nuevaImagenPPM.escrituraFichero("imagenesGeneradasTest/" + ficheroEntrada + "_gammaCorte" + ".ppm");
}


void test_r(FormatoPPM imagen, string ficheroEntrada){
    FormatoPPM nuevaImagenPPM;
    nuevaImagenPPM = ToneMapping::reinhard(imagen);
    nuevaImagenPPM.escrituraFichero("imagenesGeneradasTest/" + ficheroEntrada + "_reinhard" + ".ppm");
}

void test_rCorte(FormatoPPM imagen, string ficheroEntrada){
    FormatoPPM nuevaImagenPPM;
    nuevaImagenPPM = ToneMapping::reinhardCorte(imagen,160);
    nuevaImagenPPM.escrituraFichero("imagenesGeneradasTest/" + ficheroEntrada + "_reinhardCorte" + ".ppm");
}



int main(){
    FormatoPPM imagenPPM;
    string ficheroEntrada = "forest_path";
    imagenPPM.lecturaFichero(ficheroEntrada + ".ppm");

    
    //test_corte(imagenPPM, ficheroEntrada);
    //test_lineal(imagenPPM, ficheroEntrada);
    //test_linealCorte(imagenPPM, ficheroEntrada);
    //test_gamma(imagenPPM, ficheroEntrada);
    //test_gammaCorte(imagenPPM, ficheroEntrada);
    test_r(imagenPPM, ficheroEntrada);
    test_rCorte(imagenPPM, ficheroEntrada);
}