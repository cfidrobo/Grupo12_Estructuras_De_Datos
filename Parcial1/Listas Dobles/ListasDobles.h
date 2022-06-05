#ifndef LISTASDOBLES_H
#define LISTASDOBLES_H
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <string.h>

#define ASCENDENTE 1
#define DESCENDENTE 0

class ListasDobles
{
	public:
		ListasDobles *siguiente;
		ListasDobles *anterior;	
		int valor;
	public:
		ListasDobles a();
		void Insertar(ListasDobles *, int);
		void Borrar(ListasDobles *, int);
		void BorrarLista(ListasDobles *);
		void MostrarLista(ListasDobles * , int);
	
};

#endif
