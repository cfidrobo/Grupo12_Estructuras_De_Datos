/*      UNIVERSIDAD DE LAS FUERZAS ARMADAS
*       Aplicativo - transformar de string a entero
*       Autor: Limones G. John J. - Cristian Idrobo
*       Fecha de creación: 10/05/2022
*       Fecha de modificación: --/--/----
*       Grupo: 12
*       Github: https://github.com/cfidrobo/Grupo12_Estructuras_De_Datos.git
*/

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