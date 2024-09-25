#include "angulos.hpp"

float radiansToGrades(float angulo) {
    return angulo * (180.0f / M_PI);
}

float gradesToRadians(float angulo) {
    return angulo * (M_PI / 180.0f);
}

