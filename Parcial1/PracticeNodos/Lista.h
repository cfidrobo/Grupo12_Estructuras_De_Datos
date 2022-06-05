
#include "Nodo.h"
#ifndef NULL
#define NULL (0)
#endif

/**
 * .Creacion esqueleto clase "Lista" con sus metodos atributos
 */
class Lista {
public:
	Lista();
	void ingreso();
	void insertar(int);
	void mostrar();
	void eliminar();
	void sumaLista();
	void buscar();

private:
	Nodo* primero;
	Nodo* actual;
	bool listaVacia() {
		return (this->primero == NULL);
	}

};
