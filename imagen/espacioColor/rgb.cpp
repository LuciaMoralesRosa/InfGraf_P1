#include "rgb.hpp"

// Constructores
RGB::RGB(float red, float green, float blue) : r(red), g(green), b(blue) {}

RGB::RGB(const HSV color){
    float h = color.getH();
    float s = color.getS();
    float v = color.getV();

    float red = 0, green = 0, blue = 0;

    float C = v * s; // Chroma
    float H_ = h / 60.0; // H prima
    float X = C * (1 - fabs(fmod(H_, 2) - 1)); // valor intermedio

    float m = v - C;

    if (0 <= H_ && H_ < 1) {
        red = C;
        green = X;
        blue = 0;
    } else if (1 <= H_ && H_ < 2) {
        red = X;
        green = C;
        blue = 0;
    } else if (2 <= H_ && H_ < 3) {
        red = 0;
        green = C;
        blue = X;
    } else if (3 <= H_ && H_ < 4) {
        red = 0;
        green = X;
        blue = C;
    } else if (4 <= H_ && H_ < 5) {
        red = X;
        green = 0;
        blue = C;
    } else if (5 <= H_ && H_ < 6) {
        red = C;
        green = 0;
        blue = X;
    }

    // Ajuste con el valor m y conversión al rango 0-255
    r = static_cast<int>((red + m) * 255);
    g = static_cast<int>((green + m) * 255);
    b = static_cast<int>((blue + m) * 255);
}

RGB::RGB(const HSL color){
    float h = color.getH();
    float s = color.getS();
    float l = color.getL();

    float C = (1 - fabs(2 * l - 1)) * s;   // Chroma
    float X = C * (1 - fabs(fmod(h / 60.0, 2) - 1));
    float m = l - C / 2;

    float red = 0, green = 0, blue = 0;

    if (0 <= h && h < 60) {
        red = C;
        green = X;
        blue = 0;
    } else if (60 <= h && h < 120) {
        red = X;
        green = C;
        blue = 0;
    } else if (120 <= h && h < 180) {
        red = 0;
        green = C;
        blue = X;
    } else if (180 <= h && h < 240) {
        red = 0;
        green = X;
        blue = C;
    } else if (240 <= h && h < 300) {
        red = X;
        green = 0;
        blue = C;
    } else if (300 <= h && h < 360) {
        red = C;
        green = 0;
        blue = X;
    }

    // Convertir a rango [0, 255]
    r = static_cast<int>((red + m) * 255);
    g = static_cast<int>((green + m) * 255);
    b = static_cast<int>((blue + m) * 255);
}


// Implementación del método mostrarColor
void RGB::mostrarColor() const {
    cout << "RGB(" << r << ", " << g << ", " << b << ")" << endl;
}

RGB RGB::normalizar(float maximoImagen){
    return RGB(r/maximoImagen, g/maximoImagen, b/maximoImagen);
}

float RGB::maximo() const{
    return max(r, max(b, g));
}


float RGB::getR() const {
    return r;
}

float RGB::getG() const {
    return g;
}

float RGB::getB() const {
    return b;
}

RGB RGB::clamping(float valor) {
    float nuevaR, nuevaG, nuevaB;
    if(r > valor){
        nuevaR = valor;
    }
    else{
        nuevaR = r;
    }
    if(g > valor){
        nuevaG = valor;
    }
    else{
        nuevaG = g;
    }
    if(b > valor){
        nuevaB = valor;
    }
    else{
        nuevaB = b;
    }
    return RGB(nuevaR, nuevaG, nuevaB);
}

RGB RGB::equalization(float valorMax, float resolucion){
    return RGB(r / valorMax, g / valorMax, b / valorMax);
}

RGB RGB::equalizationClamping(float valorMax, float resolucion, float valor){
    RGB equalizado = equalization(valorMax, resolucion);
    cout << "RGB equalizado: ";
    equalizado.mostrarColor(); 
    return equalizado.clamping(valor);
}

RGB RGB::operator*(const RGB& otro) const{
    return RGB(r*otro.r, g*otro.g, b*otro.b);
}

RGB RGB::operator+(const RGB& otro) const {
    return RGB(r+otro.r, g+otro.g, b+otro.b);
}


RGB RGB::operator*(const float& otro) const {
    return RGB(r*otro, g*otro, b*otro);
}

RGB RGB::operator/(const int& otro) const {
    return RGB(r/otro, g/otro, b/otro);
}


ostream& operator<<(ostream& os, const RGB& color) {
    os << "RGB(" << color.getR() << ", " << color.getG() << ", " << color.getB() << ")";
    return os;
}

bool RGB::esNegro(){
    return (r== 0 && g == 0 & b == 0);
}

