#include "camara.hpp"

Camara::Camara(Punto3D origen_val, Direccion u_val, Direccion l_val, Direccion f_val, int tam_val[2]){
    origen = origen_val;
    u = u_val;
    l = l_val;
    f = f_val;
    tamanyo[0] = tam_val[0];
    tamanyo[1] = tam_val[1];
}

vector<Pixel> Camara::generarPuntos() {
    // Tengo que añadir operaciones entre punto y dirección o utilizar coordenadas homogeneas
    // Si no esto queda larguisimo
    // Recorre de arriba a la izquierda a abajo a la derecha
    vector<Pixel> pixeles;

    // Coordenadas de la esquina de arriba a la izquierda
    float x_esquina = origen.getx() + f.getx() + u.getx() + l.getx();
    float y_esquina = origen.gety() + f.gety() + u.gety() + l.gety();
    float z_esquina = origen.getz() + f.getz() + u.getz() + l.getz();
    // Tamaño del pixel en dirección down
    float tam_pixel_u_x = u.getx()/tamanyo[1];
    float tam_pixel_u_y = u.gety()/tamanyo[1];
    float tam_pixel_u_z = u.getz()/tamanyo[1];
    //cout << "Tamanyo de pixel down: (" << tam_pixel_u_x << "," << tam_pixel_u_y << "," << tam_pixel_u_z << ")" << endl;
    // Tamaño del pixel en dirección right
    float tam_pixel_l_x = l.getx()/tamanyo[0];
    float tam_pixel_l_y = l.gety()/tamanyo[0];
    float tam_pixel_l_z = l.getz()/tamanyo[0];
    //cout << "Tamanyo de pixel right: (" << tam_pixel_l_x << "," << tam_pixel_l_y << "," << tam_pixel_l_z << ")" << endl;

    for (int j = tamanyo[1]; j > 0; j--) {
        for (int i = tamanyo[0]; i > 0; i--) {
            //    Esquina arr-izq - despl abajo j pixeles + tam pixel     - despl der i pixeles + tam pixel
            // nota: + tam pixel para centrar punto a mitad del pixel, cambiar cuando se envien multiples rayos
            Punto3D p(  x_esquina - (tam_pixel_u_x*j*2) + (tam_pixel_u_x) - (tam_pixel_l_x*i*2) + (tam_pixel_l_x), 
                        y_esquina - (tam_pixel_u_y*j*2) + (tam_pixel_u_y) - (tam_pixel_l_y*i*2) + (tam_pixel_l_y), 
                        z_esquina - (tam_pixel_u_z*j*2) + (tam_pixel_u_z) - (tam_pixel_l_z*i*2) + (tam_pixel_l_z));
            Punto3D p2(  x_esquina - (tam_pixel_u_x*j*2) + (tam_pixel_u_x*2) - (tam_pixel_l_x*i*2) + (tam_pixel_l_x*2), 
                        y_esquina - (tam_pixel_u_y*j*2) + (tam_pixel_u_y*2) - (tam_pixel_l_y*i*2) + (tam_pixel_l_y*2), 
                        z_esquina - (tam_pixel_u_z*j*2) + (tam_pixel_u_z*2) - (tam_pixel_l_z*i*2) + (tam_pixel_l_z*2));
            //cout << ": " << p << endl;
            pixeles.push_back(Pixel(p,p2));
        }
    }
    return pixeles;
}

// Print
ostream& operator<<(ostream& os, const Camara& c) {
    os << "Camara: (Origen: " << c.origen << ", Up: " << c.u << ", Left: " << c.l << ", Forward: " << c.f << ", Tamanyo: " << c.tamanyo[0] << "x" << c.tamanyo[1] << ")";
    return os;
}

// Esquina arriba a la izquierda = u + l + f + o
// Esquina abajo a la derecha = - u - l + f + o
// d*u + t*l + f + o con d y t entre 0 y 1 -> pixeles = 256 -> 1/256