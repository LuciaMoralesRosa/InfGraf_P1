#ifndef FORMATOPPM_HPP
#define FORMATOPPM_HPP

#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <cstring>
#include <iomanip>

#include "pixelRGB.hpp"

using namespace std;

/**
 * Estructura de un fichero PPM
 * 
 * P3                           // Formato
 * #MAX=MaxValue                // Maximo valor de color
 * # comentario                 // Comentario opcional
 * w h                          // Anchura y altura
 * resolucionColor              // Resolucion dada del color
 */

class FormatoPPM{

    private:
        string formato;
        float maxValor;
        string comentario;
        int width, height;
        float resolucionColor;
        
    public:
        
        vector<vector<PixelRGB>> pixelsImagen;

        // Constructores
        FormatoPPM();

        FormatoPPM(vector<vector<PixelRGB>> img);

        FormatoPPM(float mv, int w, int h, float res) : 
            formato("P3"), maxValor(mv), comentario(""),
            width(w), height(h), resolucionColor(res),
            pixelsImagen(h, vector<PixelRGB>(w)) {}
        
        FormatoPPM(float mv, int w, int h, float res, string c) : 
            formato("P3"), maxValor(mv), comentario(c),
            width(w), height(h), resolucionColor(res),
            pixelsImagen(h, vector<PixelRGB>(w)) {}

        FormatoPPM(int w, int h, float res) : 
            formato("P3"), maxValor(), comentario(""),
            width(w), height(h), resolucionColor(res),
            pixelsImagen(h, vector<PixelRGB>(w)) {}
    
        FormatoPPM(string f, float mv, string c, int w, int h, float res,
            vector<vector<PixelRGB>> img);

        FormatoPPM lecturaFichero(const string& ficheroPPM);
        void escrituraFichero(const string& ficheroPPM);
        void FormatoPPM::escrituraFichero_255(const string& ficheroPPM);


        // Getters
        string getFormato() const;
        float getMaxValor() const;
        string getComentario() const;
        int getWidth() const;
        int getHeight() const;
        float getResolucionColor() const;
        vector<vector<PixelRGB>> getPixelsImagen() const;

        // Setters
        void setFormato(const string& newFormato);
        void setMaxValor(float newMaxValor);
        void setComentario(const string& newComentario);
        void setWidth(int newWidth);
        void setHeight(int newHeight);
        void setResolucionColor(float newResolucionColor);
        void setPixelsImagen(const vector<vector<PixelRGB>>& newPixelsImagen);


};

#endif