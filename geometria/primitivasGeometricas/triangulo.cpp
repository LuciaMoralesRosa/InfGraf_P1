#include "triangulo.hpp"

Triangulo::Triangulo(Punto3D p1, Punto3D p2, Punto3D p3, Textura _textura) : a(p1), b(p2), c(p3), Primitiva(_textura, "Triangulo") {
    Direccion d1 = p2 - p1;
    Direccion d2 = p3 - p1;
    normal = d1.vector_product(d2).normalize();
}

Punto3D Triangulo::getA(){
    return a;
}

Punto3D Triangulo::getB(){
    return b;
} 

Punto3D Triangulo::getC(){
    return c;
} 

Direccion Triangulo::getNormal(){
    return normal;
} 

Interseccion Triangulo::interseccionRayo(Rayo rayo) const{
    Interseccion resultado;
    resultado.intersecta = false; // Inicializa a no intersecta

    // Vectores de los vértices del triángulo
    Punto3D v0 = a;
    Punto3D v1 = b;
    Punto3D v2 = c;

    // Calcula los vectores
    Direccion e1 = v1 - v0; // v1 - v0
    Direccion e2 = v2 - v0; // v2 - v0

    // Producto cruzado
    Direccion p = rayo.getDireccion().vector_product(e2);
    float det = e1.dot_product(p);

    // Tolerancia para determinar si el rayo es paralelo al triángulo
    const float EPSILON = 1e-8;

    // Verificar si el rayo es paralelo al triángulo
    if (det > -EPSILON && det < EPSILON) {
        return resultado; // No hay intersección
    }

    float invDet = 1.0f / det;

    // Cálculo de las coordenadas Barycentric
    Direccion t = rayo.getOrigen() - v0;
    float u = t.dot_product(p) * invDet;

    if (u < 0.0f || u > 1.0f) {
        return resultado; // No hay intersección
    }

    Direccion q = t.vector_product(e1);
    float v = rayo.getDireccion().dot_product(q) * invDet;

    if (v < 0.0f || u + v > 1.0f) {
        return resultado; // No hay intersección
    }

    // Calcular la distancia hasta el punto de intersección
    float tIntersect = e2.dot_product(q) * invDet;

    if (tIntersect > EPSILON) { // Asegura que la intersección esté frente al rayo
        resultado.intersecta = true;
        resultado.distancia.push_back(tIntersect);
        resultado.puntoInterseccion.push_back(Punto3D(
            rayo.getOrigen().getx() + rayo.getDireccion().getx() * tIntersect,
            rayo.getOrigen().gety() + rayo.getDireccion().gety() * tIntersect,
            rayo.getOrigen().getz() + rayo.getDireccion().getz() * tIntersect
        ));
        //resultado.normal = this->normal;
        resultado.colorPrimitiva = getColor();
    }

    return resultado;
}

