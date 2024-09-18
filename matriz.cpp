#include "matriz.hpp"

// Constructor
Matriz::Matriz(float m[4][4]){
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            matrix[i][j] = m[i][j];
        }
    }
}

float Matriz::det() const {
    float B = matrix[1][1]*matrix[2][2]*matrix[3][3] + 
                matrix[2][1]*matrix[3][2]*matrix[1][3] +
                matrix[3][1]*matrix[1][2]*matrix[2][3] -
                matrix[1][3]*matrix[2][2]*matrix[3][1] - 
                matrix[2][3]*matrix[3][2]*matrix[1][1] - 
                matrix[3][3]*matrix[2][1]*matrix[1][2];
    float C = matrix[1][0]*matrix[2][2]*matrix[3][3] +
                matrix[2][0]*matrix[3][2]*matrix[1][3] +
                matrix[3][0]*matrix[1][2]*matrix[2][3] -
                matrix[1][3]*matrix[2][2]*matrix[3][0] -
                matrix[2][3]*matrix[3][2]*matrix[1][0] -
                matrix[3][3]*matrix[1][2]*matrix[2][0];
    float D = matrix[1][0]*matrix[2][1]*matrix[3][3] +
                matrix[1][1]*matrix[2][3]*matrix[3][0] +
                matrix[1][3]*matrix[2][0]*matrix[3][1] -
                matrix[1][3]*matrix[2][1]*matrix[3][0] -
                matrix[2][3]*matrix[3][1]*matrix[1][0] -
                matrix[3][3]*matrix[1][1]*matrix[2][0];
    float E = matrix[1][0]*matrix[2][1]*matrix[3][2] +
                matrix[1][1]*matrix[2][2]*matrix[3][0] +
                matrix[1][2]*matrix[2][0]*matrix[3][1] -
                matrix[1][2]*matrix[2][1]*matrix[3][0] -
                matrix[2][2]*matrix[3][1]*matrix[1][0] -
                matrix[3][2]*matrix[1][1]*matrix[2][0];
    return matrix[0][0] * B - matrix[0][1] * C + matrix[0][2]*D - matrix[0][3]*E;
}


