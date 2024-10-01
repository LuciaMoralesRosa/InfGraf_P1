#include "ppmimage.hpp"

// Constructor que lee la imagen PPM
PPMImage::PPMImage(const string& ficheroPPM) {
    ifstream file(ficheroPPM);
    if (!file.is_open()) {
        cerr << "No se pudo abrir el archivo: " << ficheroPPM << endl;
        exit(1);
    }

    string line;

    // La primera linea del fichero contiene el formato
    if (getline(file, formato)) {
        if (formato != "P3") {
            cerr << "Formato de archivo no soportado: " << formato << endl;
            exit(1);
        }
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
        else{
            comentario = line;
        }
    }

    // Lee la última línea que contiene el valor maximo de color
    if (getline(file, line)) {
        maxColorValue = stoi(line);  // Convierte la última línea en entero
    }

    // Reservar espacio para los píxeles
    imagen.resize(height, vector<PixelRGB>(width));

    double ratio = (double)customMaxValue / maxColorValue;

    // Leer los píxeles (r, g, b)
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            string r, g, b;
            file >> r >> g >> b;
            //imagen[i][j] = {r*ratio, g*ratio, b*ratio};
            imagen[i][j] = PixelRGB(stof(r)*maxColorValue/customMaxValue,
                                     stof(g)*maxColorValue/customMaxValue,
                                     stof(b)*maxColorValue/customMaxValue);
        }
    }

    file.close();
}

void PPMImage::print() const {
    cout << "PPM Image: " << width << "x" << height << ", Max Color: " << maxColorValue << endl;
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            cout << "(" << imagen[i][j].getRed() << ", " << imagen[i][j].getGreen() << ", " << imagen[i][j].getBlue() << ") ";
        }
        cout << endl;
    }
}

void PPMImage::writeToFile(const string& ficheroPPM) const {
    ofstream file(ficheroPPM);
    if (!file.is_open()) {
        cerr << "No se pudo crear el archivo: " << ficheroPPM << endl;
        exit(1);
    }

    // Formato
    file << "P3" << endl;

    // MAX
    //file << "#MAX=18.35" << endl; // CAMBIAR
    file << "#MAX="+to_string((int)customMaxValue) << endl;

    if(comentario != ""){
        file << comentario << endl;
    }

    // Dimensiones
    file << to_string(width) << " " << to_string(height) << endl;
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