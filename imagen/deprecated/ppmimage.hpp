#ifndef PPMIMAGE_HPP
#define PPMIMAGE_HPP

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <cstring>
#include <iomanip>
#include "pixelRGB.hpp"

using namespace std;

class PPMImage {
    private:
        string formato;
        string comentario;
        int customMaxValue; //Max
        int width, height;
        int maxColorValue; //colorResolution
    public: 

        vector<vector<PixelRGB>> imagen;

        // Constructores
        // Constructor que lee la imagen PPM
        PPMImage(const string& filename);

        PPMImage(int w, int h, int colorResolution, int max) : 
            imagen(h, vector<PixelRGB>(w)), width(w), height(h),
            maxColorValue(colorResolution), customMaxValue(max), formato("P3"){}

        PPMImage(int w, int h, int colorResolution, int max, string _comentario) : 
            imagen(h, vector<PixelRGB>(w)), width(w), height(h),
            maxColorValue(colorResolution), customMaxValue(max), formato("P3"),
            comentario(_comentario){}

        PPMImage(int w, int h, int colorResolution, int max, string _comentario,
            vector<vector<PixelRGB>> pixels) : 
            imagen(pixels), width(w), height(h),
            maxColorValue(colorResolution), customMaxValue(max), formato("P3"),
            comentario(_comentario){}

        void print() const;
        void writeToFile(const string& filename) const;
        void transformToLDR();

        friend ostream& operator<<(ostream& os, const PixelRGB& p);

};

#endif