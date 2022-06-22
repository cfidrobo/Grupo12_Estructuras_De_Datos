
/*      UNIVERSIDAD DE LAS FUERZAS ARMADAS
*       Ordenamiento Mezcla Natural
*       Autor: Cristian Idrobo, Jhon Limones, Paul Mena, Esteban Chablay
*       Fecha de creación: 22/06/2022
*       Fecha de modificación: 22/06/2022
*       Grupo: 8 y 12
*       Github: https://github.com/cfidrobo/Grupo12_Estructuras_De_Datos
*/

#include <iostream>
#include "arreglo.h"
#include "val.h"

int main(int, char**) {
    Arreglo<int> arreglo;

    do {
        float n = val::leerNumero("ingrese un numero: ");
        arreglo.agregar(n);
    } while (val::confirmar("Desea agregar otro numero?"));

    arreglo.imprimir();
    arreglo.ordenar();
    arreglo.imprimir();

    return 0;
}
