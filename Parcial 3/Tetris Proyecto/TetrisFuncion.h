#pragma once
#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <time.h>
#include <conio.h>
#include "Posicion.h"
#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77

class TetrisFuncion {
private:
	int limiteAleatorio;
	int saltos;
public:
	TetrisFuncion();
	TetrisFuncion(int limiteAleatorio, int saltos);
	~TetrisFuncion();
	void gotoxy(int x, int y);
	void cuadro(int limVer, int limHoriz);
	void ocultarCursor();
	void imprimir(int limVer, int limHoriz, Posicion*& pos);
	void comenzarJuego();
};
