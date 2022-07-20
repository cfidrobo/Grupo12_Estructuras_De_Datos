#pragma once
#include "arbol_avl.h"
#include <string>
#include <sstream>
#include <vector>
#include <Windows.h>

template <typename T>
class NodoInfo {
public:
    int tamanio() { return texto_.length(); }
    
    std::string texto() { return texto_; }

    void texto(std::string texto) {
        texto_ = texto;
    }
    
    int posicion_inicial() { return posicion_inicial_; }
    
    void posicion_inicial(int posicion) {
        posicion_inicial_ = posicion;
    }

    int posicion_final() { return posicion_inicial_ + tamanio(); }
    void posicion_final(int valor) { posicion_inicial_ = valor - tamanio(); }
    int modotail() { return modotail_; }
    void modotail(int modo) { modotail_ = modo; }
    
    void nodo(NodoAVL<T>* nodo) {
        nodo_ = nodo;
    }
    
    NodoAVL<T>* nodo() { return nodo_; }

    void padre(NodoInfo<T>* padre) {
        padre_ = padre;
    }

    NodoInfo<T>* padre() { return padre_; }

    void izquierdo(NodoInfo<T>* nodo_info) {
        izquierdo_ = nodo_info;
    }

    NodoInfo<T>* izquierdo() { return izquierdo_; }

    void derecho(NodoInfo<T>* nodo_info) {
        derecho_ = nodo_info;
    }

    NodoInfo<T>* derecho() { return derecho_; }

private:
	NodoAVL<T>* nodo_ = nullptr;
    std::string texto_ = "";
    int posicion_inicial_ = 0;
    int posicion_final_ = 0;
    bool modotail_ = 1;

    NodoInfo<T>* padre_ = nullptr;
    NodoInfo<T>* izquierdo_ = nullptr;
    NodoInfo<T>* derecho_ = nullptr;
};

template <typename T>
class ArbolVisualizador {
public:
    void imprimir(ArbolAVL<T> arbol) {
        imprimir(arbol.obtener_raiz(), 1, 2, 2);
    }

    void imprimir(NodoAVL<T>* raiz, int modo, int margenSuperior = 2, int margenIzquierdo = 2) {
        if (raiz == nullptr) {
            return;
        }

        COORD cursor_pos = cursor_posicion();
        
        int raizTop = cursor_pos.Y + margenSuperior;
        std::vector<NodoInfo<T>*> ultimo;
		NodoAVL<T>* siguiente = raiz;
        int modotail = raiz->modotail();
        std::string txt;
        
        for (int nivel = 0; siguiente != nullptr; nivel++) {
            if (modo == 1) {
                std::stringstream ss;
                ss << " " << siguiente->valor() << " ";
                txt = ss.str();
            }

            NodoInfo<T>* item = new NodoInfo<T>();
            item->nodo(siguiente);
            item->texto(txt);
            item->modotail(modotail);

            if (nivel < ultimo.size()) {
                item->posicion_inicial(ultimo.at(nivel)->posicion_final() + 1);
                ultimo[nivel] = item;
            } else {
                item->posicion_inicial(margenIzquierdo);
                ultimo.push_back(item);
            }

            if (nivel > 0) {
                item->padre(ultimo[nivel - 1]);

                if (siguiente == item->padre()->nodo()->izquierdo()) {
                    item->padre()->izquierdo(item);
                    int pos = (item->posicion_final() > item->padre()->posicion_inicial())
                        ? item->posicion_final() : item->padre()->posicion_inicial();
                    item->posicion_final(pos);
                } else {
                    item->padre()->derecho(item);
                    int pos = (item->posicion_inicial() > item->padre()->posicion_final())
                        ? item->posicion_inicial() : item->padre()->posicion_final();
                    item->posicion_inicial(pos);
                }
            }

            siguiente = siguiente->izquierdo() != nullptr
                ? siguiente->izquierdo() : siguiente->derecho();

            for (; siguiente == nullptr; item = item->padre()) {
                imprimir(item, raizTop + 2 * nivel);

                if (--nivel < 0) break;

                if (item == item->padre()->izquierdo()) {
                    item->padre()->posicion_inicial(item->posicion_final());
                    siguiente = item->padre()->nodo()->derecho();
                } else {
                    if (item->padre()->izquierdo() == nullptr) {
                        item->padre()->posicion_final(item->posicion_inicial());
                    } else {
                        int pos = item->padre()->posicion_inicial() + ((item->posicion_inicial() - item->padre()->posicion_final()) / 2);
                        item->padre()->posicion_inicial(pos);
                    }
                }
            }
        }

        definir_posicion_cursor(0, raizTop + 2 * ultimo.size() - 1);
    }

private:

    void imprimir(NodoInfo<T>* item, int top) {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        
        if (item->izquierdo() != nullptr && item->derecho() != nullptr) {
            invertir_colores();
            imprimir(item->texto(), top, item->posicion_inicial());
            SetConsoleTextAttribute(hConsole, 7);
        } else if (item->modotail()) {
            tail_color();
            imprimir(item->texto(), top, item->posicion_inicial());
            SetConsoleTextAttribute(hConsole, 7);
        } else {
            invertir_colores();
            imprimir(item->texto(), top, item->posicion_inicial());
            SetConsoleTextAttribute(hConsole, 7);
        }

        int posicion;

        if (item->izquierdo() != nullptr) {
            posicion = item->izquierdo()->posicion_inicial() + item->izquierdo()->tamanio() / 2;
            imprimirEnlace(top + 1, "┌", "┘", posicion, item->posicion_inicial());
        }
        
        if (item->derecho() != nullptr) {
            posicion = item->derecho()->posicion_inicial() + item->derecho()->tamanio() / 2;
            imprimirEnlace(top + 1, "└", "┐", item->posicion_final() - 1, posicion);
        }
    }

    void imprimirEnlace(int top, std::string start, std::string end, int startPos, int endPos) {
        definir_posicion_cursor(startPos, top);
        std::cout << start;
        
        imprimir("─", top, startPos + 1, endPos);

        definir_posicion_cursor(endPos, top);
        std::cout << end;
    }

    void imprimir(std::string s, int top, int left, int right = -1) {
        definir_posicion_cursor(left, top);

        if (right < 0) right = left + s.length();
        
        while (cursor_posicion().X < right) {
            std::cout << s;
        }
    }

    COORD cursor_posicion() {
        CONSOLE_SCREEN_BUFFER_INFO csbInfo;
        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbInfo);
        return csbInfo.dwCursorPosition;
    }

    void definir_posicion_cursor(int x, int y) {
        CONSOLE_SCREEN_BUFFER_INFO csbInfo;
        csbInfo.dwCursorPosition.X = x;
        csbInfo.dwCursorPosition.Y = y;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), csbInfo.dwCursorPosition);
    }

    void invertir_colores() {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_SCREEN_BUFFER_INFO csbInfo;
        GetConsoleScreenBufferInfo(hConsole, &csbInfo);

        WORD wAttributes = csbInfo.wAttributes;
        wAttributes = (wAttributes & 0xfff0) | ((wAttributes & 0x000f) << 4);

        SetConsoleTextAttribute(hConsole, wAttributes);
    }

    void tail_color() {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, 236);
    }
};
