#pragma once
#include <functional>
#include <fstream>
#include <iostream>
#include <sstream>
#include <functional>

template <typename T>
class NodoAVL {
public:
    NodoAVL(T valor) {
        valor_ = valor;
    }

    void izquierdo(NodoAVL<T>* izquierdo) {
        izquierdo_ = izquierdo;
    }

    void derecho(NodoAVL<T>* derecho) {
        derecho_ = derecho;
    }

    NodoAVL<T>*& izquierdo() {
        return izquierdo_;
    }

    NodoAVL<T>*& derecho() {
        return derecho_;
    }

    T valor() {
        return valor_;
    }

    void valor(T valor) {
        valor_ = valor;
    }

    int modotail() {
        return modotail_;
    }

    void modotail(int modotail) {
        modotail_ = modotail;
    }

private:
    NodoAVL<T>* derecho_ = nullptr;
    NodoAVL<T>* izquierdo_ = nullptr;
    T valor_;
    int modotail_;
};

enum class TipoRecorrido {
    PREORDEN,
    INORDEN,
    POSTORDEN
};

template <typename T>
class ArbolAVL {
public:
    void insertar(T valor);
    void eliminar(T valor);
    NodoAVL<T>* buscar(T valor);
    void recorrer(std::function<void(T)> funcion, TipoRecorrido tipo_recorrido);
    NodoAVL<T>* obtener_raiz() { return raiz; }
	void serializar(std::string nombre_archivo);
	void deserializar(std::string nombre_archivo, std::function<T(std::string)> convertidor);

    void serializar_recursivo(NodoAVL<T>* nodo, std::ostream& archivo);
	void deserializar_recursivo(NodoAVL<T>*& nodo, std::istream& archivo, std::function<T(std::string)> convertidor);

private:
    void preorden(NodoAVL<T>* nodo, std::function<void(T)> funcion);
    void postorden(NodoAVL<T>* nodo, std::function<void(T)> funcion);
    void inorden(NodoAVL<T>* nodo, std::function<void(T)> funcion);

    NodoAVL<T>* insertar_recursivo(NodoAVL<T>*& actual, NodoAVL<T>* nodo);
    NodoAVL<T>* eliminar_recursivo(NodoAVL<T>*& actual, T valor);
    NodoAVL<T>* buscar_recursivo(NodoAVL<T>* actual, T valor);

    NodoAVL<T>* balancear_arbol(NodoAVL<T>*& actual);
    int obtener_factor_balance(NodoAVL<T>* nodo);
    int obtener_altura(NodoAVL<T>* nodo);
    NodoAVL<T>* rotar_izquierda_izquierda(NodoAVL<T>* nodo);
    NodoAVL<T>* rotar_derecha_derecha(NodoAVL<T>* nodo);
    NodoAVL<T>* rotar_izquierda_derecha(NodoAVL<T>* nodo);
    NodoAVL<T>* rotar_derecha_izquierda(NodoAVL<T>* nodo);
    int maximo(int a, int b) { return a > b ? a : b; }

    NodoAVL<T>* raiz = nullptr;
};

template <typename T>
void ArbolAVL<T>::insertar(T valor) {
    NodoAVL<T>* nodo = new NodoAVL<T>(valor);

    if (raiz == nullptr) {
        raiz = nodo;
    } else {
        insertar_recursivo(raiz, nodo);
    }
}

template <typename T>
void ArbolAVL<T>::eliminar(T valor) {
    raiz = eliminar_recursivo(raiz, valor);
}

template <typename T>
NodoAVL<T>* ArbolAVL<T>::buscar(T valor) {
    NodoAVL<T>* nodo = buscar_recursivo(raiz, valor);

    if (nodo != nullptr && nodo->valor() == valor) {
        return nodo;
    }
    
    return nullptr;
}

template <typename T>
void ArbolAVL<T>::recorrer(std::function<void(T)> funcion, TipoRecorrido tipo_recorrido) {
    if (tipo_recorrido == TipoRecorrido::PREORDEN) {
        preorden(raiz, funcion);
    } else if (tipo_recorrido == TipoRecorrido::INORDEN) {
        inorden(raiz, funcion);
    } else if (tipo_recorrido == TipoRecorrido::POSTORDEN) {
        postorden(raiz, funcion);
    }
}

