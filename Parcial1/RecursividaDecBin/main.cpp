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
