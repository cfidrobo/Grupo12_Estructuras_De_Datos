#pragma once
#include "nodo.h"
#include <iostream>
#include <functional>

using namespace std;

template <typename T>
class ListaSimple {
public:
    void insertar_final(T valor);
    void insertar_inicio(T valor);

    void imprimir();

    void recorrer(std::function<void(T valor)> callback);
    void recorrer_nodos(std::function<void(Nodo<T> *nodo)> callback);

    void eliminar(int indice);

    Nodo<T>* buscar(int valor);

    bool esta_vacia();
    int tamanio();

private:
    Nodo<T>* cabeza_ = nullptr;
    int tamanio_ = 0;
};

////////////////////////////////////////////////////////

template <typename T>
void ListaSimple<T>::insertar_final(T valor) {
    Nodo<T>* nodo = new Nodo<T>(valor, nullptr);

    tamanio_++;

    if (cabeza_ == nullptr) {
        cabeza_ = nodo;
        return;
    }

    Nodo<T>* temporal = cabeza_;

    while (temporal->get_siguiente() != nullptr) {
        temporal = temporal->get_siguiente();
    }

    temporal->set_siguiente(nodo);
}

template<typename T>
void ListaSimple<T>::insertar_inicio(T valor)
{
    if (esta_vacia()) {
        insertar_final(valor);
        return;
    }

    Nodo<T>* nodo = new Nodo<T>(valor);
    Nodo<T>* temporal = cabeza_;

    cabeza_ = nodo;
    cabeza_->set_siguiente(temporal);
    tamanio_++;
}

template <typename T>
void ListaSimple<T>::imprimir() {
    Nodo<T>* temporal = cabeza_;

    while (temporal != nullptr) {
        cout << temporal->get_valor() << endl;
        temporal = temporal->get_siguiente();
    }
}

template<typename T>
void ListaSimple<T>::recorrer(std::function<void(T valor)> callback)
{
    Nodo<T>* temporal = cabeza_;

    while (temporal != nullptr) {
        callback(temporal->get_valor());
        temporal = temporal->get_siguiente();
    }
}

template<typename T>
void ListaSimple<T>::recorrer_nodos(std::function<void(Nodo<T> *nodo)> callback)
{
    Nodo<T>* temporal = cabeza_;

    while (temporal != nullptr) {
        callback(temporal);
        temporal = temporal->get_siguiente();
    }
}

template<typename T>
void ListaSimple<T>::eliminar(int indice)
{
    if (indice < 0 || indice >= tamanio_) {
        cout << "Error: indice no encontrado en la lista";
        return;
    }

    // si la lista tiene 1 solo elemento, se elimina
    // ese unico nodo, es decir la cabeza
    if (tamanio_ == 1) {
        delete cabeza_;
        cabeza_ = nullptr;
    }
    
    // si indice es la cabeza
    else if (indice == 0) {
        Nodo<T>* temporal = cabeza_;
        cabeza_ = cabeza_->get_siguiente();
        delete temporal;
    }

    // si el indice es la cola o el ultimo elemento
    else if (indice == tamanio_ - 1) {
        Nodo<T>* temporal = cabeza_;
        Nodo<T>* penultimo{};
        int i = 0;

        while (temporal->get_siguiente() != nullptr) {
            if (i == tamanio_ - 2) {
                penultimo = temporal;
            }

            temporal = temporal->get_siguiente();
            i++;
        };

         delete temporal;
         penultimo->set_siguiente(nullptr);
    }

    // si el nodo esta entre la cola y la cabeza
    else {
        Nodo<T>* actual=nullptr;
        Nodo<T>* anterior=nullptr;
        Nodo<T>* siguiente=nullptr;
        Nodo<T>* temporal = cabeza_;
        int i = 0;

        while (temporal != nullptr) {
            if (i == indice) {
                actual = temporal;
            } else if (i == indice - 1) {
                anterior = temporal;
            }

            temporal = temporal->get_siguiente();
            i++;
        }

        siguiente = actual->get_siguiente();
        anterior->set_siguiente(siguiente);
        delete actual;
    }

    tamanio_--;
}

template<typename T>
Nodo<T>* ListaSimple<T>::buscar(int valor)
{
    Nodo<T>* temporal = cabeza_;

    while (temporal != nullptr) {
        if (valor == temporal->get_valor()) {
            return temporal;
        }

        temporal = temporal->get_siguiente();
    }

    return nullptr;
}

template<typename T>
bool ListaSimple<T>::esta_vacia()
{
    return (tamanio_ == 0);
}

template<typename T>
int ListaSimple<T>::tamanio()
{
    return tamanio_;
}
