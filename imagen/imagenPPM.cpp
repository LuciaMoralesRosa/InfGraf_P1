#include "imagenPPM.hpp"


// Constructores

ImagenPPM::ImagenPPM(string fichero, tipoEspacioColor tipoEspacio){
    imagenDesdeFichero(fichero);
    
    switch (tipoEspacio) {
    case formatoHSL:
        convertirHSL();
        break;
    case formatoHSV:
        convertirHSV();
        break;    
    default:
        break;
    }
}

ImagenPPM::ImagenPPM(ImagenPPM imagen, tipoEspacioColor tipoEspacio):
        espacioColor(tipoEspacio) {
    formato = imagen.formato;
    comentario = imagen.comentario;
    altura = imagen.altura;
    base = imagen.base;
    valorMax = imagen.valorMax;
    resolucion = imagen.resolucion;
    espacioColor = tipoEspacio;
    arrayPixeles = imagen.arrayPixeles;
    
    switch (tipoEspacio) {
    case formatoHSL:
        convertirHSL();
        break;
    case formatoHSV:
        convertirHSV();
        break;
    case formatoRGB:
        convertirRGB();
        break;    
    default:
        break;
    }
}

ImagenPPM::ImagenPPM(string f, float vmax, string c, int b, int a, float res, tipoEspacioColor espacio, vector<RGB> pixeles){
    formato = f;
    valorMax = vmax;
    comentario = c;
    base = b;
    altura = a;
    resolucion = res;
    espacioColor = espacio;
    for(auto p : pixeles){
        arrayPixeles.push_back(&p);
    }
}

