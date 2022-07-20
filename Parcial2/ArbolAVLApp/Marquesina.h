#pragma once
#include <thread>
#include <queue>
#include <vector>
#include <functional>
#include <string>
#include <Windows.h>

class MarquesinaCaracter {
public:
	MarquesinaCaracter(char c, int x = 0, int y = 0)
		: c_(c), x_(x), y_(y) {}

	char valor() { return c_; }
	int x() { return x_; }
	int y() { return y_; }

	void x(int x) { x_ = x; }
	void y(int y) { y_ = y; }

	void move(int x, int y) {
		x_ += x;
		y_ += y;
	}

private:
	char c_;
	int x_;
	int y_;
};

class Marquesina {
public:
	Marquesina() {
		crearHilo();
	}

	void ejecutar(std::string texto);

private:
	void crearHilo();
	void correrProceso();
	int getAnchoConsola();

	HANDLE consola_out_;
	std::thread hiloMarquee;
	std::string texto_;
	std::queue<MarquesinaCaracter> cola_;
	std::vector<MarquesinaCaracter> caracteres_;
};

