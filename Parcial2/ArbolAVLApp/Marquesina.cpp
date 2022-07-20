#include "Marquesina.h"

void Marquesina::crearHilo()
{
	hiloMarquee = std::thread( // se crea el hilo
		// le pasamos una funcion al hilo para que lo ejecute en un proceso aparte
		std::bind(&Marquesina::correrProceso, this)
	);
}

void Marquesina::correrProceso()
{
	while (true) {
		int ancho = getAnchoConsola();

		if (caracteres_.empty()) {
			int x = ancho;

			while (!cola_.empty()) {
				auto caracter = cola_.front();
				caracter.x(x + 1);

				caracteres_.push_back(caracter);
				cola_.pop();
				x++;
			}
		}

		for (auto& caracter : caracteres_) {
			caracter.move(-1, 0);

			if (caracter.x() >= ancho) {
				continue;
			}

			if (caracter.x() < 0) {
				cola_.push(caracter);
				caracteres_.erase(caracteres_.begin());
			}

			CHAR_INFO* lpBuffer = (CHAR_INFO*)calloc(1, sizeof(CHAR_INFO));
			lpBuffer[0].Char.AsciiChar = caracter.valor();
			lpBuffer[0].Attributes = 15;

			SMALL_RECT posicion;
			posicion.Left = (SHORT)caracter.x();
			posicion.Top = 0;
			posicion.Right = ancho;
			posicion.Bottom = 1;

			WriteConsoleOutputA(consola_out_, lpBuffer, { 1, 1 }, { 0, 0 }, &posicion);
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}
}

void Marquesina::ejecutar(std::string texto)
{
	texto_ = texto;
	consola_out_ = GetStdHandle(STD_OUTPUT_HANDLE);

	texto.push_back(' ');

	// creamos los caracteres iniciales
	int ancho = getAnchoConsola();
	int x = ancho;

	for (char c : texto) {
		caracteres_.push_back(MarquesinaCaracter(c, x + 1, 0));
		x++;
	}

	SetConsoleCursorPosition(consola_out_, { 0, 3 });

	// separamos el hilo de la marquesina del hilo principal del programa
	// para hacer esto usamos el metodo detach
	hiloMarquee.detach();
}

int Marquesina::getAnchoConsola() {
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	return csbi.srWindow.Right - csbi.srWindow.Left + 1;
}