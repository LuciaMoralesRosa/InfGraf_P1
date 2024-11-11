#include "esfera.hpp"

// NOTA: FALTA SACAR LA NORMAL

Esfera::Esfera(Punto3D _c, float _r, Textura _textura) : c(_c), r(_r), Primitiva(_textura) { }

Punto3D Esfera::anyadirPunto(float azimut, float altitud){
    ciudad = Punto3D(c.getx() + r * (float)sin(azimut * M_PI/180.0f),
                   c.gety() + r * (float)cos(azimut * M_PI/180.0f) * (float)sin(altitud * M_PI/180.0f),
                   c.getz() + r * (float)cos(azimut * M_PI/180.0f) * (float)cos(altitud * M_PI/180.0f)); 
    return  ciudad;
}

Direccion Esfera::getNormal(Punto3D punto) const {
    return punto-c;
}


Interseccion Esfera::interseccionRayo(Rayo rayo) const {
    Punto3D ORayo = rayo.getOrigen();
    Direccion dir = rayo.getDireccion().normalize();

    Punto3D OEsfera = c;
    float radio = r;
    

    Direccion L = ORayo - OEsfera; //vector desde el centro de la esfera al punto de origen del rayo.
    //t2(d⋅d) + 2t(d⋅L) + (L⋅L−r2)=0

    float A = dir.dot_product(dir);         // A = d · d
    float B = 2 * (dir.dot_product(L));     // B = 2 * (d · L)
    float C = L.dot_product(L) - (r * r);   // C = L · L - r^2

    float discriminante = B * B - 4 * A * C;

    Interseccion resultado;

    if (discriminante < 0) {
        // No hay intersección
        resultado.intersecta = false;
        resultado.distancia.clear();
        resultado.puntoInterseccion.clear();
        return resultado;
    }
    else {
        // Hay una o dos intersecciones
        float sqrtDiscriminante = sqrt(discriminante);
        float t1 = (-B - sqrtDiscriminante) / (2 * A);
        float t2 = (-B + sqrtDiscriminante) / (2 * A);
        resultado.intersecta = true;
        resultado.distancia.push_back(t1); // Una interseccion
        resultado.puntoInterseccion.push_back(Punto3D(ORayo, dir, t1));
        resultado.colorPrimitiva = getColor();
        if (t1 != t2){
            resultado.distancia.push_back(t2); // Dos intersecciones
            resultado.puntoInterseccion.push_back(Punto3D(ORayo, dir, t2));
        }
        return resultado;
    }
}

// Print
ostream& operator<<(ostream& os, const Esfera& esfera) {
    os << "Esfera";
    return os;
}

