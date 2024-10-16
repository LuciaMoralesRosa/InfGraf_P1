#include "camara.hpp"

Camara::Camara(Punto3D origen_val, Direccion u_val, Direccion l_val, Direccion f_val, int tam_val[2]){
    origen = origen_val;
    u = u_val;
    l = l_val;
    f = f_val;
    tamanyo[0] = tam_val[0];
    tamanyo[1] = tam_val[1];
}

Punto3D Camara::generarPuntos() {
    // Tengo que añadir operaciones entre punto y dirección o utilizar coordenadas homogeneas
    Punto3D punto(  origen.getx() + f.getx() + u.getx() + l.getx(), 
                    origen.gety() + f.gety() + u.gety() + l.gety(), 
                    origen.getz()  + f.getz() + u.getz() + l.getz());
    cout << "Arriba izquierda: " << punto << endl;
    Punto3D punto2( origen.getx() + f.getx() - u.getx() - l.getx(), 
                    origen.gety() + f.gety() - u.gety() - l.gety(), 
                    origen.getz()  + f.getz() - u.getz() - l.getz());
    cout << "Abajo derecha: " << punto2 << endl;
}

// Print
ostream& operator<<(ostream& os, const Camara& c) {
    os << "Camara: (Origen: " << c.origen << ", Up: " << c.u << ", Left: " << c.l << ", Forward: " << c.f << ", Tamanyo: " << c.tamanyo[0] << "x" << c.tamanyo[1] << ")";
    return os;
}

// Esquina arriba a la izquierda = u + l + f + o
// Esquina abajo a la derecha = - u - l + f + o
// d*u + t*l + f + o con d y t entre 0 y 1 -> pixeles = 256 -> 1/256