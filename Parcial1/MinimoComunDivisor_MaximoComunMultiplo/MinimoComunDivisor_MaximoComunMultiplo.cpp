/*      UNIVERSIDAD DE LAS FUERZAS ARMADAS
*       Recursividad MinimoComunMultiplo MaximoComunDivisor
*       Autor: Limones G. John J. - Cristian Idrobo
*       Fecha de creación: 16/05/2022
*       Fecha de modificación: --/--/----
*       Grupo: 12
*       Github: https://github.com/cfidrobo/Grupo12_Estructuras_De_Datos
*/


#include <iostream>
#include "MCM.h"
#include "MCD.h"

using namespace std;



int main(int argc, char** argv) {
	MCM recursividadObj1;
	MCD recursividadObj2;
	int n1, n2;
	cout << "ingrese el numero 1:" << endl;
	cin >> n1;
	cout << "ingrese el numero 2:" << endl;
	cin >> n2;

	cout << "El maximo comun divisor es: " << recursividadObj1.MinimoComunMultiplo(n1, n2) << endl;
	cout << "El minimo comun multiplo es: " << recursividadObj2.MaximoComunDivisor(n1, n2) << endl;

	return 0;
}