#include "formatoPPM.hpp"

FormatoPPM::FormatoPPM(){}

FormatoPPM::FormatoPPM(string f, float mv, string c, int w, int h, float res,
            vector<vector<PixelRGB>> img) : 
            formato(f), maxValor(mv), comentario(c),
            width(w), height(h), resolucionColor(res),
            pixelsImagen(img){}

void FormatoPPM::lecturaFichero(const string& ficheroPPM){
    ifstream fichero(ficheroPPM);
    string lineaAux;

    if(!fichero.is_open()){
        cerr << "No se pudo abrir el archivo: " << ficheroPPM << endl;
        exit(1);
    }

    if(getline(fichero, formato)){
        if(formato != "P3"){
            cerr << "Formato de archivo no valido: " << formato << endl;
            exit(1);
        }
    }

    if(getline(fichero, lineaAux)){

        //Eliminar espacios antes de la linea
        lineaAux.erase(0, lineaAux.find_first_not_of(" \t"));

        if (lineaAux.find("#MAX=") != std::string::npos) {
            // Obtener la posición de "#MAX=" y extraer el valor numérico después de "MAX="
            //string aux = lineaAux.substr(5);
            //maxValor = (float) stoi(aux);
            
            try {
                maxValor = stof(lineaAux.substr(5)); // Convertir a float
            } catch (const invalid_argument &e) {
                cerr << "Error: No se pudo convertir el valor después de #MAX= a número válido.\n";
            } catch (const out_of_range &e) {
                cerr << "Error: El valor después de #MAX= está fuera del rango permitido.\n";
            }
            // Leer la siguiente línea
            if (!getline(fichero, lineaAux)) {
                cerr << "Error: No se pudo leer la siguiente línea después de #MAX=\n";
            }
        }

        // Verificar si la línea contiene un comentario (comienza con "#")
        if (lineaAux.find("#") == 0) {
            // Extraer el comentario después del "#"
            comentario = lineaAux.substr(1); // Extraer todo lo que sigue al "#"
            // Leer la siguiente línea
            if (!getline(fichero, lineaAux)) {
                cerr << "Error: No se pudo leer la siguiente línea después del comentario\n";
            }
        }

    }

    stringstream ss(lineaAux);
    ss >> width >> height;

    // Lee la última línea que contiene el valor maximo de color
    if (getline(fichero, lineaAux)) {
        resolucionColor = stoi(lineaAux);  // Convierte la última línea en entero
    }

    // Reservar espacio para los píxeles
    pixelsImagen.resize(height, vector<PixelRGB>(width));
    
    string r, g, b;
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            fichero >> r >> g >> b;
            pixelsImagen[i][j] = PixelRGB(stof(r) * maxValor / resolucionColor,
                                          stof(g) * maxValor / resolucionColor,
                                          stof(b) * maxValor / resolucionColor);
        }
    }

    fichero.close();
}

void FormatoPPM::escrituraFichero(const string& ficheroPPM){
    ofstream fichero;
    fichero.open(ficheroPPM);

    fichero << formato << endl;
    fichero << "#MAX="+to_string(maxValor) << endl;
    if(comentario != ""){
        fichero << "#" + comentario << endl;
    }
    fichero << to_string(width) + " " + to_string(height) << endl;
    fichero << fixed << setprecision(0) << resolucionColor << endl;

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            PixelRGB pixel = pixelsImagen[i][j];
            fichero << fixed << setprecision(0) << pixel.getRed()*(resolucionColor/maxValor) << " "
                                                << pixel.getGreen()*(resolucionColor/maxValor) << " "
                                                << pixel.getBlue()*(resolucionColor/maxValor) << "     ";
        }
        fichero << endl;
    }
    fichero << endl;
    fichero.close();
}

/*void FormatoPPM::escrituraFichero_255(const string& ficheroPPM){
    ofstream fichero;
    fichero.open(ficheroPPM);

    float resolucion = 255;

    fichero << formato << endl;
    fichero << "#MAX="+to_string(maxValor) << endl;
    if(comentario != ""){
        fichero << "#" + comentario << endl;
    }
    fichero << to_string(width) + " " + to_string(height) << endl;
    fichero << resolucion << endl;

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            PixelRGB pixel = pixelsImagen[i][j];
            fichero << fixed << setprecision(0) 
                    << (pixel.getRed() * 255 /maxValor) << " "
                    << (pixel.getGreen() * 255 / maxValor) << " "
                    << (pixel.getBlue() * 255 / maxValor) << "     ";
        }
        fichero << endl;
    }
    fichero << endl;
    fichero.close();
}
*/

void FormatoPPM::print(){
    cout << formato << endl;
    cout << "#MAX="+to_string(maxValor) << endl;
    if(comentario != ""){
        cout << "#" + comentario << endl;
    }
    cout << to_string(width) + " " + to_string(height) << endl;
    cout << fixed << setprecision(0) <<  resolucionColor << endl;

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            PixelRGB pixel = pixelsImagen[i][j];
            cout << fixed << setprecision(0) << pixel.getRed()*(resolucionColor/maxValor) << " "
                                                << pixel.getGreen()*(resolucionColor/maxValor) << " "
                                                << pixel.getBlue()*(resolucionColor/maxValor);
        cout << "\t";
        }
        cout << endl;
    }
}

string FormatoPPM::getFormato() const {
    return formato;
}

float FormatoPPM::getMaxValor() const {
    return maxValor;
}

string FormatoPPM::getComentario() const {
    return comentario;
}

int FormatoPPM::getWidth() const {
    return width;
}

int FormatoPPM::getHeight() const {
    return height;
}

float FormatoPPM::getResolucionColor() const {
    return resolucionColor;
}

vector<vector<PixelRGB>> FormatoPPM::getPixelsImagen() const {
    return pixelsImagen;
}

// Setters
void FormatoPPM::setFormato(const string& newFormato) {
    formato = newFormato;
}

void FormatoPPM::setMaxValor(float newMaxValor) {
    maxValor = newMaxValor;
}

void FormatoPPM::setComentario(const string& newComentario) {
    comentario = newComentario;
}

void FormatoPPM::setWidth(int newWidth) {
    width = newWidth;
}

void FormatoPPM::setHeight(int newHeight) {
    height = newHeight;
}

void FormatoPPM::setResolucionColor(float newResolucionColor) {
    resolucionColor = newResolucionColor;
}

void FormatoPPM::setPixelsImagen(const vector<vector<PixelRGB>>& newPixelsImagen) {
    pixelsImagen = newPixelsImagen;
}