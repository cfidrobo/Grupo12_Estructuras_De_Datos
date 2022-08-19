#include "TetrisFuncion.h"

TetrisFuncion::TetrisFuncion(int limiteAleatorio, int saltos)
{
	srand(time(NULL));
	this->limiteAleatorio = limiteAleatorio;
	this->saltos = saltos;
}


TetrisFuncion::~TetrisFuncion()
{
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
void TetrisFuncion::ocultarCursor()
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = FALSE;
	SetConsoleCursorInfo(consoleHandle, &info);
}

void TetrisFuncion::imprimir(int limVer, int limHoriz, Posicion*& pos)
{
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
					posY = (3 + rand() % ((limHoriz - 4) - 3));
				} while (posY % 3 != 0);
				pos->setPosXY(posY, (pos->getPosY() + 1), num);
				gotoxy(pos->getPosX(), pos->getPosY());
				std::cout << pos->getNum();
			}
			else {
				if (pos->getPosY() + 5 >= limVer - 1) {
					num = 1 + rand() % (limiteAleatorio - 1);
					do {
						posY = 3 + rand() % ((limHoriz - 4) - 3);
					} while (posY % 3 != 0);
					pos->setPosXY(posY, (pos->getPosY() + 1), num);
					gotoxy(pos->getPosX(), pos->getPosY());
					std::cout << pos->getNum();
				}
				else {
					pos->setPosXY(pos->getPosX(), (pos->getPosY() + 3), (pos->getNum()));
					gotoxy(pos->getPosX(), pos->getPosY());
					std::cout << pos->getNum();
				}
			}
			break;
		case LEFT:
			if (pos->getPosX() <= 3) {
				pos->setPosXY(pos->getPosX(), (pos->getPosY() + 1), (pos->getNum()));
				gotoxy(pos->getPosX(), pos->getPosY());
				std::cout << pos->getNum();
			}
			else {
				if (pos->getPosX() - saltos <= 3) {
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
		case UP:
			if (pos->getPosY() >= limVer - 1) {
				num = 1 + rand() % (limiteAleatorio - 1);
				do {
					posY = (3 + rand() % ((limHoriz - 4) - 3));
				} while (posY % 3 != 0);
				pos->setPosXY(posY, (pos->getPosY() - 2), num);   ///
				gotoxy(pos->getPosX(), pos->getPosY());
				std::cout << pos->getNum();
			}
			else {
				if (pos->getPosY() + 5 >= limVer - 1) {
					num = 1 + rand() % (limiteAleatorio - 1);
					do {
						posY = 3 + rand() % ((limHoriz - 4) - 3);
					} while (posY % 3 != 0);
					pos->setPosXY(posY, (pos->getPosY() - 2), num);  ///
					gotoxy(pos->getPosX(), pos->getPosY());
					std::cout << pos->getNum();
				}
				else {
					pos->setPosXY(pos->getPosX(), (pos->getPosY() - 2), (pos->getNum())); ///
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
					posY = 3 + rand() % ((limHoriz - 4) - 3);
				} while (posY % 3 != 0);
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
				posY = (3 + rand() % ((limHoriz - 4) - 3));
			} while (posY % 3 != 0);
			pos->setPosXY(posY, (pos->getPosY() + 1), num);
			gotoxy(pos->getPosX(), pos->getPosY());
			std::cout << pos->getNum();
		}
		else {
			if (pos->getPosY() >= limVer - 1) {
				num = 1 + rand() % (limiteAleatorio - 1);
				do {
					posY = (3 + rand() % ((limHoriz - 4) - 3));
				} while (posY % 3 != 0);
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


