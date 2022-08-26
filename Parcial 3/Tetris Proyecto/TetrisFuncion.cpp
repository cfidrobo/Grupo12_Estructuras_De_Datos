#pragma warning(disable : 4996)
#include "TetrisFuncion.h"
#include "Posicion.h"
#include "Consola.h"
#include "ListaDoble.h"

TetrisFuncion::TetrisFuncion(int limiteAleatorio, int saltos) {
	srand(time(NULL));
	this->limiteAleatorio = limiteAleatorio;
	this->saltos = saltos;
}

TetrisFuncion::TetrisFuncion() {
}


TetrisFuncion::~TetrisFuncion() {
}

void TetrisFuncion::gotoxy(int x, int y) {
	HANDLE hcon;
	hcon = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD dwPos;
	dwPos.X = x;
	dwPos.Y = y;
	SetConsoleCursorPosition(hcon, dwPos);
}

void TetrisFuncion::cuadro(int limVer, int limHoriz) {
	ocultarCursor();
	char a = char(223);
	char b[] = { a };
	std::string c;
	c.assign(b, 1);
	for (int i = 0; i <= limHoriz; i++) {
		gotoxy(i, 0);
		std::cout << c;
	}
	a = char(219);
	char d[] = { a };
	c.assign(d, 1);
	for (int i = 0; i <= limVer; i++) {
		gotoxy(limHoriz, i);
		std::cout << c;
	}
	c.assign(b, 1);
	for (int i = limHoriz; i >= 0; i--) {
		gotoxy(i, limVer);
		std::cout << c;
	}
	c.assign(d, 1);
	for (int i = limVer - 1; i >= 0; i--) {
		gotoxy(0, i);
		std::cout << c;
	}
	gotoxy(0, limVer + 1);
}

void TetrisFuncion::ocultarCursor() {
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = FALSE;
	SetConsoleCursorInfo(consoleHandle, &info);
}

