#ifndef DIRECCION_HPP
#define DIRECCION_HPP

#include <iostream>
#include <math.h>
using namespace std;

/**
 * Implementacion de la clase Direccion y sus operaciones
 */
class Direccion {
    private:
        // COordenadas de la direccion    
        float x, y, z;
        
    public:

        /**
         * @brief Constructor de Direccion
         * 
         * @param x_val Valor para la coordenada x de la direccion
         * @param y_val Valor para la coordenada y de la direccion
         * @param z_val Valor para la coordenada z de la direccion
         */
        Direccion(float x_val = 0, float y_val = 0, float z_val = 0);

        //Operadores
        Direccion operator+(const Direccion& dir) const;
        Direccion operator-(const Direccion& dir) const;
        Direccion operator*(const int scalar) const;
        Direccion operator/(const int scalar) const;

        // Comparadores
        bool operator==(const Direccion& otro) const;    
        bool operator!=(const Direccion& otro) const;
        bool operator>(const Direccion& otro) const;
        bool operator<(const Direccion& otro) const;
        bool operator>=(const Direccion& otro) const;
        bool operator<=(const Direccion& otro) const;

        float getx();
        float gety();
        float getz();
        
        //Metodos de operacion

        /**
         * Producto escalar de dos vectores
         * 
         * @param dir Vector a multiplicar
         * @return Resultado del producto escalar
         */
        float dot_product(const Direccion& dir) const;

        /**
         * Producto vectorial de dos vectores
         * 
         * @param dir Vector a multiplicar
         * @return Resultado del producto vectorial
         */
        Direccion vector_product(const Direccion& dir) const;

        /**
         * Calculo del angulo entre dos vectores
         * 
         * @param dir Vector con el que se forma el angulo
         * @return Grados del angulo que forman los dos vectores (NO RADIANES) 
         */
        float obtenerAngulo(const Direccion& dir) const;

        /**
         * Calculo del modulo del vector
         * 
         * @return Valor del modulo del vector 
         */
        float modulus() const;
        
        /**
         * Normalizacion del vector
         *  
         * @return Devuelve el vector normalizado 
         */
        Direccion normalize() const;

        /**
         * Comprueba si dos vectores son perpendiculares
         * 
         * @param dir Vector con el que evaluar la perpendicularidad
         * @return true si los vectores son perpendiculares y false si no lo son
         */
        bool is_perpendicular(const Direccion& dir) const;

        /**
         * Comprueba si el vector esta normalizado
         * 
         * @return true si el vector esta normalizado y false si no lo esta
         */
        bool is_normalized() const;

        /**
         * @brief Sobrecarga del operador de inserción << para imprimir un objeto de tipo Direccion.
         * 
         * Esta función permite imprimir los valores de un objeto Direccion utilizando un flujo de salida estándar 
         * (por ejemplo, cout). La función toma una referencia al flujo de salida y una referencia constante 
         * a un objeto Direccion, y devuelve el mismo flujo de salida después de imprimir los valores de los miembros 
         * del objeto Direccion.
         * 
         * @param os Flujo de salida en el que se imprimirán los valores de Direccion.
         * @param d Referencia constante al objeto Direccion cuyos valores se desean imprimir.
         * @return ostream& El flujo de salida modificado con los valores de la Dirección.
         */
        friend ostream& operator<<(ostream& os, const Direccion& d);
        
};

#endif