template <typename T>
inline void ArbolAVL<T>::serializar(std::string nombre_archivo) {
    std::ofstream archivo(nombre_archivo);

    if (archivo.is_open()) {
        serializar_recursivo(raiz, archivo);
    }
}

template <typename T>
inline void ArbolAVL<T>::deserializar(std::string nombre_archivo, std::function<T(std::string)> convertidor) {
    std::ifstream archivo(nombre_archivo);
    
    if (archivo.is_open()) {
		deserializar_recursivo(raiz, archivo, convertidor);
    }
}

template <typename T>
inline void ArbolAVL<T>::serializar_recursivo(NodoAVL<T>* nodo, std::ostream& salida) {
	if (nodo == nullptr) {
		salida << "null" << std::endl;
		return;
	}

	salida << nodo->valor() << std::endl;
	serializar_recursivo(nodo->izquierdo(), salida);
	serializar_recursivo(nodo->derecho(), salida);
}

template <typename T>
inline void ArbolAVL<T>::deserializar_recursivo(NodoAVL<T>*& nodo, std::istream& entrada, std::function<T(std::string)> convertidor) {
	std::string linea;
	std::getline(entrada, linea);

	if (linea == "null") {
		nodo = nullptr;
		return;
	}

	nodo = new NodoAVL<T>(convertidor(linea));
	deserializar_recursivo(nodo->izquierdo(), entrada, convertidor);
	deserializar_recursivo(nodo->derecho(), entrada, convertidor);

	return;
}

template <typename T>
void ArbolAVL<T>::preorden(NodoAVL<T>* nodo, std::function<void(T)> funcion) {
    if (nodo != nullptr) {
        funcion(nodo->valor());
        preorden(nodo->izquierdo(), funcion);
        preorden(nodo->derecho(), funcion);
    }
}

template <typename T>
void ArbolAVL<T>::postorden(NodoAVL<T>* nodo, std::function<void(T)> funcion) {
    if (nodo != nullptr) {
        postorden(nodo->izquierdo(), funcion);
        postorden(nodo->derecho(), funcion);
        funcion(nodo->valor());
    }
}

template <typename T>
void ArbolAVL<T>::inorden(NodoAVL<T>* nodo, std::function<void(T)> funcion) {
    if (nodo != nullptr) {
        inorden(nodo->izquierdo(), funcion);
        funcion(nodo->valor());
        inorden(nodo->derecho(), funcion);
    }
}

template <typename T>
NodoAVL<T>* ArbolAVL<T>::insertar_recursivo(NodoAVL<T>*& actual, NodoAVL<T>* nodo) {
    if (actual == nullptr) {
        actual = nodo;
        return actual;
    } else if (nodo->valor() < actual->valor()) {
        NodoAVL<T>* izquierdo = actual->izquierdo();
        actual->izquierdo(insertar_recursivo(izquierdo, nodo));
        actual = balancear_arbol(actual);
    } else if (nodo->valor() >= actual->valor()) {
        NodoAVL<T>* derecho = actual->derecho();
        actual->derecho(insertar_recursivo(derecho, nodo));
        actual = balancear_arbol(actual);
    }
    
    return actual;
}

