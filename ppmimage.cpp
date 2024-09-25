#include "ppmimage.hpp"

// Constructor que lee la imagen PPM
PPMImage::PPMImage(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "No se pudo abrir el archivo: " << filename << endl;
        exit(1);
    }

    string format;
    string line;

    if (getline(file, line)) {
        format = line;  // Almacena el formato en la variable
    }

    if (format != "P3") {
        cerr << "Formato de archivo no soportado: " << format << endl;
        exit(1);
    }

    // Lee la segunda línea que contiene el "#MAX=436"
    if (getline(file, line)) {
        if (line.find("#MAX=") != std::string::npos) {
            customMaxValue = std::stoi(line.substr(5)); // Extrae el número después de "#MAX="
        }
    }

    while (getline(file, line)) {
        if (line[0] != '#') {
            istringstream iss(line);
            // Lee los valores de ancho y alto
            if (iss >> width >> height) {
                break;
            }
        }
    }

    // Lee la última línea que contiene el valor
    if (getline(file, line)) {
        maxColorValue = stoi(line);  // Convierte la última línea en entero
    }

    // Reservar espacio para los píxeles
    pixels.resize(height, vector<Pixel>(width));

    double ratio = (double)customMaxValue / maxColorValue;

    // Leer los píxeles (r, g, b)
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            int r, g, b;
            file >> r >> g >> b;
            pixels[i][j] = {r*ratio, g*ratio, b*ratio};
        }
    }

    file.close();
}

void PPMImage::print() const {
    cout << "PPM Image: " << width << "x" << height << ", Max Color: " << maxColorValue << endl;
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            cout << "(" << pixels[i][j].r << ", " << pixels[i][j].g << ", " << pixels[i][j].b << ") ";
        }
        cout << endl;
    }
}

void PPMImage::writeToFile(const string& filename) const {
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "No se pudo crear el archivo: " << filename << endl;
        exit(1);
    }

    // Formato
    file << "P3" << endl;

    // MAX
    //file << "#MAX=18.35" << endl; // CAMBIAR

    // Dimensiones
    file << width << " " << height << endl;
    // Valor máximo de color
    file << maxColorValue << endl;

    // Escribir los píxeles (r, g, b)
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            file << pixels[i][j].r << " " << pixels[i][j].g << " " << pixels[i][j].b << " ";
        }
        file << endl;
    }

    file.close();
}

void PPMImage::transformToLDR() {
    double ratio = (double)customMaxValue / maxColorValue;
    cout << "M: " << customMaxValue << endl;
    cout << "C: " << maxColorValue << endl;
    cout << "M/C: " << ratio << endl;
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            pixels[i][j].r = pixels[i][j].r * (ratio);
            pixels[i][j].g = pixels[i][j].g * (ratio);
            pixels[i][j].b = pixels[i][j].b * (ratio);
        }
    }
}