// g++ test_espacioColor.cpp ../imagen/espacioColor/hsl.cpp ../imagen/espacioColor/hsv.cpp ../imagen/espacioColor/rgb.cpp -o testEspacioColor
#include "../imagen/espacioColor/rgb.hpp"
#include "../imagen/espacioColor/hsv.hpp"
#include "../imagen/espacioColor/hsl.hpp"

#include <iostream>


int main(){
    RGB rgb(2, 3, 5);
    cout << rgb;
    
}