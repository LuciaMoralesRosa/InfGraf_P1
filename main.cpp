#include <iostream>
using namespace std;

#include "punto3d.hpp"
#include "direccion.hpp"
#include "coordenadas.hpp"
#include "matriz.hpp"
#include "esfera.hpp"
#include <math.h>

// g++ main.cpp esfera.cpp punto3d.cpp direccion.cpp coordenadas.cpp matriz.cpp -o programa

void probar() {
    // Crear dos puntos
    Punto3D p1(3.0, 4.0, 2.0);
    Punto3D p2(1.0, 2.0, -1.0);

    // Sumar los puntos usando el operador +
    Punto3D p3 = p1 + p2;

    // Comparar los puntos usando el operador ==
    if (p1 == p2) {
        cout << "Los puntos p1 y p2 son iguales" << endl;
    } else {
        cout << "Los puntos p1 y p2 son diferentes" << endl;
    }

    // Imprimir los puntos usando el operador <<
    cout << "p1: " << p1 << endl;
    cout << "p2: " << p2 << endl;
    cout << "p3 (p1 + p2): " << p3 << endl;

    // Crear dos puntos
    Direccion d1(3.0, 4.0, 2.0);
    Direccion d2(1.0, 2.0, -1.0);

    // Sumar los puntos usando el operador +
    Direccion d3 = d1 + d2;
    Direccion d4(1.0, 2.0, -1.0);

    // Comparar los puntos usando el operador ==
    if (d1 == d2) {
        cout << "Las direcciones d1 y d2 son iguales" << endl;
    } else {
        cout << "Las direcciones d1 y d2 son diferentes" << endl;
    }
    if (d2 == d4) {
        cout << "Las direcciones d2 y d4 son iguales" << endl;
    } else {
        cout << "Las direcciones d2 y d4 son diferentes" << endl;
    }

    Direccion d5 = d1 * 2;
    Direccion d6 = d1 / 2;
    Direccion d7 = d5.dot_product(d6);
    //Direccion d8 = d5.vector_product(d6);

    Direccion d10 = Direccion(-3,4,0);
    cout << d10.modulus() <<endl;
    Direccion d9 = d10.normalize();
    cout << d9.modulus() <<endl;
    if (d9.is_normalized()) {
        cout << "d9 es normal" << endl;
    }

    // Imprimir las direcciones usando el operador <<
    //cout << "d1: " << d1 << endl;
    //cout << "d2: " << d2 << endl;
    //cout << "d3 (d1 + d2): " << d3 << endl;
    //cout << "d5 (d1 * 2): " << d5 << endl;
    //cout << "d6 (d1 / 2): " << d6 << endl;
    //cout << "d7 (d5 . d6): " << d7 << endl;
    //cout << "d8 (d5 x d6): " << d8 << endl;
    cout << "d9 (normalized): " << d9 << endl;
}

void probar_coordenadas() {
    Coordenadas c1(1,1,1,1);
    Coordenadas c2 = c1.translate(2.0, 2.0, 2.0);
    Coordenadas c3 = c1.scale(2.0, 2.0, 2.0);
    Coordenadas c4 = c1.rotate_x_axis((90*M_PI)/180); 
    Coordenadas c5 = c1.rotate_y_axis(90);
    Coordenadas c6 = c1.rotate_z_axis(90);
    cout << "C1:" << endl << c1 << endl << "C2:" << endl << c2 << endl << "C3:" << endl << c3 << endl << "C4:" << endl <<
    c4 << endl << "C5:" << endl << c5 << endl << "C6:" << endl << c6 << endl;
    Coordenadas c7(1,1,1,0);
    Coordenadas c8 = c7.translate(2.0, 2.0, 2.0);
    Coordenadas c9 = c7.scale(2.0, 2.0, 2.0);
    Coordenadas c10 = c7.rotate_x_axis((90*3.14159274101257324219)/180);
    Coordenadas c11 = c7.rotate_y_axis(90);
    Coordenadas c12 = c7.rotate_z_axis(90);
    cout << "C7:" << endl << c7 << endl << "C8:" << endl << c8 << endl << "C9:" << endl << c9 << endl << "C10:" << endl <<
    c10 << endl << "C11:" << endl << c11 << endl << "C12:" << endl << c12 << endl;
}

