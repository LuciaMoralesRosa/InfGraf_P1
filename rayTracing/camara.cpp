#include "camara.hpp"

Camara::Camara(Punto3D origen_val, Direccion u_val, Direccion l_val, Direccion f_val, array<int, 2> tam_val){
    origen = origen_val;
    u = u_val;
    l = l_val;
    f = f_val;
    tamanyoPlano[0] = tam_val[0];
    tamanyoPlano[1] = tam_val[1];
}

vector<Pixel> Camara::generarPixeles() {
    // Tengo que añadir operaciones entre punto y dirección o utilizar coordenadas homogeneas
    // Si no esto queda larguisimo
    // Recorre de arriba a la izquierda a abajo a la derecha
    vector<Pixel> pixeles;

    // Coordenadas de la esquina de arriba a la izquierda
    float x_esquina = origen.getx() + f.getx() + u.getx() + l.getx();
    float y_esquina = origen.gety() + f.gety() + u.gety() + l.gety();
    float z_esquina = origen.getz() + f.getz() + u.getz() + l.getz();
    // Tamaño del pixel en dirección down
    float tam_pixel_u_x = u.getx()/tamanyoPlano[1];
    float tam_pixel_u_y = u.gety()/tamanyoPlano[1];
    float tam_pixel_u_z = u.getz()/tamanyoPlano[1];
    //cout << "tamanyoPlano de pixel down: (" << tam_pixel_u_x << "," << tam_pixel_u_y << "," << tam_pixel_u_z << ")" << endl;
    // Tamaño del pixel en dirección right
    float tam_pixel_l_x = l.getx()/tamanyoPlano[0];
    float tam_pixel_l_y = l.gety()/tamanyoPlano[0];
    float tam_pixel_l_z = l.getz()/tamanyoPlano[0];
    //cout << "tamanyoPlano de pixel right: (" << tam_pixel_l_x << "," << tam_pixel_l_y << "," << tam_pixel_l_z << ")" << endl;

    for (int j = tamanyoPlano[1]; j > 0; j--) {
        for (int i = tamanyoPlano[0]; i > 0; i--) {
            //    Esquina arr-izq - despl abajo j pixeles + tam pixel     - despl der i pixeles + tam pixel
            // nota: + tam pixel para centrar punto a mitad del pixel, cambiar cuando se envien multiples rayos
            Punto3D p(  x_esquina - (tam_pixel_u_x*j*2) + (tam_pixel_u_x) - (tam_pixel_l_x*i*2) + (tam_pixel_l_x), 
                        y_esquina - (tam_pixel_u_y*j*2) + (tam_pixel_u_y) - (tam_pixel_l_y*i*2) + (tam_pixel_l_y), 
                        z_esquina - (tam_pixel_u_z*j*2) + (tam_pixel_u_z) - (tam_pixel_l_z*i*2) + (tam_pixel_l_z));
            Punto3D p2(  x_esquina - (tam_pixel_u_x*j*2) + (tam_pixel_u_x*2) - (tam_pixel_l_x*i*2) + (tam_pixel_l_x*2), 
                        y_esquina - (tam_pixel_u_y*j*2) + (tam_pixel_u_y*2) - (tam_pixel_l_y*i*2) + (tam_pixel_l_y*2), 
                        z_esquina - (tam_pixel_u_z*j*2) + (tam_pixel_u_z*2) - (tam_pixel_l_z*i*2) + (tam_pixel_l_z*2));
            //cout << ": " << p << endl;
            Pixel pix(p, p2);
            pix.generarRayoMitad(origen);
            pixeles.push_back(pix);
        }
    }
    return pixeles;
}

void Camara::generarImagen(int base, int altura){
    vector<RGB> pixeles;
    imagenEscena = ImagenPPM("P3", 255, "", base, altura, 255, formatoRGB, pixeles);

}

void Camara::anyadirPrimitiva(Primitiva* primitiva){
    escena.anyadirPrimitiva(primitiva);
}

