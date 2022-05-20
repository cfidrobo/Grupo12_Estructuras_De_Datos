#include "conversor.h"

void Conversor::decimalABinario(int decimal, char* binario) {
    if (decimal == 0)
        strcat(binario, "0");
    else {
        decimalABinario(decimal / 2, binario);
        
        if(decimal % 2)
            strcat(binario, "1");
        else
            strcat(binario, "0");
    }
}
