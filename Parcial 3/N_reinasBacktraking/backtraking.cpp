#include <iostream>
#include <stdio.h>
#include "N_reinas.h"
#include "val.h"

using namespace std;

int main(int argc, char* argv[]) {
	SetConsoleOutputCP(65001);
	bool repetir = true;
	int cant;
	do {
		cant = val::leerNumero("ingrese el numero de reinas de 4 a 8: ");
		if (cant > 8 || cant < 4) {
			repetir = true;
		}
		else {
			repetir = false;
		}
	} while (repetir);
	cout << endl;
	int* reinas = new int[cant];

	for (int i = 0;i < cant;i++) {
		reinas[i] = -1;
	}
	Nreinas(reinas, cant, k);
	cout << endl;
	
	//definiendo una matriz 2d 100 X 100 (se puede definir según su rango de entrada)
	int tablero[10][10];
	//inicializando la matriz 2d con valor inicial 0
	memset(tablero, 0, sizeof(tablero));
	//función definida para el enfoque de retroceso
	backtrackingRecursividad(tablero, 0, cant);

	return 0;
}