Matriz Matriz::adjunta() const {
    float resultado[4][4];
    resultado[0][0] = matrix[1][1] * matrix[2][2] * matrix[3][3] +  
                        matrix[2][1] * matrix[3][2] * matrix[1][3] +  
                        matrix[1][2] * matrix[2][3] * matrix[3][1] - 
                        matrix[1][3] * matrix[2][2] * matrix[3][1] - 
                        matrix[2][1] * matrix[1][2] * matrix[3][3] - 
                        matrix[3][2] * matrix[2][3] * matrix[1][1];
    resultado[1][0] = -(matrix[0][1] * matrix[2][2] * matrix[3][3] + 
                        matrix[2][1] * matrix[3][2] * matrix[0][3] + 
                        matrix[0][2] * matrix[2][3] * matrix[3][1] - 
                        matrix[0][3] * matrix[2][2] * matrix[3][1] - 
                        matrix[2][1] * matrix[0][2] * matrix[3][3] - 
                        matrix[3][2] * matrix[2][3] * matrix[0][1]);
    resultado[2][0] = matrix[0][1] * matrix[1][2] * matrix[3][3] + 
                        matrix[1][1] * matrix[3][2] * matrix[0][3] + 
                        matrix[0][2] * matrix[1][3] * matrix[3][1] - 
                        matrix[0][3] * matrix[1][2] * matrix[3][1] - 
                        matrix[1][1] * matrix[0][2] * matrix[3][3] - 
                        matrix[3][2] * matrix[1][3] * matrix[0][1];
    resultado[3][0] = -(matrix[0][1] * matrix[1][2] * matrix[2][3] + 
                        matrix[1][1] * matrix[2][2] * matrix[0][3] +
                        matrix[0][2] * matrix[1][3] * matrix[2][1] - 
                        matrix[0][3] * matrix[1][2] * matrix[2][1] -
                        matrix[1][1] * matrix[0][2] * matrix[2][3] - 
                        matrix[2][2] * matrix[1][3] * matrix[0][1]);

    resultado[0][1] = -(matrix[1][0] * matrix[2][2] * matrix[3][3] + 
                        matrix[2][0] * matrix[3][2] * matrix[1][3] + 
                        matrix[1][2] * matrix[2][3] * matrix[3][0] - 
                        matrix[1][3] * matrix[2][2] * matrix[3][0] - 
                        matrix[2][0] * matrix[1][2] * matrix[3][3] - 
                        matrix[2][3] * matrix[3][2] * matrix[1][0]);
    resultado[1][1] = matrix[0][0] * matrix[2][2] * matrix[3][3] + 
                        matrix[2][0] * matrix[3][2] * matrix[0][3] + 
                        matrix[0][2] * matrix[2][3] * matrix[3][0] - 
                        matrix[0][3] * matrix[2][2] * matrix[3][0] - 
                        matrix[2][0] * matrix[0][2] * matrix[3][3] - 
                        matrix[2][3] * matrix[3][2] * matrix[0][0];
    resultado[2][1] = -(matrix[0][0] * matrix[1][2] * matrix[3][3] + 
                        matrix[1][0] * matrix[3][2] * matrix[0][3] + 
                        matrix[0][2] * matrix[1][3] * matrix[3][0] - 
                        matrix[0][3] * matrix[1][2] * matrix[3][0] - 
                        matrix[1][0] * matrix[0][2] * matrix[3][3] - 
                        matrix[1][3] * matrix[3][2] * matrix[0][0]);
    resultado[3][1] = matrix[0][0] * matrix[1][2] * matrix[2][3] + 
                        matrix[1][0] * matrix[2][2] * matrix[0][3] + 
                        matrix[0][2] * matrix[1][3] * matrix[2][0] - 
                        matrix[0][3] * matrix[1][2] * matrix[2][0] - 
                        matrix[1][0] * matrix[0][2] * matrix[2][3] - 
                        matrix[1][3] * matrix[2][2] * matrix[0][0];

    resultado[0][2] = matrix[1][0] * matrix[2][1] * matrix[3][3] + 
                        matrix[2][0] * matrix[3][1] * matrix[1][3] + 
                        matrix[1][1] * matrix[2][3] * matrix[3][0] - 
                        matrix[1][3] * matrix[2][1] * matrix[3][0] - 
                        matrix[2][3] * matrix[3][1] * matrix[1][0] - 
                        matrix[2][0] * matrix[1][1] * matrix[3][3];

    resultado[1][2] = -(matrix[0][0] * matrix[2][1] * matrix[3][3] + 
                        matrix[2][0] * matrix[3][1] * matrix[0][3] + 
                        matrix[0][1] * matrix[2][3] * matrix[3][0] - 
                        matrix[0][3] * matrix[2][1] * matrix[3][0] - 
                        matrix[2][3] * matrix[3][1] * matrix[0][0] - 
                        matrix[2][0] * matrix[0][1] * matrix[3][3]);
    
    resultado[2][2] = matrix[0][0] * matrix[1][1] * matrix[3][3] + 
                        matrix[1][0] * matrix[3][1] * matrix[0][3] + 
                        matrix[0][1] * matrix[1][3] * matrix[3][0] - 
                        matrix[0][3] * matrix[1][1] * matrix[3][0] - 
                        matrix[1][3] * matrix[3][1] * matrix[0][0] - 
                        matrix[1][0] * matrix[0][1] * matrix[3][3];

    resultado[3][2] = -(matrix[0][0] * matrix[1][1] * matrix[2][3] + 
                        matrix[1][0] * matrix[2][1] * matrix[0][3] + 
                        matrix[0][1] * matrix[1][3] * matrix[2][0] - 
                        matrix[0][3] * matrix[1][1] * matrix[2][0] - 
                        matrix[1][3] * matrix[2][1] * matrix[0][0] - 
                        matrix[1][0] * matrix[0][1] * matrix[2][3]);


    resultado[0][3] = -(matrix[1][0] * matrix[2][1] * matrix[3][2] + 
                        matrix[2][0] * matrix[3][1] * matrix[1][2] + 
                        matrix[1][1] * matrix[2][2] * matrix[3][0] - 
                        matrix[1][2] * matrix[2][1] * matrix[3][0] - 
                        matrix[2][2] * matrix[3][1] * matrix[1][0] - 
                        matrix[2][0] * matrix[1][1] * matrix[3][2]);

    resultado[1][3] = matrix[0][0] * matrix[2][1] * matrix[3][2] + 
                        matrix[2][0] * matrix[3][1] * matrix[0][2] + 
                        matrix[0][1] * matrix[2][2] * matrix[3][0] - 
                        matrix[0][2] * matrix[2][1] * matrix[3][0] - 
                        matrix[2][2] * matrix[3][1] * matrix[0][0] - 
                        matrix[2][0] * matrix[0][1] * matrix[3][2];

    resultado[2][3] = -(matrix[0][0] * matrix[1][1] * matrix[3][2] + 
                        matrix[1][0] * matrix[3][1] * matrix[0][2] + 
                        matrix[0][1] * matrix[1][2] * matrix[3][0] - 
                        matrix[0][2] * matrix[1][1] * matrix[3][0] - 
                        matrix[1][2] * matrix[3][1] * matrix[0][0] - 
                        matrix[1][0] * matrix[0][1] * matrix[3][2]);

    resultado[3][3] = matrix[0][0] * matrix[1][1] * matrix[2][2] + 
                        matrix[1][0] * matrix[2][1] * matrix[0][2] + 
                        matrix[0][1] * matrix[1][2] * matrix[2][0] - 
                        matrix[0][2] * matrix[1][1] * matrix[2][0] - 
                        matrix[1][2] * matrix[2][1] * matrix[0][0] - 
                        matrix[1][0] * matrix[0][1] * matrix[2][2];
    return Matriz(resultado);
}

