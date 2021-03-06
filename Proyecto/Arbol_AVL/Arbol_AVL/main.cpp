#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include "AVL.h"

using namespace std;

// Función de prueba para recorridos del árbol
void Mostrar(int& d, int FE)
{
    //cout << d << "(" << FE << "),";
    cout << d << " - ";
}

int main()
{
    // Un árbol de enteros
    AVL ArbolInt;

    // Inserción de nodos en árbol:
    ArbolInt.Insertar(1);
    ArbolInt.Insertar(2);
    ArbolInt.Insertar(3);
    ArbolInt.Insertar(4);
    ArbolInt.Insertar(5);
    ArbolInt.Insertar(6);
    ArbolInt.Insertar(7);
    ArbolInt.Insertar(8);
    ArbolInt.Insertar(9);
    ArbolInt.Insertar(10);
    ArbolInt.Insertar(11);
    ArbolInt.Insertar(12);
    ArbolInt.Insertar(13);
    ArbolInt.Insertar(14);
    ArbolInt.Insertar(15);
    ArbolInt.Insertar(16);

    cout << "Altura de arbol " << ArbolInt.AlturaArbol() << endl;

    // Mostrar el árbol en tres ordenes distintos:
    cout << "InOrden: ";
    ArbolInt.InOrden(Mostrar);
    cout << endl;
    cout << "PreOrden: ";
    ArbolInt.PreOrden(Mostrar);
    cout << endl;
    cout << "PostOrden: ";
    ArbolInt.PostOrden(Mostrar);
    cout << endl;

    ArbolInt.Borrar(8);
    ArbolInt.Borrar(11);

    cout << "Altura de arbol " << ArbolInt.AlturaArbol() << endl;

    // Mostrar el árbol en tres ordenes distintos:
    cout << "InOrden: ";
    ArbolInt.InOrden(Mostrar);
    cout << endl;
    cout << "PreOrden: ";
    ArbolInt.PreOrden(Mostrar);
    cout << endl;
    cout << "PostOrden: ";
    ArbolInt.PostOrden(Mostrar);
    cout << endl;

    /*   // Borraremos algunos elementos:
       cout << "N nodos: " << ArbolInt.NumeroNodos() << endl;
       ArbolInt.Borrar(5);
       cout << "Borrar   5: ";
       ArbolInt.InOrden(Mostrar);
       cout << endl;
       ArbolInt.Borrar(8);
       cout << "Borrar   8: ";
       ArbolInt.InOrden(Mostrar);
       cout << endl;
       ArbolInt.Borrar(15);
       cout << "Borrar  15: ";
       ArbolInt.InOrden(Mostrar);
       cout << endl;
       ArbolInt.Borrar(245);
       cout << "Borrar 245: ";
       ArbolInt.InOrden(Mostrar);
       cout << endl;
       ArbolInt.Borrar(4);
       cout << "Borrar   4: ";
       ArbolInt.InOrden(Mostrar);
       ArbolInt.Borrar(17);
       cout << endl;
       cout << "Borrar  17: ";
       ArbolInt.InOrden(Mostrar);
       cout << endl;

       // Veamos algunos parámetros
       cout << "N nodos: " << ArbolInt.NumeroNodos() << endl;
       cout << "Altura de 1 " << ArbolInt.Altura(1) << endl;
       cout << "Altura de 10 " << ArbolInt.Altura(10) << endl;
       cout << "Altura de arbol " << ArbolInt.AlturaArbol() << endl;

       cin.get();

       // Arbol de cadenas:
       AVL<Cadena> ArbolCad;

       // Inserción de valores:
       ArbolCad.Insertar("Hola");
       ArbolCad.Insertar(",");
       ArbolCad.Insertar("somos");
       ArbolCad.Insertar("buenos");
       ArbolCad.Insertar("programadores");

       // Mostrar en diferentes ordenes:
       cout << "InOrden: ";
       ArbolCad.InOrden(Mostrar);
       cout << endl;
       cout << "PreOrden: ";
       ArbolCad.PreOrden(Mostrar);
       cout << endl;
       cout << "PostOrden: ";
       ArbolCad.PostOrden(Mostrar);
       cout << endl;

       // Borrar "buenos":
       ArbolCad.Borrar("buenos");
       cout << "Borrar 'buenos': ";
       ArbolCad.InOrden(Mostrar);
       cout << endl; */
    cin.get();
}