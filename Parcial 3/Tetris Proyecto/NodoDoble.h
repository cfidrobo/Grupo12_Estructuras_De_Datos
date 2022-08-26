#pragma once
#include <cstddef>
class NodoDoble {
private:
	int dato;
	NodoDoble* siguiente;
	NodoDoble* ultimo;
public:
	NodoDoble();
	~NodoDoble();
	friend class ListaDoble;
};