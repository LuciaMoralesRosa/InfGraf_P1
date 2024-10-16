#pragma once
#include "boundingBox.hpp"
#include <list>

using namespace std;

class Nodo{
    public:
        BoundingBox bounds;
        list<BVHTriangulo> listaTriangulos;
        Nodo hijo1;
        Nodo hijo2;
        
};