void Camara::lanzarRayos(int rayosPorPixel){
    float tamBasePixel = imagenEscena.getBase() / tamanyoPlano[0];
    float tamAlturaPixel = imagenEscena.getAltura() / tamanyoPlano[1];

    Punto3D esquinaIzqSup = Punto3D(l.getx(), u.gety(), f.getz());
    Pixel pixelInicial = Pixel(esquinaIzqSup, Punto3D(esquinaIzqSup.getx() + tamBasePixel, esquinaIzqSup.gety() - tamAlturaPixel, esquinaIzqSup.getz()));
    vector<Pixel> listaPixelesPlano;
    listaPixelesPlano.push_back(pixelInicial);
    Pixel pixelCalculado = pixelInicial;
    for(int a = tamAlturaPixel; a < imagenEscena.getAltura(); a = a + tamAlturaPixel){
        for(int b = tamBasePixel; b < imagenEscena.getBase(); b = b + tamBasePixel){
            Pixel aux = Pixel(Punto3D(pixelCalculado.getPuntoIzqSup().getx() + tamBasePixel, pixelCalculado.getPuntoIzqSup().gety(), pixelCalculado.getPuntoIzqSup().getz()), Punto3D(pixelCalculado.getPuntoDchInf().getx() + tamBasePixel, pixelCalculado.getPuntoDchInf().gety(), pixelCalculado.getPuntoDchInf().getz()));
            listaPixelesPlano.push_back(aux);
            pixelCalculado = aux;
        }
        pixelCalculado = Pixel(Punto3D(pixelInicial.getPuntoIzqSup().getx(), pixelInicial.getPuntoIzqSup().gety() - a, pixelInicial.getPuntoIzqSup().getz()), Punto3D(pixelInicial.getPuntoDchInf().getx(), pixelInicial.getPuntoDchInf().gety() - a, pixelInicial.getPuntoDchInf().getz()));
    }


    //Ahora tenemos todo un vector de pixeles donde lanzar rayos. Para cada pixel, lanzamos rayosPorPixel rayos y los guardamos todos para evaluarlos despues
    vector<Rayo> listaRayosAleatorios;
    for(auto p : listaPixelesPlano){
        for(int i = 0; i < rayosPorPixel; i++){
            Punto3D puntoAleatorio = generarPuntoAleatorioEnPixel(p);
            Rayo rayoAleatorioEnPixel = Rayo(origen, puntoAleatorio);
            // Para cada rayo, hay que ver si intersecta y darle color al pixel
            escena.intersectarRayo(p, rayoAleatorioEnPixel);
        }
    }
    // En este punto todos los pixeles deberian tener color
    listaPixeles = listaPixelesPlano;
}

Punto3D Camara::generarPuntoAleatorioEnPixel(Pixel pixel){
    // General altura y anchura aleatoria dentro del tamaño del pixel.
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<float> distribucion_altura(pixel.getPuntoDchInf().gety(), pixel.getPuntoIzqSup().gety());
    uniform_real_distribution<float> distribucion_anchura(pixel.getPuntoIzqSup().getx(), pixel.getPuntoDchInf().getx());

    float puntoAltura = distribucion_altura(gen);
    float puntoAnchura = distribucion_anchura(gen);

    return Punto3D(puntoAnchura, puntoAltura, pixel.getPuntoDchInf().getz());
}

ImagenPPM Camara::crearImagenPPM(){
    float valorMax = 0;
    float v;
    vector<RGB> pixeles;
    vector<Pixel> arrayPixeles = listaPixeles;
    for(auto p : arrayPixeles){
        v = p.getColor().maximo();
        pixeles.push_back(p.getColor());
        if(v > valorMax){
            valorMax = v;
        }
    }
    string formato = "P3";
    string comentario = "";
    return ImagenPPM(formato, valorMax, comentario, tamanyoPlano[0], tamanyoPlano[1], 255, formatoRGB, pixeles);
}


// Print
ostream& operator<<(ostream& os, const Camara& c) {
    os << "Camara: (Origen: "/* << c.origen << ", Up: " << c.u << ", Left: " << c.l << ", Forward: " << c.f << ", tamanyoPlano: " << c.tamanyoPlano[0] << "x" << c.tamanyoPlano[1]*/ << ")";
    return os;
}

// Esquina arriba a la izquierda = u + l + f + o
// Esquina abajo a la derecha = - u - l + f + o
// d*u + t*l + f + o con d y t entre 0 y 1 -> pixeles = 256 -> 1/256