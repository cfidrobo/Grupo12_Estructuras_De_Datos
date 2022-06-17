#include <iostream>

#include "pila.h"
using namespace std;

pila* primero=NULL;
void pila::insertarNodo(){
	pila* nuevo = new pila();
	cout << " Ingrese el dato que contendra el nuevo Nodo: ";
	cin >> nuevo->dato;
	nuevo->siguiente = primero;
	primero = nuevo;
	cout << endl << " Nodo Ingresado " << endl << endl;
}

void pila::buscarNodo(){
	pila* actual = new pila();
	actual = primero;
	int nodoBuscado = 0;
	bool encontrado = false;
	cout << " Ingrese el dato del Nodo a Buscar: ";
	cin >> nodoBuscado;
	if(primero!=NULL){
		while(actual!=NULL && encontrado != true){
			
			if(actual->dato == nodoBuscado){
				cout << endl << " Nodo con el dato ( " << nodoBuscado << " ) Encontrado" << endl << endl;
				encontrado = true;
			}
			
			actual = actual->siguiente;
		}
		if(encontrado==false){
			cout << endl << " Nodo no Encontrado" << endl << endl;
		}
	}else{
		cout << endl << " La Pila se encuentra vacia" << endl << endl;
	}
}

void pila::modificarNodo(){
	pila* actual = new pila();
	actual = primero;
	int nodoBuscado = 0;
	bool encontrado = false;
	cout << " Ingrese el dato del Nodo a Buscar par Modificar: ";
	cin >> nodoBuscado;
	if(primero!=NULL){
		while(actual!=NULL && encontrado != true){
			
			if(actual->dato == nodoBuscado){
				cout << endl << " Nodo con el dato ( " << nodoBuscado << " ) Encontrado";
				cout << endl << " Ingrese el nuevo dato para este Nodo: ";
				cin >> actual->dato;
				cout << endl << " Nodo Modificado " << endl << endl;
				encontrado = true;
			}
			
			actual = actual->siguiente;
		}
		if(encontrado==false){
			cout << endl << " Nodo no Encontrado" << endl << endl;
		}
	}else{
		cout << endl << " La Pila se encuentra vacia" << endl << endl;
	}	
}

// primero = 9       actual =  9    anterior = null     nodoBuscado = 9   encontrado = false            4,7,8,9

//PILA  -     9 -> 8 -> 7 -> 4 -> null                       9   8  7  4

void pila::eliminarNodo(){
	pila* actual = new pila();
	actual = primero;
	pila* anterior = new pila();
	anterior = NULL;
	int nodoBuscado = 0;
	bool encontrado = false;
	cout << " Ingrese el dato del Nodo a Buscar para Eliminar: ";
	cin >> nodoBuscado;
	if(primero!=NULL){
		while(actual!=NULL && encontrado != true){
			
			if(actual->dato == nodoBuscado){
				cout << endl << " Nodo con el dato ( " << nodoBuscado << " ) Encontrado";
				
				if(actual == primero){
					primero = primero->siguiente;
				}else{
					anterior->siguiente = actual->siguiente;
				}
				cout << endl << " Nodo Eliminado" << endl << endl;
				encontrado = true;
			}
			anterior = actual;
			actual = actual->siguiente;
		}
		if(encontrado==false){
			cout << endl << " Nodo no Encontrado" << endl << endl;
		}
	}else{
		cout << endl << " La Pila se encuentra vacia" << endl << endl;
	}	
}

void pila::desplegarPila(){
	pila* actual = new pila();
	actual = primero;
	if(primero!=NULL){
		while(actual!=NULL){
			cout << endl << " " << actual->dato; 
			actual = actual->siguiente;
			
		}
	}else{
		cout << endl << " La Pila se encuentra vacia" << endl << endl;
	}
}



