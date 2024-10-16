#include "punto3d.hpp"

// Constructor
Punto3D::Punto3D(float x_val, float y_val, float z_val) : x(x_val), y(y_val), z(z_val) {}

Punto3D::Punto3D(Punto3D origen, Direccion direccion, float distancia){
    Direccion normalizada = direccion.normalize();
    Direccion nuevaDir = normalizada*distancia;
    x = origen.getx() + nuevaDir.getx();
    y = origen.gety() + nuevaDir.gety();
    z = origen.getz() + nuevaDir.getz();
}

Punto3D Punto3D::restarPuntos(const Punto3D& otro) const{
    Punto3D nuevoPunto(x - otro.x, y - otro.y, z - otro.z);
    return nuevoPunto;
}

float Punto3D::getx() {
    return x;
}

float Punto3D::gety() {
    return y;
}
float Punto3D::getz() {
    return z;
}
// Operadores
Punto3D Punto3D::operator+(const Punto3D& otro) const {
    return Punto3D(x + otro.x, y + otro.y, z + otro.z);
}

Direccion Punto3D::operator-(const Punto3D& otro) const {
    return Direccion(x - otro.x, y - otro.y, z - otro.z);
}

Punto3D Punto3D::operator*(const float scalar) const {
    return Punto3D(x * scalar, y * scalar, z * scalar);
}

Punto3D Punto3D::operator/(const float scalar) const {
    return Punto3D(x / scalar, y / scalar, z / scalar);
}

// Comparadores
bool Punto3D::operator==(const Punto3D& otro) const {
    return (x == otro.x && y == otro.y && z == otro.z);
}

bool Punto3D::operator!=(const Punto3D& otro) const {
    return (x != otro.x && y != otro.y && z != otro.z);
}

bool Punto3D::operator>(const Punto3D& otro) const {
    return (x > otro.x && y > otro.y && z > otro.z);
}

bool Punto3D::operator<(const Punto3D& otro) const {
    return (x < otro.x && y < otro.y && z < otro.z);
}

bool Punto3D::operator>=(const Punto3D& otro) const {
    return (x >= otro.x && y >= otro.y && z >= otro.z);
}

bool Punto3D::operator<=(const Punto3D& otro) const {
    return (x <= otro.x && y <= otro.y && z <= otro.z);
}

// Print
ostream& operator<<(ostream& os, const Punto3D& p) {
    os << "(" << p.x << ", " << p.y << ", " << p.z << ")";
    return os;
}