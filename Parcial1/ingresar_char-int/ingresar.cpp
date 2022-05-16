#include "ingresar.h"
#include <string>

int Ingresar::ingresar(std::string valor) {
    int dato = std::stoi(valor);
    return dato;
}