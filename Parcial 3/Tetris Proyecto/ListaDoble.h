#pragma once
#include <iostream>
#include <math.h>
#include "NodoDoble.h"
#include "Posicion.h"

class ListaDoble {
private:
	NodoDoble* cabeza;
	NodoDoble* cola;
public:
	ListaDoble();
	~ListaDoble();
	bool insertarDato(int dato);
	void listaDobleTetris(int tamanio);
	void imprimirLista();
	void insertarEnLista(Posicion* pos, int num, int limVer, int limHor);
	bool perdio(int elementos);
	bool gano(int elementos);
};