template <typename T>
NodoAVL<T>* ArbolAVL<T>::eliminar_recursivo(NodoAVL<T>*& actual, T valor) {
    NodoAVL<T>* padre;

    if (actual == nullptr) {
        return nullptr;
    } else {
        if (valor < actual->valor()) {
            NodoAVL<T>* izquierdo = actual->izquierdo();
            actual->izquierdo(eliminar_recursivo(izquierdo, valor));

            if (obtener_factor_balance(actual) == -2) {
                if (obtener_factor_balance(actual->izquierdo()) <= 0) {
                    actual = rotar_derecha_derecha(actual);
                } else {
                    actual = rotar_derecha_izquierda(actual);
                }
            }
        } else if (valor > actual->valor()) {
            NodoAVL<T>* derecho = actual->derecho();
            actual->derecho(eliminar_recursivo(derecho, valor));

            if (obtener_factor_balance(actual) == 2) {
                if (obtener_factor_balance(actual->izquierdo()) >= 0) {
                    actual = rotar_izquierda_izquierda(actual);
                } else {
                    actual = rotar_izquierda_derecha(actual);
                }
            }
        } else {
            if (actual->derecho() != nullptr) {
                padre = actual->derecho();

                while (padre->izquierdo() != nullptr) {
                    padre = padre->izquierdo();
                }

                actual->valor(padre->valor());
                NodoAVL<T>* derecho = actual->derecho();
                actual->derecho(eliminar_recursivo(derecho, padre->valor()));

                if (obtener_factor_balance(actual) == 2) {
                    if (obtener_factor_balance(actual->izquierdo()) >= 0) {
                        actual = rotar_izquierda_izquierda(actual);
                    } else {
                        actual = rotar_izquierda_derecha(actual);
                    }
                }
            } else {
                return actual->izquierdo();
            }
        }
    }

    return actual;
}

template <typename T>
NodoAVL<T>* ArbolAVL<T>::buscar_recursivo(NodoAVL<T>* actual, T valor) {
    if (actual == nullptr) {
        return nullptr;
    }
    
    if (valor < actual->valor()) {
        if (valor == actual->valor()) {
            return actual;
        } else {
            return buscar_recursivo(actual->izquierdo(), valor);
        }
    } else {
        if (valor == actual->valor()) {
            return actual;
        } else {
            return buscar_recursivo(actual->derecho(), valor);
        }
    }
}

template <typename T>
NodoAVL<T>* ArbolAVL<T>::balancear_arbol(NodoAVL<T>*& actual) {
    int factor_balance = obtener_factor_balance(actual);

    if (factor_balance > 1) {
        if (obtener_factor_balance(actual->izquierdo()) > 0) {
            actual = rotar_izquierda_izquierda(actual);
        } else {
            actual = rotar_izquierda_derecha(actual);
        }
    } else if (factor_balance < -1) {
        if (obtener_factor_balance(actual->derecho()) > 0) {
            actual = rotar_derecha_izquierda(actual);
        } else {
            actual = rotar_derecha_derecha(actual);
        }
    }
    
    return actual;
}

template <typename t>
int ArbolAVL<t>::obtener_factor_balance(NodoAVL<t>* nodo) {
    int izq = obtener_altura(nodo->izquierdo());
    int der = obtener_altura(nodo->derecho());
    int factor = izq - der;

    return factor;
}

template <typename T>
int ArbolAVL<T>::obtener_altura(NodoAVL<T>* nodo) {
    int altura = 0;

    if (nodo != nullptr) {
        int izq = obtener_altura(nodo->izquierdo());
        int der = obtener_altura(nodo->derecho());
        int m = maximo(izq, der);
        altura = m + 1;
    }

    return altura;
}

template <typename T>
NodoAVL<T>* ArbolAVL<T>::rotar_izquierda_izquierda(NodoAVL<T>* nodo) {
    NodoAVL<T>* pivote = nodo->izquierdo();
    nodo->izquierdo(pivote->derecho());
    pivote->derecho(nodo);
    return pivote;
}

template <typename T>
NodoAVL<T>* ArbolAVL<T>::rotar_derecha_derecha(NodoAVL<T>* nodo) {
    NodoAVL<T>* pivote = nodo->derecho();
    nodo->derecho(pivote->izquierdo());
    pivote->izquierdo(nodo);
    return pivote;
}

template <typename T>
NodoAVL<T>* ArbolAVL<T>::rotar_izquierda_derecha(NodoAVL<T>* nodo) {
    NodoAVL<T>* pivote = nodo->izquierdo();
    nodo->izquierdo(rotar_derecha_derecha(pivote));
    return rotar_izquierda_izquierda(nodo);
}

template <typename T>
NodoAVL<T>* ArbolAVL<T>::rotar_derecha_izquierda(NodoAVL<T>* nodo) {
    NodoAVL<T>* pivote = nodo->derecho();
    nodo->derecho(rotar_izquierda_izquierda(pivote));
    return rotar_derecha_derecha(nodo);
}