void TetrisFuncion::imprimir(int limVer, int limHoriz, Posicion*& pos) {
	int num = 0;
	int posY = 0;
	int salto = 0;
	system("cls");
	cuadro(limVer, limHoriz);
	if (_kbhit()) {
		char key = _getch();
		switch (key) {
		case DOWN:
			if (pos->getPosY() >= limVer - 1) {
				num = 1 + rand() % (limiteAleatorio - 1);
				do {
					posY = (6 + rand() % ((limHoriz - 4) - 6));
				} while (posY % 6 != 0);
				pos->setPosXY(posY, (pos->getPosY() + 1), num);
				gotoxy(pos->getPosX(), pos->getPosY());
				std::cout << pos->getNum();
			}
			else {
				if (pos->getPosY() + 5 >= limVer - 1) {
					num = 1 + rand() % (limiteAleatorio - 1);
					do {
						posY = 6 + rand() % ((limHoriz - 4) - 6);
					} while (posY % 6 != 0);
					pos->setPosXY(posY, (pos->getPosY() + 1), num);
					gotoxy(pos->getPosX(), pos->getPosY());
					std::cout << pos->getNum();
				}
				else {
					pos->setPosXY(pos->getPosX(), (pos->getPosY() + 5), (pos->getNum()));
					gotoxy(pos->getPosX(), pos->getPosY());
					std::cout << pos->getNum();
				}
			}
			break;
		case LEFT:
			if (pos->getPosX() <= 6) {
				pos->setPosXY(pos->getPosX(), (pos->getPosY() + 1), (pos->getNum()));
				gotoxy(pos->getPosX(), pos->getPosY());
				std::cout << pos->getNum();
			}
			else {
				if (pos->getPosX() - saltos <= 6) {
					salto = pos->getPosX() - saltos;
					pos->setPosXY(pos->getPosX() - salto, (pos->getPosY() + 1), (pos->getNum()));
					gotoxy(pos->getPosX(), pos->getPosY());
					std::cout << pos->getNum();
				}
				else {
					pos->setPosXY(pos->getPosX() - saltos, (pos->getPosY() + 1), (pos->getNum()));
					gotoxy(pos->getPosX(), pos->getPosY());
					std::cout << pos->getNum();
				}
			}
			break;
		case RIGHT:
			if (pos->getPosX() >= limHoriz - 5) {
				pos->setPosXY(pos->getPosX(), (pos->getPosY() + 1), (pos->getNum()));
				gotoxy(pos->getPosX(), pos->getPosY());
				std::cout << pos->getNum();
			}
			else {
				if (pos->getPosX() + saltos >= limHoriz - 5) {
					salto = saltos - ((pos->getPosX() + saltos) - (limHoriz - 5));
					pos->setPosXY(pos->getPosX() + salto, (pos->getPosY() + 1), (pos->getNum()));
					gotoxy(pos->getPosX(), pos->getPosY());
					std::cout << pos->getNum();
				}
				else {
					pos->setPosXY(pos->getPosX() + saltos, (pos->getPosY() + 1), (pos->getNum()));
					gotoxy(pos->getPosX(), pos->getPosY());
					std::cout << pos->getNum();
				}
			}
			break;
		case 13:
			gotoxy(pos->getPosX(), pos->getPosY());
			std::cout << pos->getNum();
			gotoxy((limHoriz / 2) - 7, limVer / 2);
			std::cout << "JUEGO PAUSADO";
			gotoxy((limHoriz / 2) - 14, (limVer / 2) + 1);
			std::cout << "PRESIONE CUALQUIER TECLA PARA CONTINUAR";
			_getch();
			break;
		default:
			if (pos->getPosY() >= limVer - 1) {
				num = 1 + rand() % (limiteAleatorio - 1);
				do {
					posY = 6 + rand() % ((limHoriz - 4) - 6);
				} while (posY % 6 != 0);
				pos->setPosXY(posY, (pos->getPosY() + 1), num);
				gotoxy(pos->getPosX(), pos->getPosY());
				std::cout << pos->getNum();
			}
			else {
				pos->setPosXY(pos->getPosX(), (pos->getPosY() + 1), (pos->getNum()));
				gotoxy(pos->getPosX(), pos->getPosY());
				std::cout << pos->getNum();
			}
			break;
		}

	}
	else {
		if (pos->getPosY() == 0) {
			num = 1 + rand() % (limiteAleatorio - 1);
			do {
				posY = (6 + rand() % ((limHoriz - 4) - 6));
			} while (posY % 6 != 0);
			pos->setPosXY(posY, (pos->getPosY() + 1), num);
			gotoxy(pos->getPosX(), pos->getPosY());
			std::cout << pos->getNum();
		}
		else {
			if (pos->getPosY() >= limVer - 1) {
				num = 1 + rand() % (limiteAleatorio - 1);
				do {
					posY = (6 + rand() % ((limHoriz - 4) - 6));
				} while (posY % 6 != 0);
				pos->setPosXY(posY, (1), num);
				gotoxy(pos->getPosX(), pos->getPosY());
				std::cout << pos->getNum();
			}
			else {
				pos->setPosXY(pos->getPosX(), (pos->getPosY() + 1), (pos->getNum()));
				gotoxy(pos->getPosX(), pos->getPosY());
				std::cout << pos->getNum();
			}
		}
	}

}

void TetrisFuncion::comenzarJuego() {
	ajustarConsola();
	ajustarFuente(48);
	int columnas = 0, filas = 0;
	sacarTamano(columnas, filas);

	int n = 9;
	int m = 0;
	if (n >= 11) {
		m = 9;
	}
	else {
		m = n;
	}

	int maxh = 0;
	bool escape = true;
	int cont = 0;
	int maxv = 0;
	maxh = columnas - 2;
	maxv = filas;
	Posicion* pos = new Posicion();
	ListaDoble lista = ListaDoble();
	lista.listaDobleTetris(maxh - 9);
	system("color F0");
	TetrisFuncion tetris = TetrisFuncion(m + 1, 6);
	tetris.ocultarCursor();
	tetris.cuadro(maxv, maxh);
	do {
		if (lista.gano(n) == false) {
			escape = false;
		}
		if (lista.perdio(n) == false) {
			escape = false;
		}
		tetris.imprimir(maxv, maxh, pos);
		tetris.gotoxy(6, maxv - 1);
		lista.imprimirLista();
		lista.insertarEnLista(pos, pos->getNum(), maxv, maxh);
		Sleep(200);
	} while (escape);

	tetris.gotoxy(0, maxv + 10);
	lista.imprimirLista();
	system("pause");
}


