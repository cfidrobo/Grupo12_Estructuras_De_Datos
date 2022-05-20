/*      UNIVERSIDAD DE LAS FUERZAS ARMADAS
*       Transformar numero Decimal a Binario con Recursividad
*       Autor: Limones G. John J. - Cristian Idrobo
*       Fecha de creación: 19/05/2022
*       Fecha de modificación: 16/05/2022
*       Grupo: 12
*       Github: https://github.com/cfidrobo/Grupo12_Estructuras_De_Datos.git
*/
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include "conversor.h"

int main() {
    Conversor conversor;
    char binario[255];

    memset(binario, 0, 255);

    int decimal;
    std::cout << "ingresa el decimal:";
    std::cin >> decimal;
    
    conversor.decimalABinario(decimal, binario);

    printf("binario: %s\n", binario);
}
