#include "ListaDoble.h"

ListaDoble::ListaDoble() {
	cabeza = new NodoDoble();
	cola = new NodoDoble();
	cabeza->ultimo = NULL;
	cabeza->siguiente = cola;
	cola->siguiente = NULL;
	cola->ultimo = cabeza;
}
ListaDoble::~ListaDoble() {
	delete cabeza;
	delete cola;
}
bool ListaDoble::insertarDato(int dato) {
	return false;
}
void ListaDoble::listaDobleTetris(int tamanio) {
	int cont = 0;
	do {
		NodoDoble* nuevoNodo = new NodoDoble();
		nuevoNodo->dato = 0;
		nuevoNodo->ultimo = cola->ultimo;
		nuevoNodo->siguiente = cola;
		cola->ultimo->siguiente = nuevoNodo;
		cola->ultimo = nuevoNodo;
		cont++;
	} while (cont != tamanio);
}
void ListaDoble::imprimirLista() {
	NodoDoble* aux = cabeza->siguiente;
	while (aux != cola) {
		if (aux->dato == 0 || aux->dato == -1) {
			std::cout << " ";
			aux = aux->siguiente;
		}
		else {
			std::cout << aux->dato;
			aux = aux->siguiente;
		}
	}
}
void ListaDoble::insertarEnLista(Posicion* pos, int num, int limVer, int limHor) {
	int cont = 0;
	if (pos->getPosY() >= limVer - 1) {
		NodoDoble* aux = new NodoDoble();
		aux = cabeza->siguiente;
		while (cont != pos->getPosX() - 3) {
			aux = aux->siguiente;
			cont++;
		}
		if (cont % 3 == 0 && (aux->dato == 0 || aux->dato == -1)) {
			if (aux->dato == num) {
				aux->dato = -1;
			}
			else {
				aux->dato = num;
			}
		}
		else {
			if (pos->getPosX() - 3 == 0) {
				if (aux->dato == num) {
					aux->dato = -1;
					return;
				}
				cont = 0;
				aux = cabeza->siguiente;
				while (aux != cola) {
					if ((aux->dato == 0 || aux->dato == -1) && cont % 3 == 0) {
						aux->dato = num;
						return;
					}
					else {
						aux = aux->siguiente;
						cont++;
					}
				}
			}
			else if (cont == limHor - 8) {
				if (aux->dato == num) {
					aux->dato = -1;
					return;
				}
				cont = pos->getPosX() - 3;
				aux = cola->ultimo;
				while (aux != cabeza) {
					if ((aux->dato == 0 || aux->dato == -1) && cont % 3 == 0) {
						aux->dato = num;
						return;
					}
					else {
						aux = aux->ultimo;
						cont--;
					}
				}
			}
			else if (cont % 3 == 0) {
				if (aux->dato == num) {
					aux->dato = -1;
					return;
				}
				cont = 0;
				aux = cabeza->siguiente;
				while (aux != cola) {
					if ((aux->dato == 0 || aux->dato == -1) && cont % 3 == 0) {
						aux->dato = num;
						return;
					}
					else {
						aux = aux->siguiente;
						cont++;
					}
				}
				if (aux->dato == num) {
					aux->dato = -1;
					return;
				}
				cont = pos->getPosX() - 3;
				aux = cola->ultimo;
				while (aux != cabeza) {
					if ((aux->dato == 0 || aux->dato == -1) && cont % 3 == 0) {
						aux->dato = num;
						return;
					}
					else {
						aux = aux->ultimo;
						cont--;
					}
				}
			}
		}
	}
}
bool ListaDoble::perdio(int elementos)
{
	int cont = 0;
	int cont2 = 0;
	NodoDoble* aux = new NodoDoble();
	aux = cabeza->siguiente;
	while (aux != cola) {
		if (aux->dato != 0) {
			cont++;
		}
		if (aux->dato == -1) {
			cont2++;
		}
		aux = aux->siguiente;
	}
	if (cont == elementos && cont2 == 0) {
		return false;
	}
	return true;
}

bool ListaDoble::gano(int elementos) {
	int cont = 0;
	int cont2 = 0;
	int cont3 = 0;
	int total = 0;
	NodoDoble* aux = new NodoDoble();
	aux = cabeza->siguiente;
	while (aux != cola) {
		if (aux->dato == -1) {
			cont++;
		}
		if (aux->dato == 0 && cont3 % 3 == 0) {
			cont2++;
		}
		aux = aux->siguiente;
		cont3++;
	}
	if (cont2 == elementos) {
		cont2--;
	}
	total = cont + cont2;
	if (total == elementos) {
		return false;
	}
	return true;
}