void testMatrices(){

    //Determinante
    float matriz_det[4][4] = {{1, 2, 3, 4}, {3, 2, 6, 1}, {0, 1, 1, 0}, {1, 3, 0, 0}};
    Matriz m(matriz_det);
    float resultado_det = 48;
    if(m.det() == resultado_det){
        cout << "El determinante es correcto" << endl;
    }
    else{
        cout << "El determinante es INCORRECTO" << endl;
    }

    //Suma y resta
    float matriz_suma_1[4][4] = {{1, 1, 1, 1}, {1, 1, 1, 1}, {2, 2, 2, 2}, {1, 1, 1, 1}};
    float matriz_suma_2[4][4] = {{3, 3, 3, 3}, {1, 1, 1, 1}, {2, 2, 2, 2}, {1, 1, 1, 1}};
    float matriz_suma_res[4][4] = {{4, 4, 4, 4}, {2, 2, 2, 2}, {4, 4, 4, 4}, {2, 2, 2, 2}};
    float matriz_resta_res[4][4] = {{-1, -1, -1, -1}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};

    Matriz m_suma_1(matriz_suma_1);
    Matriz m_suma_2(matriz_suma_2);
    Matriz m_resta_res(matriz_resta_res);
    Matriz m_suma_res(matriz_suma_res);
    Matriz m_suma_obt = m_suma_1 + m_suma_2;
    Matriz m_resta_obt = m_suma_2 - m_suma_1;
    cout << "La matriz obtenida es: " << m_suma_obt << endl;
    cout << "El resultado correcto es: " << m_suma_res << endl;
    if(m_suma_res == m_suma_obt){
        cout << "El resultado de la suma es correcto" << endl;
    }
    else{
        cout << "El resultado de la suma es INCORRECTO" << endl;   
    }

    if(m_resta_res == m_resta_obt){
        cout << "El resultado de la resta es correcto" << endl;
    }
    else{
        cout << "El resultado de la resta es INCORRECTO" << endl;   
    }

    //Producto por escalar
    float matriz_prodEsc_res[4][4] = {{2, 2, 2, 2}, {2, 2, 2, 2}, {4, 4, 4, 4}, {2, 2, 2, 2}};
    Matriz m_prodEsc_res(matriz_prodEsc_res);
    Matriz m_prodEsc_obt = m_suma_1*2;
    if(m_prodEsc_res == m_prodEsc_obt){
        cout << "El resultado del producto escalar es correcto" << endl;
    }
    else{
        cout << "El resultado del producto escalar es INCORRECTO" << endl;   
    }


    float matriz_inv[4][4] = {{1, 1, 0, 0}, {0, -1, -2, 0}, {0, 0, 1, -1}, {0, 0, 0, 1}};
    float matriz_inv_res[4][4] = {{1, 1, 2, 2}, {0, -1, -2, -2}, {0, 0, 1, 1}, {0, 0, 0, 1}};

    Matriz m_inv(matriz_inv);
    Matriz m_inv_res(matriz_inv_res);
    Matriz m_inv_obt(m_inv.inversa());
    
    if(m_inv_res == m_inv_obt){
        cout << "El resultado de la inversa es correcto" << endl;
    }
    else{
        cout << "El resultado de la inversa es INCORRECTO" << endl;   
    }

}


/*******************************************************************************
 * Planetas
 ******************************************************************************/

/**
 * Creacion de una ciudad en un planeta
 */
Punto3D crearCiudad(Punto3D centro, float r, float az, float al){
    Esfera planeta = Esfera(centro, r);
    return planeta.anyadirPunto(az, al);
}

Direccion calcularNormal(Punto3D ciudad, Punto3D centro){
    Direccion normal = ciudad - centro;
    cout << "Planeta: " << endl << "Centro: " << centro << endl << 
    "Ciudad: " << ciudad << endl << "Normal: " << normal << endl << endl;
    return normal;
}

void viajesEspaciales(){

    // Variables
    float x1, y1, z1;
    float x2, y2, z2;
    float radio1, radio2;
    float azimut1, azimut2;
    float altitud1, altitud2;

    cout << "Introduzca las coordenadas del centro del planeta 1: " << endl;
    cin >> x1 >> y1 >> z1;

    cout << "Introduzca el radio planeta 1: " << endl;
    cin >> radio1;

    cout << "Introduzca el azimut y altitud del planeta 1: " << endl;
    cin >> azimut1 >> altitud1;
    
    cout << "Introduzca las coordenadas del centro del planeta 2: " << endl;
    cin >> x2 >> y2 >> z2;

    cout << "Introduzca el radio planeta 2: " << endl;
    cin >> radio2;

    cout << "Introduzca el azimut y altitud del planeta 2: " << endl;
    cin >> azimut2 >> altitud2;
    

    // Crear primer planeta y su ciudad
    Punto3D centro1 = Punto3D(x1, y1, z1);
    Punto3D ciudad1 = crearCiudad(centro1, radio1, azimut1, altitud1);
    Direccion normal1 = calcularNormal(ciudad1, centro1);

    // Crear segundo planeta
    Punto3D centro2 = Punto3D(x2, y2, z2);
    Punto3D ciudad2 = crearCiudad(centro2, radio2, azimut2, altitud2);
    Direccion normal2 = calcularNormal(ciudad2, centro2);

    // Unir ciudades -> crear trayectoria
    Direccion trayectoria1 = ciudad2 - ciudad1;
    Direccion trayectoria2 = ciudad1 - ciudad2;

    cout << endl << endl;
    float angulo1 = trayectoria1.obtenerAngulo(normal1);
    float angulo2 = trayectoria2.obtenerAngulo(normal2);
    
    if(abs(angulo1) <= 90 && abs(angulo2) <= 90){
        cout << "Es posible realizar el lanzamiento" << endl;
    }
    else {
        cout << "No es posible realizar el lanzamiento" << endl;
    }
}

int main() {
    
    viajesEspaciales();

    return 0;
}