#ifndef MATRIZ_HPP
#define MATRIZ_HPP

#include <iostream>
#include <math.h>
using namespace std;

class Matriz {
    
    private: 
        float matrix[4][4];

    public:
        float det() const;
        Matriz adjunta() const;
        Matriz traspuesta() const;

        //Operadores
        Matriz operator+(const Matriz& m) const;
        Matriz operator-(const Matriz& m) const;

        Matriz operator*(const Matriz& m) const;
        Matriz operator*(const int scalar) const;
        Matriz operator/(const int scalar) const;

        bool operator==(const Matriz& m) const;


        Matriz(float m[4][4]);


        Matriz inversa() const;
        friend ostream& operator<<(ostream& os, const Matriz& m);

};

#endif