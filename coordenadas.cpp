#include "coordenadas.hpp"
    
//Constructor
Coordenadas::Coordenadas(float x_val, float y_val, float z_val, float is_point_val): x(x_val), y(y_val), z(z_val), is_point(is_point_val) {}

//Operadores
Coordenadas Coordenadas::translate(const float x_displacement, const float y_displacement, const float z_displacement) const {
    float m[4][4] = { 
        {1, 0, 0, x_displacement},
        {0, 1, 0, y_displacement},
        {0, 0, 1, z_displacement},
        {0, 0, 0, 1} };
    return Coordenadas(multiply(m));
}

Coordenadas Coordenadas::scale(const float x_factor, const float y_factor, const float z_factor) const {
    float m[4][4] = { 
        {x_factor, 0, 0, 0},
        {0, y_factor, 0, 0},
        {0, 0, z_factor, 0},
        {0, 0, 0, 1} };
    return Coordenadas(multiply(m));
}

Coordenadas Coordenadas::rotate_x_axis(const double angle) const {
    float radians = gradesToRadians(angle);
    float m[4][4] = { 
        {1, 0, 0, 0},
        {0, (float)cos(radians), -(float)sin(radians), 0},
        {0, (float)sin(radians), (float)cos(radians), 0},
        {0, 0, 0, 1} };
    return Coordenadas(multiply(m));
}

Coordenadas Coordenadas::rotate_y_axis(const double angle) const {
    float radians = gradesToRadians(angle);
    float m[4][4] = { 
        {(float)cos(radians), 0, (float)sin(radians), 0},
        {0, 1, 0, 0},
        {-(float)sin(radians), 0, (float)cos(radians), 0},
        {0, 0, 0, 1} };
    return Coordenadas(multiply(m));
}

Coordenadas Coordenadas::rotate_z_axis(const double angle) const {
    float radians = gradesToRadians(angle);
    float m[4][4] = { 
        {(float)cos(radians), -(float)sin(radians), 0, 0},
        {(float)sin(radians), (float)cos(radians), 0, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 1} };
    return Coordenadas(multiply(m));
}

Coordenadas Coordenadas::change_basis(const Coordenadas& o, const Coordenadas& u, const Coordenadas& v, const Coordenadas& w) const {
    float m[4][4] = { 
        {u.x, v.x, w.x, o.x},
        {u.y, v.y, w.y, o.y},
        {u.z, v.z, w.z, o.z},
        {u.is_point, v.is_point, w.is_point, o.is_point}};
    return Coordenadas(multiply(m));
}

Coordenadas Coordenadas::multiply(const float matrix[4][4]) const {
    return Coordenadas(dot_product(matrix[0]), dot_product(matrix[1]), dot_product(matrix[2]), dot_product(matrix[3]));
}

float Coordenadas::dot_product(const float matrix[4]) const {
    return matrix[0] * x + matrix[1] * y + matrix[2] * z + matrix[3] * is_point;
}

// Print
ostream& operator<<(ostream& os, const Coordenadas& c) {
    os << "( " << c.x << ", " << c.y << ", " << c.z << ", " << c.is_point << " )";
    return os;
}
