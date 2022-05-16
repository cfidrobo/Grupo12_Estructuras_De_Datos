/*      UNIVERSIDAD DE LAS FUERZAS ARMADAS
*       Aplicativo - transformar de string a entero
*       Autor: Limones G. John J. - Cristian Idrobo
*       Fecha de creaci�n: 10/05/2022
*       Fecha de modificaci�n: --/--/----
*       Grupo: 12
*       Github: https://github.com/cfidrobo/Grupo12_Estructuras_De_Datos.git
*/

#include <iostream>
#include "ingresar.h"

int main(int argc, char **argv) {
	Ingresar ingresarObj;
	std::string entrada;

	std::cout << "ingrese un numero: ";
	std::cin >> entrada;

	try {
		int transformado = ingresarObj.ingresar(entrada);
		std::cout << transformado;
	} catch (std::exception ex) {
		std::cout << "numero invalido";
	}

	return 0;
}
