#ifndef PIXELRGB_HPP
#define PIXELRGB_HPP

#include <iostream>

using namespace std;

class PixelRGB {

    private:
        float r;
        float g;
        float b;

    public:

        PixelRGB(float _r, float _g, float _b);

        PixelRGB(): r(0), g(0), b(0){};

        PixelRGB operator+(const PixelRGB& pixel) const;
        PixelRGB operator-(const PixelRGB& pixel) const;
        PixelRGB operator*(const PixelRGB& pixel) const;
        PixelRGB operator/(const PixelRGB& pixel) const;

        PixelRGB operator+(const float valor) const;
        PixelRGB operator-(const float valor) const;
        PixelRGB operator*(const float valor) const;
        PixelRGB operator/(const float valor) const;

        // Getters y setters
        float getRed() const;
        float getGreen() const;
        float getBlue() const;

        void setRed(float valor);  
        void setGreen(float valor);
        void setBlue(float valor);

        friend ostream& operator<<(ostream& os, const PixelRGB& pixel);

};

#endif