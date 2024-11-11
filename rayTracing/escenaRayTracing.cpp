#include "escenaRayTracing.hpp"

//------------------------------- PRIVADAS -----------------------------------//
Punto3D EscenaRayTracing::generarPuntoAleatorioEnPixel(mt19937 gen, Pixel pixel){
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

RGB EscenaRayTracing::intersectarRayo(RGB colorPixel, Rayo rayo){
    
    vector<Interseccion> interseccionesPrimitivas;
    vector<float> vectorDistancias;
    vector<Primitiva*> primitivasIntersectadas;

    for(const auto& pri : primitivas){
        Interseccion i = pri->interseccionRayo(rayo);
        if(i.intersecta){
            interseccionesPrimitivas.push_back(i);
            vectorDistancias.push_back(calcularMIN(i.distancia));
            primitivasIntersectadas.push_back(pri);
        }
    }

    if(interseccionesPrimitivas.empty()){
        return colorPixel;
    }

    Primitiva* primitivaVisible;
    Interseccion interseccion;
    Punto3D puntoInterseccion;
    float menorDistancia = calcularMIN(vectorDistancias);
    
    for(int i = 0; i < interseccionesPrimitivas.size(); i++){
        for(int j = 0; j < interseccionesPrimitivas[i].distancia.size(); j++){
            if(interseccionesPrimitivas[i].distancia[j] == menorDistancia) {
                primitivaVisible = primitivasIntersectadas[i];
                interseccion = interseccionesPrimitivas[i];
                puntoInterseccion = interseccion.puntoInterseccion[j];
            }
        }
    }

    return primitivaVisible->getColor();
}


//------------------------------- PUBLICAS -----------------------------------//

void EscenaRayTracing::lanzarRayos(int rayosPorPixel) {
    vector<Rayo> listaRayos;

    vector<Pixel> cuadriculaPixeles = camara.getCuadriculaPixeles();

    if(!cuadriculaPixeles.empty()){
        vector<Pixel> nuevaCuadricula;
        vector<float> red, green, blue;

        random_device rd;
        for(auto p : cuadriculaPixeles){
            for(int i = 0; i < rayosPorPixel; i++){
                mt19937 gen(rd());
                Punto3D puntoAleatorio = generarPuntoAleatorioEnPixel(gen, p);
                Rayo rayoAleatorio = Rayo(camara.getOrigen(), puntoAleatorio);
                RGB colorObtenido = intersectarRayo(p.getColor(), rayoAleatorio);
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
        camara.setCuadricutaPixeles(cuadriculaPixeles);
    }
}

ImagenPPM EscenaRayTracing::crearImagenPPM(){
    float valorMax = 0;
    float v;
    vector<RGB> pixeles;
    vector<Pixel> arrayPixeles = camara.getCuadriculaPixeles();
    cout << "Depurando: Array pixeles en crear imagen: " << arrayPixeles[0].getColor() << endl;
    for(auto p : arrayPixeles){
        v = p.getColor().maximo();
        pixeles.push_back(p.getColor());
        if(v > valorMax){
            valorMax = v;
        }
    }
    string formato = "P3";
    string comentario = "";
    ImagenPPM imagen = ImagenPPM(formato, valorMax, comentario, camara.getTamPlanoImagenBase(), camara.getTamPlanoImagenAltura(), 255, formatoRGB, pixeles);
    return imagen;
}