#pragma once

#include <vector>
#include "escena.hpp"
#include "rayo.hpp"

class Render {
    private:
        Escena escena;
        vector<Rayo*> rayos;

    public:

        // CONSTRUCTORES
        /**
         * @brief Constructor de Render
         * 
         * @param _escena Escena con la que intersectar los rayos
         * @param _rayos Rayos que intersectan la escena
         */
        Render(Escena _escena, vector<Rayo*> _rayos) : escena(_escena), rayos(_rayos) {};

};