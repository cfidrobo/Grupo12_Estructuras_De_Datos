#pragma once

template <typename T>
class Nodo {
public:
	Nodo(T valor) {
		this->valor = valor;
	}

    T getValor() {
		return valor;
	}
    
    void setValor(T valor) {
		this->valor = valor;
	}
    
    Nodo<T>* getSiguiente() {
		return siguiente;
	}
    
    void setSiguiente(Nodo<T>* siguiente) {
		this->siguiente = siguiente;
	}

    Nodo<T>* getAnterior() {
		return anterior;
	}
    
    void setAnterior(Nodo<T>* anterior) {
		this->anterior = anterior;
	}

private:
    T valor;
    Nodo<T>* siguiente = nullptr;
    Nodo<T>* anterior = nullptr;
};
