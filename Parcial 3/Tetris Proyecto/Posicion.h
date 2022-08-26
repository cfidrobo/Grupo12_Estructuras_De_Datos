#pragma once
class Posicion {
private:
	int posX;
	int posY;
	int num;
public:
	Posicion();
	~Posicion();
	void setPosXY(int x, int y, int num);
	int getPosX();
	int getPosY();
	int getNum();
};