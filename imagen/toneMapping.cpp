#include "toneMapping.hpp"

FormatoPPM ToneMaping::corte(FormatoPPM img, float corte){
    FormatoPPM imagen(1, img.getWidth(), img.getHeight(), 
                      img.getResolucionColor(), img.getComentario());

    for(int i = 0; i < img.getHeight(); i++){
        for(int j = 0; j < img.getWidth(); j++){
            PixelRGB imgAux = img.pixelsImagen[i][j];
            if(imgAux.getRed() > corte){
                imgAux.setRed(corte);
            }
            if(imgAux.getGreen() > corte){
                imgAux.setGreen(corte);
            }
            if(imgAux.getBlue() > corte){
                imgAux.setBlue(corte);
            }
            imagen.pixelsImagen[i][j] = imgAux;
        }
    }

    return imagen;
}

FormatoPPM ToneMaping::lineal(FormatoPPM img){
    float max = img.getMaxValor();
    float maxCalculado = 0.0;

    FormatoPPM imagen(1, img.getWidth(), img.getHeight(), 
                      img.getResolucionColor(), img.getComentario());

    for(int i = 0; i < img.getHeight(); i++){
        for(int j = 0; j < img.getWidth(); j++){
            PixelRGB rgbAux = img.pixelsImagen[i][j];
            PixelRGB rgb(rgbAux.getRed()/max,
                         rgbAux.getGreen()/max,
                         rgbAux.getBlue()/max);
            imagen.pixelsImagen[i][j] = rgb;
            maxCalculado = maximo(maxCalculado, rgbAux.getRed()*255,
                                  rgbAux.getGreen()*255, rgbAux.getBlue()*255);
        }
    }
    imagen.setMaxValor(maxCalculado);
    return imagen;
}


FormatoPPM ToneMaping::linealCorte(FormatoPPM img, float corte){
    FormatoPPM imagen(1, img.getWidth(), img.getHeight(), 
                      img.getResolucionColor(), img.getComentario());

    for(int i = 0; i < img.getHeight(); i++){
        for(int j = 0; j < img.getWidth(); j++){
            PixelRGB rgbAux = img.pixelsImagen[i][j];
            if(rgbAux.getRed() > corte){
                rgbAux.setRed(1);
            }
            else{
                rgbAux.setRed(rgbAux.getRed()/corte);
            }

            if(rgbAux.getGreen() > corte){
                rgbAux.setGreen(1);
            }
            else{
                rgbAux.setGreen(rgbAux.getGreen()/corte);
            }

            if(rgbAux.getBlue() > corte){
                rgbAux.setBlue(1);
            }
            else{
                rgbAux.setBlue(rgbAux.getBlue()/corte);
            }

            imagen.pixelsImagen[i][j] = rgbAux;
        }
    }
    return imagen;
}


FormatoPPM ToneMaping::gamma(FormatoPPM img, float gamma){
    FormatoPPM imagen(1, img.getWidth(), img.getHeight(), 
                      img.getResolucionColor(), img.getComentario());

    float maxVal = img.getMaxValor();
    float maxNuevo = 0.0;

    for(int i = 0; i < img.getHeight(); i++){
        for(int j = 0; j < img.getWidth(); j++){
            PixelRGB rgbAux = img.pixelsImagen[i][j];

            if(rgbAux.getRed() > maxVal){
                rgbAux.setRed(maxVal);
            }
            else{
                rgbAux.setRed(pow(rgbAux.getRed(), 1/gamma)/pow(maxVal, 1/gamma));
            }

            if(rgbAux.getGreen() > maxVal){
                rgbAux.setGreen(maxVal);
            }
            else{
                rgbAux.setGreen(pow(rgbAux.getGreen(), 1/gamma)/pow(maxVal, 1/gamma));
            }

            if(rgbAux.getBlue() > maxVal){
                rgbAux.setBlue(maxVal);
            }
            else{
                rgbAux.setBlue(pow(rgbAux.getBlue(), 1/gamma)/pow(maxVal, 1/gamma));
            }

            imagen.pixelsImagen[i][j] = rgbAux;
            maxNuevo = maximo(maxNuevo, rgbAux.getRed()*255, 
                                        rgbAux.getGreen()*255, 
                                        rgbAux.getBlue()*255);
        }
    } 

    imagen.setMaxValor(maxNuevo);
    return imagen;
}

FormatoPPM ToneMaping::gammaCorte(FormatoPPM img, float gamma, float corte){
    FormatoPPM imagen(1, img.getWidth(), img.getHeight(), 
                      img.getResolucionColor(), img.getComentario());

    float maxVal = img.getMaxValor();
    for(int i = 0; i < img.getHeight(); i++){
        for(int j = 0; j < img.getWidth(); j++){
            PixelRGB rgbAux = img.pixelsImagen[i][j];
            
            if(rgbAux.getRed() > corte){
                rgbAux.setRed(1);
            }
            else{
                rgbAux.setRed(pow(rgbAux.getRed(), 1/gamma)/pow(maxVal, 1/gamma));
            }

            if(rgbAux.getGreen() > corte){
                rgbAux.setGreen(1);
            }
            else{
                rgbAux.setGreen(pow(rgbAux.getGreen(), 1/gamma)/pow(maxVal, 1/gamma));
            }

            if(rgbAux.getBlue() > corte){
                rgbAux.setBlue(1);
            }
            else{
                rgbAux.setBlue(pow(rgbAux.getBlue(), 1/gamma)/pow(maxVal, 1/gamma));
            }

            imagen.pixelsImagen[i][j] = rgbAux;
        }
    }

    return imagen;
}

FormatoPPM ToneMaping::reinhard(FormatoPPM img){
    FormatoPPM imagen(1, img.getWidth(), img.getHeight(), 
                      img.getResolucionColor(), img.getComentario());
    
    for(int i = 0; i < img.getHeight(); i++){
        for(int j = 0; j < img.getWidth(); j++){
            PixelRGB rgbAux = img.pixelsImagen[i][j];
            rgbAux.setRed(rgbAux.getRed() / (1 + rgbAux.getRed()));
            rgbAux.setGreen(rgbAux.getGreen() / (1 + rgbAux.getGreen()));
            rgbAux.setBlue(rgbAux.getBlue() / (1 + rgbAux.getBlue()));

            imagen.pixelsImagen[i][j] = rgbAux;
        }
    }
    return imagen;
}

FormatoPPM ToneMaping::reinhardCorte(FormatoPPM img, float corte){
    FormatoPPM imagen(1, img.getWidth(), img.getHeight(), 
                      img.getResolucionColor(), img.getComentario());
    
    for(int i = 0; i < img.getHeight(); i++){
        for(int j = 0; j < img.getWidth(); j++){
            PixelRGB rgbAux = img.pixelsImagen[i][j];
            PixelRGB n = rgbAux * (rgbAux / (corte*corte) + 1);
            PixelRGB d = rgbAux + 1;
            imagen.pixelsImagen[i][j] = n / d;
        }
    }
    return imagen;
}

float maximo(const float a, const float b, const float c, const float d){
    if(a > b && a > c && a > d) return a;
    else if(b > c && b > d) return b;
    else if(c > d) return c;
    else return d;
}