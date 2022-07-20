#pragma once
#include <functional>

template <typename T>
class Nodo {
public:
    Nodo(T valor) {
        valor_ = valor;
    }

    void izquierdo(Nodo<T>* izquierdo) {
        izquierdo_ = izquierdo;
    }

    void derecho(Nodo<T>* derecho) {
        derecho_ = derecho;
    }

    Nodo<T>* izquierdo() {
        return izquierdo_;
    }

    Nodo<T>* derecho() {
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
    Nodo<T>* derecho_ = nullptr;
    Nodo<T>* izquierdo_ = nullptr;
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
    Nodo<T>* buscar(T valor);
    void recorrer(std::function<void(T)> funcion, TipoRecorrido tipo_recorrido);
    Nodo<T>* obtener_raiz() { return raiz; }

private:
    void preorden(Nodo<T>* nodo, std::function<void(T)> funcion);
    void postorden(Nodo<T>* nodo, std::function<void(T)> funcion);
    void inorden(Nodo<T>* nodo, std::function<void(T)> funcion);

    Nodo<T>* insertar_recursivo(Nodo<T>*& actual, Nodo<T>* nodo);
    Nodo<T>* eliminar_recursivo(Nodo<T>*& actual, T valor);
    Nodo<T>* buscar_recursivo(Nodo<T>* actual, T valor);

    Nodo<T>* balancear_arbol(Nodo<T>*& actual);
    int obtener_factor_balance(Nodo<T>* nodo);
    int obtener_altura(Nodo<T>* nodo);
    Nodo<T>* rotar_izquierda_izquierda(Nodo<T>* nodo);
    Nodo<T>* rotar_derecha_derecha(Nodo<T>* nodo);
    Nodo<T>* rotar_izquierda_derecha(Nodo<T>* nodo);
    Nodo<T>* rotar_derecha_izquierda(Nodo<T>* nodo);
    int maximo(int a, int b) { return a > b ? a : b; }

    Nodo<T>* raiz = nullptr;
};

template <typename T>
void ArbolAVL<T>::insertar(T valor) {
    Nodo<T>* nodo = new Nodo<T>(valor);

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
Nodo<T>* ArbolAVL<T>::buscar(T valor) {
    Nodo<T>* nodo = buscar_recursivo(raiz, valor);

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
void ArbolAVL<T>::preorden(Nodo<T>* nodo, std::function<void(T)> funcion) {
    if (nodo != nullptr) {
        funcion(nodo->valor());
        preorden(nodo->izquierdo(), funcion);
        preorden(nodo->derecho(), funcion);
    }
}

template <typename T>
void ArbolAVL<T>::postorden(Nodo<T>* nodo, std::function<void(T)> funcion) {
    if (nodo != nullptr) {
        postorden(nodo->izquierdo(), funcion);
        postorden(nodo->derecho(), funcion);
        funcion(nodo->valor());
    }
}

template <typename T>
void ArbolAVL<T>::inorden(Nodo<T>* nodo, std::function<void(T)> funcion) {
    if (nodo != nullptr) {
        inorden(nodo->izquierdo(), funcion);
        funcion(nodo->valor());
        inorden(nodo->derecho(), funcion);
    }
}

template <typename T>
Nodo<T>* ArbolAVL<T>::insertar_recursivo(Nodo<T>*& actual, Nodo<T>* nodo) {
    if (actual == nullptr) {
        actual = nodo;
        return actual;
    } else if (nodo->valor() < actual->valor()) {
        Nodo<T>* izquierdo = actual->izquierdo();
        actual->izquierdo(insertar_recursivo(izquierdo, nodo));
        actual = balancear_arbol(actual);
    } else if (nodo->valor() >= actual->valor()) {
        Nodo<T>* derecho = actual->derecho();
        actual->derecho(insertar_recursivo(derecho, nodo));
        actual = balancear_arbol(actual);
    }
    
    return actual;
}

template <typename T>
Nodo<T>* ArbolAVL<T>::eliminar_recursivo(Nodo<T>*& actual, T valor) {
    Nodo<T>* padre;

    if (actual == nullptr) {
        return nullptr;
    } else {
        if (valor < actual->valor()) {
            Nodo<T>* izquierdo = actual->izquierdo();
            actual->izquierdo(eliminar_recursivo(izquierdo, valor));

            if (obtener_factor_balance(actual) == -2) {
                if (obtener_factor_balance(actual->izquierdo()) <= 0) {
                    actual = rotar_derecha_derecha(actual);
                } else {
                    actual = rotar_derecha_izquierda(actual);
                }
            }
        } else if (valor > actual->valor()) {
            Nodo<T>* derecho = actual->derecho();
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
                Nodo<T>* derecho = actual->derecho();
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
Nodo<T>* ArbolAVL<T>::buscar_recursivo(Nodo<T>* actual, T valor) {
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
Nodo<T>* ArbolAVL<T>::balancear_arbol(Nodo<T>*& actual) {
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
int ArbolAVL<t>::obtener_factor_balance(Nodo<t>* nodo) {
    int izq = obtener_altura(nodo->izquierdo());
    int der = obtener_altura(nodo->derecho());
    int factor = izq - der;

    return factor;
}

template <typename T>
int ArbolAVL<T>::obtener_altura(Nodo<T>* nodo) {
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
Nodo<T>* ArbolAVL<T>::rotar_izquierda_izquierda(Nodo<T>* nodo) {
    Nodo<T>* pivote = nodo->izquierdo();
    nodo->izquierdo(pivote->derecho());
    pivote->derecho(nodo);
    return pivote;
}

template <typename T>
Nodo<T>* ArbolAVL<T>::rotar_derecha_derecha(Nodo<T>* nodo) {
    Nodo<T>* pivote = nodo->derecho();
    nodo->derecho(pivote->izquierdo());
    pivote->izquierdo(nodo);
    return pivote;
}

template <typename T>
Nodo<T>* ArbolAVL<T>::rotar_izquierda_derecha(Nodo<T>* nodo) {
    Nodo<T>* pivote = nodo->izquierdo();
    nodo->izquierdo(rotar_derecha_derecha(pivote));
    return rotar_izquierda_izquierda(nodo);
}

template <typename T>
Nodo<T>* ArbolAVL<T>::rotar_derecha_izquierda(Nodo<T>* nodo) {
    Nodo<T>* pivote = nodo->derecho();
    nodo->derecho(rotar_izquierda_izquierda(pivote));
    return rotar_derecha_derecha(nodo);
}