Matriz Matriz::traspuesta() const {
    float resultado[4][4];
    for(int i = 0; i < 4; i ++){
        for(int j = 0; j < 4; j ++){
            resultado[i][j] = matrix[j][i];
        }
    }
    return Matriz(resultado);
}

Matriz Matriz::operator+(const Matriz& m) const{
    float resultado[4][4];
    for(int i = 0; i < 4; i ++){
        for(int j = 0; j < 4; j ++){
            resultado[i][j] = matrix[i][j] + m.matrix[i][j];
        }
    }
    return Matriz(resultado);
}

Matriz Matriz::operator-(const Matriz& m) const{
    float resultado[4][4];
    for(int i = 0; i < 4; i ++){
        for(int j = 0; j < 4; j ++){
            resultado[i][j] = matrix[i][j] - m.matrix[i][j];
        }
    }
    return Matriz(resultado);
}

Matriz Matriz::operator*(const Matriz& m) const{
    float resultado[4][4];
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            for(int k = 0; k < 4; k ++)
                resultado[i][j] += matrix[i][k] * m.matrix[k][j];
        }
    }
    return Matriz(resultado);
}

Matriz Matriz::operator*(const int scalar) const{
    float resultado[4][4];
    for(int i = 0; i < 4; i ++){
        for(int j = 0; j < 4; j ++){
            resultado[i][j] = matrix[i][j] * scalar;
        }
    }
    return Matriz(resultado);
}

Matriz Matriz::operator/(const int scalar) const{
    float resultado[4][4];
    for(int i = 0; i < 4; i ++){
        for(int j = 0; j < 4; j ++){
            resultado[i][j] = matrix[i][j] / scalar;
        }
    }
    return Matriz(resultado);
}

bool Matriz::operator==(const Matriz& m) const{
    bool resultado = true;
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 0; j++){
            resultado = matrix[i][j] == m.matrix[i][j];
            if(!resultado){
                return resultado;
            }
        }
    }
    return resultado;
}


Matriz Matriz::inversa() const {
    Matriz traspuesta = adjunta().traspuesta();
    return traspuesta/det();
}

// Print
ostream& operator<<(ostream& os, const Matriz& m) {
    for(int i = 0; i < 4; i++){
        os << "( ";
        for(int j = 0; j < 4; j++){
            os << m.matrix[i][j] << " ";
        }
        os << ")";
    }
    return os;
}

