#include "camara.hpp"

//------------------------------- PRIVADAS -----------------------------------//
Punto3D Camara::generarPuntoAleatorioEnPixel(mt19937 gen, Pixel pixel){
    // General altura y anchura aleatoria dentro del tamaño del pixel.
    //mt19937 gen(rd());

    uniform_real_distribution<float> distribucion_altura(pixel.getPuntoDchInf().gety(),
                                                         pixel.getPuntoIzqSup().gety());
    uniform_real_distribution<float> distribucion_anchura(pixel.getPuntoIzqSup().getx(),
                                                         pixel.getPuntoDchInf().getx());                 
    uniform_real_distribution<float> distribucion_profundidad(pixel.getPuntoIzqSup().getz(),
                                                         pixel.getPuntoDchInf().getz());

    float puntoAltura = distribucion_altura(gen);
    float puntoAnchura = distribucion_anchura(gen);
    float puntoProfundidad = distribucion_profundidad(gen);

    return Punto3D(puntoAnchura, puntoAltura, puntoProfundidad);
}


void Camara::crearCuadriculaPixeles(){
    Punto3D esquinaIzqSup = Punto3D(l.getx() + origen.getx(),
                                    u.gety() + origen.gety(),
                                    f.getz() + origen.getz());
    
    // Recorremos la cuadrícula en función del tamaño de la imagen
    for (int i = 0; i < tamPlanoImagen[1]; i++) {
        for (int j = 0; j < tamPlanoImagen[0]; j++) {
            // Calculamos la esquina superior izquierda del píxel actual
            Punto3D esquinaSupIzqPixel = Punto3D(
                esquinaIzqSup.getx() + j * tamPixel[0],
                esquinaIzqSup.gety() - i * tamPixel[1],
                esquinaIzqSup.getz()
            );

            // Calculamos la esquina inferior derecha del píxel actual
            Punto3D esquinaInfDerPixel = Punto3D(
                esquinaSupIzqPixel.getx() + tamPixel[0],
                esquinaSupIzqPixel.gety() - tamPixel[1],
                esquinaSupIzqPixel.getz()
            );
            
            //cout << "Tamaño de pixel: " << tamPixel[0] << "x" << tamPixel[1] << endl;
            //cout << "Puntos del pixel: " << esquinaSupIzqPixel << " - " << esquinaInfDerPixel << endl;
            
            // Creamos el objeto Pixel y lo agregamos a la cuadrícula
            Pixel pixel = Pixel(esquinaSupIzqPixel, esquinaInfDerPixel);
            cuadriculaPixeles.push_back(pixel);
        }
    }    
}
//------------------------------- FIN PRIVADAS -------------------------------//

//------------------------------ CONSTRUCTORES -------------------------------//
Camara::Camara(Punto3D origen_val, Direccion u_val, Direccion l_val,
               Direccion f_val, array<int, 2> tam_val){
    origen = origen_val;
    u = u_val;
    l = l_val;
    f = f_val;
    tamPlanoImagen[0] = tam_val[0];
    tamPlanoImagen[1] = tam_val[1];

    if (tam_val[0] == 0 || tam_val[1] == 0) {
        throw std::invalid_argument("El tamaño del plano de imagen no puede ser cero");
    }

    tamPixel[0] = l.modulus()*2 / tam_val[0];
    tamPixel[1] = u.modulus()*2 / tam_val[1];

    cuadriculaPixeles.reserve(tamPlanoImagen[0] * tamPlanoImagen[1]);
    crearCuadriculaPixeles();
}

//--------------------------------- PUBLICAS ---------------------------------//

void Camara::anyadirPrimitiva(Primitiva* primitiva){
    escena.anyadirPrimitiva(primitiva);
}

void Camara::asignarEscena(Escena e){
    escena = e;
}
/*
void Camara::generarImagen(int base, int altura){
    vector<RGB> pixeles;
    imagenEscena = ImagenPPM("P3", 255, "", base, altura, 255, formatoRGB, pixeles);
}
*/

void Camara::lanzarRayos(int rayosPorPixel){
    vector<Rayo> listaRayos;

    if(!cuadriculaPixeles.empty()){
        vector<Pixel> nuevaCuadricula;
        vector<float> red, green, blue;

        random_device rd;
        for(auto p : cuadriculaPixeles){
            for(int i = 0; i < rayosPorPixel; i++){
                mt19937 gen(rd());
                Punto3D puntoAleatorio = generarPuntoAleatorioEnPixel(gen, p);
                Rayo rayoAleatorio = Rayo(origen, puntoAleatorio);
                RGB colorObtenido = escena.intersectarRayo(p.getColor(), rayoAleatorio);
                red.push_back(colorObtenido.getR());
                green.push_back(colorObtenido.getG());
                blue.push_back(colorObtenido.getB());
            }
            // Hacer media de cada componente y crear nuevo RGB
            RGB rgb(calcularMedia(red), calcularMedia(green), calcularMedia(blue));
            p.setColor(rgb);
            nuevaCuadricula.push_back(p);
            red.clear();
            green.clear();
            blue.clear();
        }
        cuadriculaPixeles = nuevaCuadricula;
    }
}


