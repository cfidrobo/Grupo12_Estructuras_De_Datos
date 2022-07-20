#pragma once
#include <iostream>

// Clase Nodo de Arbol AVL:
class Nodo {
public:
    // Constructor:
    Nodo(const int dat, Nodo* pad = NULL, Nodo* izq = NULL, Nodo* der = NULL) :
        dato(dat), padre(pad), izquierdo(izq), derecho(der), FE(0) {}
    // Miembros:
    int dato;
    int FE;
    Nodo* izquierdo;
    Nodo* derecho;
    Nodo* padre;
    friend class AVL;
};

