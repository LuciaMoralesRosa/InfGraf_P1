#include "toneMapping.hpp"

FormatoPPM ToneMapping::corte(FormatoPPM imagen, float corte){
    for(int i = 0; i < imagen.getHeight(); i++){
        for(int j = 0; j < imagen.getWidth(); j++){
            PixelRGB pixelAux = imagen.pixelsImagen[i][j];
            if(pixelAux.getRed() > corte){
                pixelAux.setRed(corte);
            }
            if(pixelAux.getGreen() > corte){
                pixelAux.setGreen(corte);
            }
            if(pixelAux.getBlue() > corte){
                pixelAux.setBlue(corte);
            }
            imagen.pixelsImagen[i][j] = pixelAux;
        }
    }
    return imagen;
}

PixelRGB ToneMapping::corte(PixelRGB pixel, float corte){
    if(pixel.getRed() > corte){
        pixel.setRed(corte);
    }
    if(pixel.getGreen() > corte){
        pixel.setGreen(corte);
    }
    if(pixel.getBlue() > corte){
        pixel.setBlue(corte);
    }
    return pixel;
}

FormatoPPM ToneMapping::lineal(FormatoPPM img){
    float max = img.getMaxValor(); //Valor maximo sobre el que escalar
    float maxCalculado = 0.0;
    for(int i = 0; i < img.getHeight(); i++){
        for(int j = 0; j < img.getWidth(); j++){
            PixelRGB pixel = img.pixelsImagen[i][j];
            PixelRGB pixelAux(pixel.getRed()*img.getResolucionColor() / max,
                           pixel.getGreen()*img.getResolucionColor() / max,
                           pixel.getBlue()*img.getResolucionColor()/ max);
        img.pixelsImagen[i][j] = pixelAux;
        maxCalculado = maximo(maxCalculado, pixelAux.getRed(),
                                  pixelAux.getGreen(), pixelAux.getBlue());
        }
    }
    return img;
}

PixelRGB ToneMapping::lineal(FormatoPPM img, PixelRGB pixel){
    float max = img.getMaxValor(); //Valor maximo sobre el que escalar
    float maxCalculado = 0.0;
    PixelRGB pixelAux(pixel.getRed()*img.getResolucionColor() / max,
                      pixel.getGreen()*img.getResolucionColor() / max,
                      pixel.getBlue()*img.getResolucionColor()/ max);
    return pixelAux;
}

FormatoPPM ToneMapping::linealCorte(FormatoPPM imagen, float corte){
    float max = imagen.getMaxValor();
    for(int i = 0; i < imagen.getHeight(); i++){
        for(int j = 0; j < imagen.getWidth(); j++){
            PixelRGB pixelAux = imagen.pixelsImagen[i][j];
            if(pixelAux.getRed() > corte){
                pixelAux.setRed(corte);
            }
            else{
                pixelAux.setRed(pixelAux.getRed()*imagen.getResolucionColor() / max);
            }
            if(pixelAux.getGreen() > corte){
                pixelAux.setGreen(corte);
            }
            else{
                pixelAux.setGreen(pixelAux.getGreen()*imagen.getResolucionColor() / max);
            }
            if(pixelAux.getBlue() > corte){
                pixelAux.setBlue(corte);
            }
            else{
                pixelAux.setBlue(pixelAux.getBlue()*imagen.getResolucionColor() / max);
            }
            imagen.pixelsImagen[i][j] = pixelAux;
        }
    }
    return imagen;
}

PixelRGB ToneMapping::linealCorte(FormatoPPM imagen, PixelRGB pixel, float corte){
    float max = imagen.getMaxValor();
    if(pixel.getRed() > corte){
        pixel.setRed(corte);
    }
    else{
        pixel.setRed(pixel.getRed()*imagen.getResolucionColor() / max);
    }
    if(pixel.getGreen() > corte){
        pixel.setGreen(corte);
    }
    else{
        pixel.setGreen(pixel.getGreen()*imagen.getResolucionColor() / max);
    }
    if(pixel.getBlue() > corte){
        pixel.setBlue(corte);
    }
    else{
        pixel.setBlue(pixel.getBlue()*imagen.getResolucionColor() / max);
    }
    return pixel;
}


FormatoPPM ToneMapping::gamma(FormatoPPM img, float gamma){
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

FormatoPPM ToneMapping::gammaCorte(FormatoPPM img, float gamma, float corte){
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

FormatoPPM ToneMapping::reinhard(FormatoPPM img){
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

FormatoPPM ToneMapping::reinhardCorte(FormatoPPM img, float corte){
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

float ToneMapping::maximo(const float a, const float b, const float c, const float d){
    if(a > b && a > c && a > d) return a;
    else if(b > c && b > d) return b;
    else if(c > d) return c;
    else return d;
}