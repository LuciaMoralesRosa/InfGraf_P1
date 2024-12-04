#pragma once
#include <vector>
#include <random>
#include <ctime>
#include "../geometria/punto3d.hpp"
#include "../geometria/direccion.hpp"
#include "../geometria/matriz4x4.hpp"
//#include "../geometria/transformaciones.hpp"
#include "../geometria/coordenada.hpp"




using namespace std;

float calcularMAX(vector<float> vector);
float calcularMIN(vector<float> vector);
float calcularMedia(vector<float> vector);
bool algunPuntoEsMenor(vector<float> vector, float distancia);
Punto3D sumaPuntoDireccion(Punto3D punto, Direccion direccion);
float generacionNumeroAleatorio();

//Direccion muestreoCoseno(const Direccion& u, const Direccion& v, const Direccion& normal, const Punto3D& origen);