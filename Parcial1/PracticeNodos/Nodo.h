
#pragma once
/**
 * .Definir esqueleto de la clase con sus atributos y metodos
 */
class Nodo {
public:
	Nodo(int val, Nodo*);
	friend class Lista;
private:
	int valor;
	Nodo* siguiente;


};