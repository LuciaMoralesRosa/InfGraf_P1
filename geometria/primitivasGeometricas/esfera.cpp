#include "esfera.hpp"

// NOTA: FALTA SACAR LA NORMAL

Esfera::Esfera(Punto3D _c, float _r, Textura _textura) : c(_c), r(_r), Primitiva(_textura, "Esfera") { }

Punto3D Esfera::anyadirPunto(float azimut, float altitud){
    ciudad = Punto3D(c.getx() + r * (float)sin(azimut * M_PI/180.0f),
                   c.gety() + r * (float)cos(azimut * M_PI/180.0f) * (float)sin(altitud * M_PI/180.0f),
                   c.getz() + r * (float)cos(azimut * M_PI/180.0f) * (float)cos(altitud * M_PI/180.0f)); 
    return  ciudad;
}

Direccion Esfera::getNormal(Punto3D punto) const {
    return (punto-c).normalize();
}


bool Esfera::interseccionRayo(Rayo& rayo) const {
    Punto3D oRayo = rayo.getOrigen();
    Direccion dirRayo = rayo.getDireccion().normalize();

    Punto3D OEsfera = c;
    float radioEsfera = r;
    

    Direccion L = oRayo - OEsfera; //vector desde el centro de la esfera al punto de origen del rayo.
    //t2(d⋅d) + 2t(d⋅L) + (L⋅L−r2)=0

    float A = dirRayo.dot_product(dirRayo);         // A = d · d
    float B = 2 * (dirRayo.dot_product(L));     // B = 2 * (d · L)
    float C = L.dot_product(L) - (radioEsfera * radioEsfera);   // C = L · L - r^2

    float discriminante = B * B - 4 * A * C;


    if (discriminante < 0) {
        // No hay intersección
        cout << "No hay interseccion" << endl;
        return false;
    }
    else {
        // Hay una o dos intersecciones
        float sqrtDiscriminante = sqrt(discriminante);
        float t1 = (-B - sqrtDiscriminante) / (2 * A);
        float t2 = (-B + sqrtDiscriminante) / (2 * A);
        Punto3D puntoInterseccion = Punto3D(oRayo, dirRayo, t1);
        Interseccion interseccion(t1, puntoInterseccion, getNormal(puntoInterseccion));
        rayo.addInterseccion(interseccion);
        if (t1 != t2){
            puntoInterseccion = Punto3D(oRayo, dirRayo, t2);
            interseccion = Interseccion(t2, puntoInterseccion, getNormal(puntoInterseccion));
            rayo.addInterseccion(interseccion);
        }
        return true;
    }
}

// Print
ostream& operator<<(ostream& os, const Esfera& esfera) {
    os << "Esfera";
    return os;
}

