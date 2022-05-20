#include <iostream>
#include<string.h>
#include<stdlib.h>

#define BIN 2
using namespace std;
void decimalBinario(int,char[]);
void decimalBinario(int val, char cad[]){
if(val>=1){
decimalBinario((val/BIN),cad);
strcpy(cad,itoa((val%BIN),cad,10));
}
strcat(cad,"\0");
//printf("%s",cad);
}

int main(int argc, char** argv) {
char cad[10];
decimalBinario(124,cad);
cout<<"Decimal a binario %s"<<cad;
return 0;
}