void ImagenPPM::imagenDesdeFichero(string ficheroPPM){
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
            try {
                valorMax = stof(lineaAux.substr(5)); // Convertir a float
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
    ss >> base >> altura;

    // Lee la última línea que contiene el valor maximo de color
    if (getline(fichero, lineaAux)) {
        resolucion = stoi(lineaAux);  // Convierte la última línea en entero
    }

    // Reservar espacio para los píxeles
    arrayPixeles.resize(base*altura);

    string r, g, b;

    int k = 0;
    for(int i = 0; i < altura; i++){
        for(int j = 0; j < base; j++){
            fichero >> r >> g >> b;
            // Los pixeles tendran valor [0, MAX]
            arrayPixeles[k] = new RGB(stof(r) * valorMax / resolucion,
                                      stof(g) * valorMax / resolucion,
                                      stof(b) * valorMax / resolucion);
            k++;
        }
    }
}

void ImagenPPM::normalizar(){
    if(espacioColor == formatoRGB){
        for(auto pixel : arrayPixeles){
            RGB* aux = dynamic_cast<RGB*>(pixel);
            RGB aux2 = aux->normalizar(valorMax);
            pixel = new RGB(aux2.getR(), aux2.getG(), aux2.getB());
            delete aux;
        }
    }
}

ImagenPPM ImagenPPM::normalizarImagen(ImagenPPM imagen){
    ImagenPPM retorno = imagen;
    retorno.normalizar();
    return retorno;
}

void ImagenPPM::convertirHSL(){
    normalizar();
    switch(espacioColor){
        case formatoHSV:
            for(auto pixel : arrayPixeles){
                HSV* aux = dynamic_cast<HSV*>(pixel); //Casteo el EspacioColor* a un tipo VSH*
                pixel = new HSL(*aux);
                delete aux;
            }
            break;
        case formatoRGB:
            for(auto pixel : arrayPixeles){
                EspacioColor* aux = pixel;
                pixel = new HSL(*dynamic_cast<RGB*>(aux));
                delete aux;
            }
            break;
        default:
            break;
    }
    espacioColor = formatoHSL;
}

void ImagenPPM::convertirHSV(){
    normalizar();
    switch(espacioColor){
        case formatoHSL:
            for(auto pixel : arrayPixeles){
                EspacioColor* aux = pixel;
                pixel = new HSV(*dynamic_cast<HSL*>(aux));
                delete aux;
            }
            break;
        case formatoRGB:
            for(auto pixel : arrayPixeles){
                EspacioColor* aux = pixel;
                pixel = new HSV(*dynamic_cast<RGB*>(aux));
                delete aux;
            }
            break;
        default:
            break;
    }
    espacioColor = formatoHSV;
}

void ImagenPPM::convertirRGB(){
    switch(espacioColor){
        case formatoHSV:
            for(auto pixel : arrayPixeles){
                EspacioColor* aux = pixel;
                pixel = new RGB(*dynamic_cast<HSV*>(aux));
                delete aux;
            }
            break;
        case formatoHSL:
            for(auto pixel : arrayPixeles){
                EspacioColor* aux = pixel;
                pixel = new RGB(*dynamic_cast<HSL*>(aux));
                delete aux;
            }
            break;
        default:
            break;
    }
    espacioColor = formatoRGB;
}

ImagenPPM ImagenPPM::lecturaFichero(string fichero){
    espacioColor = formatoRGB;
    imagenDesdeFichero(fichero);
}

void ImagenPPM::escrituraFichero(string ficheroPPM){
    if(espacioColor != formatoRGB){
        convertirRGB();
    }
    ofstream fichero;
    fichero.open(ficheroPPM);

    fichero << formato << endl;
    fichero << "#MAX=" + to_string(valorMax) << endl;
    if(comentario != ""){
        fichero << "#" + comentario << endl;
    }
    fichero << to_string(base) + " " + to_string(altura) << endl;
    fichero << fixed << setprecision(0) << resolucion << endl;

    int k = 0;
    for (int i = 0; i < altura; ++i) {
        for (int j = 0; j < base; ++j) {
            RGB* pixel = dynamic_cast<RGB*>(arrayPixeles[k]); 
            k++;
            fichero << fixed << setprecision(0) << pixel->getR() * resolucion / valorMax << " "
                                                << pixel->getG() * resolucion / valorMax << " "
                                                << pixel->getB() * resolucion / valorMax << "     ";
        }
        fichero << endl;
    }
    fichero << endl;
    fichero.close();

}


// tonemapping
ImagenPPM ImagenPPM::clamping(float valor){
    vector<EspacioColor*> nuevoArrayPixeles;
    switch (espacioColor){
    case formatoRGB: //RGB
        // Para cada pixel, hago un corte con el valor parametro y reajusto el nuevo maximo de la imagen
        for(auto pixel : arrayPixeles){
            RGB* aux = dynamic_cast<RGB*>(pixel); 
            RGB nuevoPixel = aux->clamping(valor);
            EspacioColor* p = new RGB(nuevoPixel.getR(), nuevoPixel.getG(), nuevoPixel.getB());
            nuevoArrayPixeles.push_back(p);
            delete aux;
        }
        arrayPixeles = nuevoArrayPixeles;
        valorMax = valor; //El valor maximo ahora se ha truncado al valor dado
        resolucion = valor * 255; // Se actualiza la resolucion de la imagen
        break;
    
    default:
        break;
    }
}

ImagenPPM ImagenPPM::equalization(){
    float maxCalculado = 0.0;
    switch (espacioColor){
    case formatoRGB: //RGB
        // Para cada pixel, hago un corte con el valor parametro y reajusto el nuevo maximo de la imagen
        for(auto pixel : arrayPixeles){
            RGB* aux = dynamic_cast<RGB*>(pixel); 
            RGB nuevoPixel = aux->equalization(valorMax, resolucion);
            pixel = new RGB(nuevoPixel.getR(), nuevoPixel.getG(), nuevoPixel.getB());
            maxCalculado = max(maxCalculado, max(nuevoPixel.getR(), max(nuevoPixel.getG(),nuevoPixel.getB())));
            delete aux;
        }
        valorMax = maxCalculado;
        resolucion = maxCalculado;
        break;
    
    default:
        break;
    }
}

ImagenPPM ImagenPPM::equalizationClamping(float valor){
    float maxCalculado = 0.0;
    switch (espacioColor){
    case formatoRGB: //RGB
        // Para cada pixel, hago un corte con el valor parametro y reajusto el nuevo maximo de la imagen
        for(auto pixel : arrayPixeles){
            RGB* aux = dynamic_cast<RGB*>(pixel); 
            RGB nuevoPixel = aux->equalizationClamping(valorMax, resolucion, valor);
            pixel = new RGB(nuevoPixel.getR(), nuevoPixel.getG(), nuevoPixel.getB());
            maxCalculado = max(maxCalculado, max(nuevoPixel.getR(), max(nuevoPixel.getG(),nuevoPixel.getB())));
            delete aux;
        }
        if (maxCalculado > valor){
            valorMax = valor;
        }
        else {
            valorMax = maxCalculado;
            resolucion = maxCalculado;
        }
        break;
    
    default:
        break;
    }
}