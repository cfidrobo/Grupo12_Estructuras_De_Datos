#pragma once

template <typename T>
class Arreglo {
public:
    Arreglo();
    void agregar(int elemento);
    T obtener(int indice);
    void imprimir();
    void ordenar();
    int tamano();

private:
    T *_datos = nullptr;
    int _tamano = 0;

    void merge(int inicio, int medio, int fin);
    void merge_sort(int inferior, int superior);
};

template <typename T>
Arreglo<T>::Arreglo() {}

template <typename T>
void Arreglo<T>::agregar(int elemento) {
    if (_tamano == 0) {
        _datos = new T[1];
    } else {
        T *nuevo = new T[_tamano + 1];

        for (int i = 0; i < _tamano; i++) {
            *(nuevo + i) = *(_datos + i);
        }
        
        delete[] _datos;
        _datos = nuevo;
    }

    _datos[_tamano] = elemento;
    _tamano++;
}

template<typename T>
T Arreglo<T>::obtener(int indice)
{
    int valor = *(_datos + indice);
    return valor;
}

template <typename T>
void Arreglo<T>::imprimir() {
    std::cout << "[";

    for (int i = 0; i < _tamano; i++) {
        std::cout << *(_datos + i);

        if (i != _tamano - 1) {
            std::cout << ", ";
        }
    }

    std::cout << "]" << std::endl;
}

template <typename T>
void Arreglo<T>::ordenar() {
    merge_sort(0, _tamano - 1);
}

template<typename T>
int Arreglo<T>::tamano()
{
    return _tamano;
}

template <typename T>
void Arreglo<T>::merge(int inicio, int medio, int fin) {
    auto const subArregloUno = medio - inicio + 1;
    auto const subArregloDos = fin - medio;
 
    auto *arregloInicial = new int[subArregloUno],
         *arregloFinal = new int[subArregloDos];
    
    for (auto i = 0; i < subArregloUno; i++) {
        *(arregloInicial + i) = *(_datos + inicio + i);
    }
    
    for (auto j = 0; j < subArregloDos; j++) {
        *(arregloFinal + j) = *(_datos + medio + 1 + j);
    }
 
    auto indiceArregloUno = 0,
        indiceArregloDos = 0;
    int indiceArregloUnido = inicio;
    
    while (indiceArregloUno < subArregloUno && indiceArregloDos < subArregloDos) {
        if (*(arregloInicial + indiceArregloUno) <= *(arregloFinal + indiceArregloDos)) {
            *(_datos + indiceArregloUnido) = *(arregloInicial + indiceArregloUno);
            indiceArregloUno++;
        } else {
            *(_datos + indiceArregloUnido) = *(arregloFinal + indiceArregloDos);
            indiceArregloDos++;
        }

        indiceArregloUnido++;
    }

    while (indiceArregloUno < subArregloUno) {
        *(_datos + indiceArregloUnido) = *(arregloInicial + indiceArregloUno);
        indiceArregloUno++;
        indiceArregloUnido++;
    }

    while (indiceArregloDos < subArregloDos) {
        *(_datos + indiceArregloUnido) = *(arregloFinal + indiceArregloDos);
        indiceArregloDos++;
        indiceArregloUnido++;
    }
}

template <typename T>
void Arreglo<T>::merge_sort(int inferior, int superior) {
    if (inferior >= superior)
        return;
 
    auto medio = inferior + (superior - inferior) / 2;
    merge_sort(inferior, medio);
    merge_sort(medio + 1, superior);
    merge(inferior, medio, superior);
}