void Camara::lanzarRayos2(int rayosPorPixel){
    /*
    float tamBasePixel = tamPlanoImagen[0] / imagenEscena.getBase();
    float tamAlturaPixel = tamPlanoImagen[1] / imagenEscena.getAltura();
    Punto3D esquinaIzqSup = Punto3D(l.getx(), u.gety(), f.getz());

    Pixel pixelInicial = Pixel(esquinaIzqSup, Punto3D(esquinaIzqSup.getx() + tamBasePixel, esquinaIzqSup.gety() - tamAlturaPixel, esquinaIzqSup.getz()));
    vector<Pixel> cuadriculaPixelesPlano;
    cuadriculaPixelesPlano.push_back(pixelInicial);
    Pixel pixelCalculado = pixelInicial;
    for(int a = tamAlturaPixel; a < imagenEscena.getAltura(); a = a + tamAlturaPixel){
        for(int b = tamBasePixel; b < imagenEscena.getBase(); b = b + tamBasePixel){
            Pixel aux = Pixel(Punto3D(pixelCalculado.getPuntoIzqSup().getx() + tamBasePixel, pixelCalculado.getPuntoIzqSup().gety(), pixelCalculado.getPuntoIzqSup().getz()), Punto3D(pixelCalculado.getPuntoDchInf().getx() + tamBasePixel, pixelCalculado.getPuntoDchInf().gety(), pixelCalculado.getPuntoDchInf().getz()));
            cuadriculaPixelesPlano.push_back(aux);
            pixelCalculado = aux;
        }
        pixelCalculado = Pixel(Punto3D(pixelInicial.getPuntoIzqSup().getx(), pixelInicial.getPuntoIzqSup().gety() - a, pixelInicial.getPuntoIzqSup().getz()), Punto3D(pixelInicial.getPuntoDchInf().getx(), pixelInicial.getPuntoDchInf().gety() - a, pixelInicial.getPuntoDchInf().getz()));
    }
    //Ahora tenemos todo un vector de pixeles donde lanzar rayos. Para cada pixel, lanzamos rayosPorPixel rayos y los guardamos todos para evaluarlos despues
    vector<Rayo> listaRayosAleatorios;
    for(auto p : cuadriculaPixelesPlano){
        for(int i = 0; i < rayosPorPixel; i++){
            Punto3D puntoAleatorio = generarPuntoAleatorioEnPixel(p);
            Rayo rayoAleatorioEnPixel = Rayo(origen, puntoAleatorio);
            escena.intersectarRayo(p, rayoAleatorioEnPixel);
        }
    }
    cuadriculaPixeles = cuadriculaPixelesPlano;
    */

}


ImagenPPM Camara::crearImagenPPM(){
    float valorMax = 0;
    float v;
    vector<RGB> pixeles;
    vector<Pixel> arrayPixeles = cuadriculaPixeles;
    for(auto p : arrayPixeles){
        cout << "Color del pixel de la cuadricula en crearImagen: " << p.getColor() << endl;
        v = p.getColor().maximo();
        pixeles.push_back(p.getColor());
        if(v > valorMax){
            valorMax = v;
        }
    }
    string formato = "P3";
    string comentario = "";
    ImagenPPM imagen = ImagenPPM(formato, valorMax, comentario, tamPlanoImagen[0], tamPlanoImagen[1], 255, formatoRGB, pixeles);
    return imagen;
}


//-------------------------------- IMPRESION ---------------------------------//
ostream& operator<<(ostream& os, const Camara& c) {
    os << "Camara: (Origen: "/* << c.origen << ", Up: " << c.u << ", Left: " << c.l << ", Forward: " << c.f << ", tamPlanoImagen: " << c.tamPlanoImagen[0] << "x" << c.tamPlanoImagen[1]*/ << ")";
    return os;
}

// Esquina arriba a la izquierda = u + l + f + o
// Esquina abajo a la derecha = - u - l + f + o
// d*u + t*l + f + o con d y t entre 0 y 1 -> pixeles = 256 -> 1/256


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
    float tam_pixel_u_x = u.getx()/tamPlanoImagen[1];
    float tam_pixel_u_y = u.gety()/tamPlanoImagen[1];
    float tam_pixel_u_z = u.getz()/tamPlanoImagen[1];
    //cout << "tamPlanoImagen de pixel down: (" << tam_pixel_u_x << "," << tam_pixel_u_y << "," << tam_pixel_u_z << ")" << endl;
    // Tamaño del pixel en dirección right
    float tam_pixel_l_x = l.getx()/tamPlanoImagen[0];
    float tam_pixel_l_y = l.gety()/tamPlanoImagen[0];
    float tam_pixel_l_z = l.getz()/tamPlanoImagen[0];
    //cout << "tamPlanoImagen de pixel right: (" << tam_pixel_l_x << "," << tam_pixel_l_y << "," << tam_pixel_l_z << ")" << endl;

    for (int j = tamPlanoImagen[1]; j > 0; j--) {
        for (int i = tamPlanoImagen[0]; i > 0; i--) {
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