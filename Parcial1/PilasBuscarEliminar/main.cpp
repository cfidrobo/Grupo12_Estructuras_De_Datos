#include <iostream>
#include <stdlib.h>
#include "pila.h"

using namespace std;

int main(int argc, char** argv){

	pila *nd=NULL;

	int opcion_menu=0;
	do
	{
	
		
		cout << endl << "|-------------------------------------|";
		cout << endl << "|              ? PILA ?               |";
		cout << endl << "|------------------|------------------|";
		cout << endl << "| 1. Insertar      | 4. Eliminar      |";
		cout << endl << "| 2. Buscar        | 5. Desplegar     |";
		cout << endl << "| 3. Modificar     | 6. Salir         |";
		cout << endl << "|------------------|------------------|";
		cout << endl << endl << " Escoja una Opcion: ";
		cin >> opcion_menu;
		switch(opcion_menu ){
			case 1:
				//system("cls");
				cout << endl << endl << " INSERTA NODO EN LA PILA " << endl << endl;
				nd->insertarNodo();
				break;
			case 2:
				cout << endl << endl << " BUSCAR UN NODO EN LA PILA " << endl << endl;
				nd->buscarNodo();
				break;
			case 3:
				cout << endl << endl << " MODIFICAR UN NODO DE LA PILA " << endl << endl;
				nd->modificarNodo();
				break;
			case 4:
				cout << endl << endl << " ELIMINAR UN NODO DE LA PILA " << endl << endl;
				nd->eliminarNodo();
				break;
			case 5: 
				cout << endl << endl << " DESPLEGAR PILA DE NODOS " << endl << endl;
				nd->desplegarPila();
				break;
			case 6:
				cout << endl << endl << " Programa finalizado..." << endl << endl;
				break;
			default:
				cout << endl << endl << " Opcion No Valida " << endl << endl;
			}
	} while (opcion_menu != 6);
	return 0;
}










