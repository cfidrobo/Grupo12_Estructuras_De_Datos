/*      UNIVERSIDAD DE LAS FUERZAS ARMADAS
*       Aplicativo Recursividad
*       Autor: Limones G. John J. - Cristian Idrobo
*       Fecha de creación: 16/05/2022
*       Fecha de modificación: --/--/----
*       Grupo: 12
*       Github: https://github.com/cfidrobo/Grupo12_Estructuras_De_Datos
*/

#include <iostream>
#include "lista_simple.h"

using namespace std;

int main()
{
	ListaSimple<int> lista;

	for (int i = 1; i <= 5; i++) {
		lista.insertar_final(i);
	}

	lista.insertar_inicio(7);
	lista.insertar_inicio(8);

	lista.recorrer([](int valor) {
		cout << "-> " << valor << endl;
		});

	lista.eliminar(6);

	cout << endl << endl;

	lista.recorrer([](int valor) {
		cout << "-> " << valor << endl;
		});

	lista.recorrer_nodos([](Nodo<int>* nodo) {
		int valor = nodo->get_valor();
		nodo->set_valor(valor * 2);
		});

	cout << endl << endl;

	lista.recorrer([](int valor) {
		cout << "=> " << valor << endl;
		});

	cout << endl << endl;

	Nodo<int>* encontrado = lista.buscar(2);

	if (encontrado == nullptr) {
		cout << "no se encontro en la lista" << endl;
	}
	else {
		cout << "se encontro el elemento: ";
		cout << encontrado->get_valor() << endl;
	}

	return 0;
}
