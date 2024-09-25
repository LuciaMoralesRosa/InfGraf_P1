#ifndef PPMIMAGE_HPP
#define PPMIMAGE_HPP

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

struct Pixel {
    int r, g, b;
};

class PPMImage {
    public: 
        int width, height, maxColorValue, customMaxValue;
        vector<vector<Pixel>> pixels;

        // Constructor que lee la imagen PPM
        PPMImage(const string& filename);

        void print() const;
        void writeToFile(const string& filename) const;
        void transformToLDR();
};

#endif