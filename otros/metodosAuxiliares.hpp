#pragma once
#include <vector>
#include <random>
#include <ctime>
#include "../geometria/punto3d.hpp"
#include "../geometria/direccion.hpp"

using namespace std;

float calcularMAX(vector<float> vector);
float calcularMIN(vector<float> vector);
float calcularMedia(vector<float> vector);
bool algunPuntoEsMenor(vector<float> vector, float distancia);
Punto3D sumaPuntoDireccion(Punto3D punto, Direccion direccion);
float generacionNumeroAleatorio();