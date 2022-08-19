#include "Posicion.h"

Posicion::Posicion() {
	this->posX = 0;
	this->posY = 0;
	this->num = 0;
}
Posicion::~Posicion() {}
void Posicion::setPosXY(int x, int y, int num) {
	this->posX = x;
	this->posY = y;
	this->num = num;
}
int Posicion::getPosX() {
	return this->posX;
}
int Posicion::getPosY() {
	return this->posY;
}
int Posicion::getNum() {
	return this->num;
}
