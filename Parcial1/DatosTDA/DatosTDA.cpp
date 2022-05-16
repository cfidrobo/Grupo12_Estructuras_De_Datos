#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include "Conversion.h"
#include "DatosIngresados.h"

using namespace std;

int main() {
    DatosIngresados lector;
    ConversorDatos conversor;

    string cadena = lector.leerCadenaNumerica("ingrese un numero: ");
    int valorEntero = conversor.convertirEnEntero(cadena);

    
    cout << endl << endl << "Entero leido: " << valorEntero << endl << endl;
    

    cadena = lector.leerCadenaNumerica("ingrese otro numero: ");
    double valorReal = conversor.convertirEnReal(cadena);

    cout << endl << endl;
    cout << "Real leido: " << valorReal << endl;
}