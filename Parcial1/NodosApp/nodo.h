#pragma once

template <typename T>
class Nodo {
public:
    Nodo(T valor, Nodo<T>* siguiente);
    Nodo(T valor);

    Nodo<T> *get_siguiente();
    void set_siguiente(Nodo<T>* siguiente);

    T get_valor();
    void set_valor(T valor);

private:
    T valor_;
    Nodo<T>* siguiente_;
};

///////////////////////////////////////////////////////////////////

template <typename T>
Nodo<T>::Nodo(T valor, Nodo<T>* siguiente) {
    this->valor_ = valor;
    this->siguiente_ = siguiente;
}

template<typename T>
Nodo<T>::Nodo(T valor)
{
    this->valor_ = valor;
    this->siguiente_ = nullptr;
}

template<typename T>
Nodo<T>* Nodo<T>::get_siguiente()
{
    return siguiente_;
}

template<typename T>
void Nodo<T>::set_siguiente(Nodo<T>* siguiente) {
    siguiente_ = siguiente;
}

template<typename T>
T Nodo<T>::get_valor()
{
    return this->valor_;
}

template<typename T>
void Nodo<T>::set_valor(T valor)
{
    valor_ = valor;
}
