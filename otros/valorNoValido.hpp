#include <iostream>
#include <exception>

using namespace std;

class ValorNoValido : public exception {
    public:
        const char * what () const noexcept override {
            return "El parametro introducido no es un valor valido";
        }
};