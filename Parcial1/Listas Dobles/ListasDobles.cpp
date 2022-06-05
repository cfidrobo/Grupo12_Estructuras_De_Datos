#include "listasdobles.h"
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <string.h>

void ListasDobles::Insertar(ListasDobles *lista, int v)
{
	ListasDobles *nuevo;
	ListasDobles *actual;
	/* Crear un nodo nuevo */
	nuevo = (ListasDobles *)malloc(sizeof(ListasDobles *));

	// nuevo = new ListasDobles*;
	nuevo->valor = v;
	/* Colocamos actual en la primera posicion de la lista */
	actual = lista;
	if (actual)
		while (actual->anterior)
			actual = actual->anterior;
	/* Si la lista esta vacia o el primer miembro es mayor que el nuevo */
	if (!actual || actual->valor > v)
	{
		/* A�adimos la lista a continuacion del nuevo nodo */
		nuevo->siguiente = actual;
		nuevo->anterior = NULL;
		if (actual)
			actual->anterior = nuevo;
		if (!lista)
			lista = nuevo;
	}
	else
	{
		/* Avanzamos hasta el �ltimo elemento o hasta que el siguiente tenga
		un valor mayor que v */
		while (actual->siguiente && actual->siguiente->valor <= v)
			actual = actual->siguiente;
		/* Insertamos el nuevo nodo despues del nodo anterior */
		nuevo->siguiente = actual->siguiente;
		actual->siguiente = nuevo;
		nuevo->anterior = actual;
		if (nuevo->siguiente)
			nuevo->siguiente->anterior = nuevo;
	}
}

void ListasDobles::Borrar(ListasDobles *lista, int v)
{
	ListasDobles *nodo;
	/* Buscar el nodo de valor v */
	nodo = lista;
	while (nodo && nodo->valor < v)
		nodo = nodo->siguiente;
	while (nodo && nodo->valor > v)
		nodo = nodo->anterior;
	/* El valor v no est� en la lista */
	if (!nodo || nodo->valor != v)
		return;
	/* Borrar el nodo */
	/* Si lista apunta al nodo que queremos borrar, apuntar a otro */
	if (nodo == lista)
		if (nodo->anterior)
			lista = nodo->anterior;
		else
			lista = nodo->siguiente;
	if (nodo->anterior) /* no es el primer elemento */
		nodo->anterior->siguiente = nodo->siguiente;
	if (nodo->siguiente) /* no es el ultimo nodo */
		nodo->siguiente->anterior = nodo->anterior;
	free(nodo);
}

void ListasDobles::BorrarLista(ListasDobles *lista)
{
	ListasDobles *nodo;
	ListasDobles *actual;

	actual = lista;
	while (actual->anterior)
		actual = actual->anterior;
	while (actual)
	{
		nodo = actual;
		actual = actual->siguiente;
		free(nodo);
	}
	lista = NULL;
}

void ListasDobles::MostrarLista(ListasDobles *lista, int orden)
{
	ListasDobles *nodo = lista;
	
	if (!lista)
		printf("Lista vacia");
	nodo = lista;
	if (orden == ASCENDENTE)
	{
		while (nodo->anterior)
			nodo = nodo->anterior;
		printf("Orden ascendente: ");
		while (nodo)
		{
			printf("%d -> ", nodo->valor);
			nodo = nodo->siguiente;
		}
	}
	else
	{
		while (nodo->siguiente)
			nodo = nodo->siguiente;
		printf("Orden descendente: ");
		while (nodo)
		{
			printf("%d -> ", nodo->valor);
			nodo = nodo->anterior;
		}
	}
	printf("\n");
}
