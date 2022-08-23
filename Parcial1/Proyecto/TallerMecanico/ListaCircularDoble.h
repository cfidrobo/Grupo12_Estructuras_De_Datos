#pragma once
#include "nodo.h"
#include <functional>
#include <iostream>

template<typename T>
class ListaCircularDoble {
public:
	ListaCircularDoble() {}
    void insertarFinal(T valor);
    void insertarInicio(T valor);
    void insertarEn(int indice, T valor);
    void eliminarEn(int indice);
	void eliminar(std::function<bool(T valor)>);
	Nodo<T>* obtenerCabeza();
    Nodo<T>* obtenerCola();
    Nodo<T>* obtenerNodo(int indice);
    Nodo<T>* buscar(std::function<bool(T valor)>);
    void recorrer(std::function<void(T valor)>);
    bool estaVacio();
    int total();

private:
    Nodo<T>* cabeza = nullptr;
    int tamanio = 0;
};

template<typename T>
void ListaCircularDoble<T>::insertarFinal(T valor)
{
    Nodo<T>* nodo = new Nodo<T>(valor);

    if (cabeza == nullptr) {
		cabeza = nodo;
		cabeza->setAnterior(cabeza);
		cabeza->setSiguiente(cabeza);
		tamanio++;
	} else {
		Nodo<T>* cola = obtenerCola();
		cola->setSiguiente(nodo);
		nodo->setAnterior(cola);
		nodo->setSiguiente(cabeza);
		cabeza->setAnterior(nodo);
		tamanio++;
    }
}

template<typename T>
void ListaCircularDoble<T>::insertarInicio(T valor)
{
    Nodo<T>* nodo = new Nodo<T>(valor);

    if (estaVacio()) {
        insertarFinal(valor);
        return;
    }

    Nodo<T>* aux = cabeza;

    cabeza = nodo;
	cabeza->setSiguiente(aux);
	cabeza->setAnterior(aux->setAnterior());
	aux->setAnterior()->setSiguiente(cabeza);
	aux->setAnterior(cabeza);
	tamanio++;
}

template<typename T>
void ListaCircularDoble<T>::insertarEn(int indice, T valor)
{
    if (indice < 0 || indice >= tamanio) {
        return;
    }

    if (tamanio == 1) {
		insertarInicio(valor);
    }
    else if (indice == 0) {
        insertarInicio(valor);
    }
    else if (indice == tamanio - 1) {
        insertarFinal(valor);
    }
    else {
        Nodo<T>* objetivo = obtenerNodo(indice);
        Nodo<T>* anterior = objetivo->setAnterior();
        Nodo<T>* siguiente = objetivo->setSiguiente();
        Nodo<T>* nodo = new Nodo<T>(valor);

        anterior->setSiguiente(nodo);
		nodo->setAnterior(anterior);
		nodo->setSiguiente(objetivo);
		objetivo->setAnterior(nodo);
        tamanio++;
    }
}

template<typename T>
void ListaCircularDoble<T>::eliminarEn(int index)
{
	if (index < 0 
        || 
        index >= tamanio) return;

    if (index == 0 || tamanio == 1) {
		if (tamanio > 1) {
			Nodo<T>* aux = cabeza;
			cabeza = cabeza->getSiguiente();
			cabeza->setAnterior(aux->setAnterior());
			aux->setAnterior()->setSiguiente(cabeza);
			delete aux;
		} else {
			delete cabeza;
			cabeza = nullptr;
		}
	} else if (index == tamanio - 1) {
		Nodo<T>* objetivo = cabeza->setAnterior();
		Nodo<T>* aux = objetivo->setAnterior();
		cabeza->setAnterior(aux);
		aux->setSiguiente(cabeza);
		delete objetivo;
	} else {
		Nodo<T>* objetivo = obtenerNodo(index);
		Nodo<T>* anterior = objetivo->setAnterior();
		Nodo<T>* siguiente = objetivo->getSiguiente();

		delete objetivo;
		anterior->setSiguiente(siguiente);
		siguiente->setAnterior(anterior);
	}

	tamanio = tamanio - 1;
}

template<typename T>
void ListaCircularDoble<T>::eliminar(std::function<bool(T valor)> filtro)
{
    Nodo<T>* nodo = cabeza;
    int indice = 0;

    while (nodo != nullptr) {
        bool eliminar = filtro(nodo->setValor());

        if (eliminar) {
            eliminarEn(indice);
            return;
        }

        nodo = nodo->getSiguiente();
        indice++;
    }
}

template <typename T>
inline Nodo<T>* ListaCircularDoble<T>::obtenerCabeza() {
	return cabeza;
}

template<typename T>
Nodo<T>* ListaCircularDoble<T>::obtenerCola()
{
    Nodo<T>* cola = cabeza;

    if (cola == nullptr) {
        return nullptr;
    }

    while (cola->getSiguiente() != cabeza) {
		cola = cola->getSiguiente();
	}

    return cola;
}

template<typename T>
Nodo<T>* ListaCircularDoble<T>::obtenerNodo(int indice)
{
    if (indice < 0 || indice >= tamanio) {
        return nullptr;
    }

    int i = 0;
    Nodo<T>* nodo = cabeza;

    if (nodo == nullptr)
		return nullptr;

    do {
	    if (i == indice) {
            return nodo;
        }

        nodo = nodo->getSiguiente();
        i++;
    } while (nodo != cabeza);

    return nullptr;
}

template<typename T>
Nodo<T>* ListaCircularDoble<T>::buscar(std::function<bool(T valor)> filtro)
{
	Nodo<T>* nodo = cabeza;
    
    if (nodo == nullptr) {
        return nullptr;
    }

	do {
		if (filtro(nodo->getValor())) {
			return nodo;
		}
        
		nodo = nodo->getSiguiente();
	} while (nodo != cabeza);

    return nullptr;
}

template<typename T>
void ListaCircularDoble<T>::recorrer(std::function<void(T valor)> llamada)
{
    Nodo<T>* nodo = cabeza;

    if (nodo == nullptr) {
        return;
    }
    
    do {
        llamada(nodo->getValor());
        nodo = nodo->getSiguiente();
    } while (nodo != cabeza);
}

template<typename T>
bool ListaCircularDoble<T>::estaVacio()
{
    return tamanio == 0;
}

template<typename T>
int ListaCircularDoble<T>::total()
{
    return tamanio;;
}
