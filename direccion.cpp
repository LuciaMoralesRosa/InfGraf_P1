#include "direccion.hpp"
    
//Constructor
Direccion::Direccion(float x_val, float y_val, float z_val) : x(x_val), y(y_val), z(z_val) {}

//Operadores
Direccion Direccion::operator+(const Direccion& dir) const {
    return Direccion(x+dir.x, y+dir.y, z+dir.z);
}

Direccion Direccion::operator-(const Direccion& dir) const {
    return Direccion(x-dir.x, y-dir.y, z-dir.z);
}

Direccion Direccion::operator*(const int scalar) const {
    return Direccion(x*scalar, y*scalar, z*scalar);
}

Direccion Direccion::operator/(const int scalar) const {
    return Direccion(x/scalar, y/scalar, z/scalar);
}

float Direccion::dot_product(const Direccion& dir) const {
    return x*dir.x + y*dir.y + z*dir.z;
}

Direccion Direccion::vector_product(const Direccion& dir) const {
    return Direccion(y*dir.z - z*dir.y, z*dir.x - x*dir.z, x*dir.y - y*dir.x);
}

float Direccion::modulus() const {
    return sqrt(x*x + y*y + z*z);
}

Direccion Direccion::normalize() const {
    float mod = modulus();
    if (mod > 0) {
        return Direccion(x / mod, y / mod, z / mod);
    } else {
        // puede que lanzar una excepcion
        return Direccion(0, 0, 0);
    }
}

// Comparadores
bool Direccion::operator==(const Direccion& otro) const {
    return (x == otro.x && y == otro.y && z == otro.z);
}

bool Direccion::operator!=(const Direccion& otro) const {
    return (x != otro.x && y != otro.y && z != otro.z);
}

bool Direccion::operator>(const Direccion& otro) const {
    return (x > otro.x && y > otro.y && z > otro.z);
}

bool Direccion::operator<(const Direccion& otro) const {
    return (x < otro.x && y < otro.y && z < otro.z);
}

bool Direccion::operator>=(const Direccion& otro) const {
    return (x >= otro.x && y >= otro.y && z >= otro.z);
}

bool Direccion::operator<=(const Direccion& otro) const {
    return (x <= otro.x && y <= otro.y && z <= otro.z);
}

bool Direccion::is_normalized() const {
    float length_squared = x*x + y*y + z*z;
    const float epsilon = 1e-6;
    return fabs(length_squared - 1.0) < epsilon;
}

bool Direccion::is_perpendicular(const Direccion& dir) const {
    return vector_product(dir) == 0;
}

float Direccion::obtenerAngulo(const Direccion& dir) const {
    Direccion actual = Direccion(x, y, z);
    float coseno = (actual.dot_product(dir)) / (actual.modulus() * dir.modulus());
    return acosf(coseno) * 180/M_PI;
}

// Print
ostream& operator<<(ostream& os, const Direccion& d) {
    os << "-->(" << d.x << ", " << d.y << ", " << d.z << ")";
    return os;
}
