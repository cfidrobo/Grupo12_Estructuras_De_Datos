#include <iostream>
#include "arbol_avl.h"
#include "visualizador.h"
#include "menu.h"
#include "funciones.h"

int main()
{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    ArbolAVL<int> arbol;

    Menu menu("Arbol AVL");

    menu.agregar(MenuOpcion("insertar", [&]() {
        int valor = Funciones::leer_entero("Ingrese un valor: ", 1);
        arbol.insertar(valor);
        std::cout << "valor insertado" << std::endl;
    }));

    menu.agregar(MenuOpcion("eliminar", [&]() {
        int valor = Funciones::leer_entero("Ingrese un valor: ", 1);
        if (arbol.buscar(valor) != nullptr) {
            arbol.eliminar(valor);
            std::cout << "valor eliminado\n";
        } else {
            std::cout << "valor no encontrado\n";
        }
    }));

    menu.agregar(MenuOpcion("buscar", [&]() {
        int valor = Funciones::leer_entero("Ingrese un valor: ", 1);
        if (arbol.buscar(valor) != nullptr) {
            std::cout << "valor encontrado\n";
        }
        else {
            std::cout << "valor no encontrado\n";
        }
    }));

    menu.agregar(MenuOpcion("sumar cifras arbol", [&]() {
        ArbolAVL<int> nuevoArbol;

        arbol.recorrer([&](int n) {
            nuevoArbol.insertar(Funciones::reducir_numero(n));
        }, TipoRecorrido::INORDEN);

        ArbolVisualizador<int> visualizador;
        visualizador.imprimir(nuevoArbol);
    }));

    menu.agregar(MenuOpcion("Ver arbol", [&]() {
        ArbolVisualizador<int> visualizador;
        visualizador.imprimir(arbol);
    }));

    menu.agregar(menu.opcion_salir("Salir"));
    menu.iniciar();
}
