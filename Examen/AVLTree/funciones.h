#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <limits>
#include <random>
#include <cctype>
#include <regex>
#include <iomanip>
#include <sstream>
#include <cfloat>
#include <Windows.h>
#include <conio.h>
#include <filesystem>

class Funciones {
public:
	static int reducir_numero(int n) {
		int sum = 0;
		while (n > 0 || sum > 9) {
			if (n == 0) {
				n = sum;
				sum = 0;
			}
			sum += n % 10;
			n /= 10;
		}
		
		return sum;
	}

	static void limpiar_consola() {
		COORD topLeft = { 0, 0 };
		HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
		CONSOLE_SCREEN_BUFFER_INFO screen;
		DWORD written;

		GetConsoleScreenBufferInfo(console, &screen);
		FillConsoleOutputCharacterA(
			console, ' ', screen.dwSize.X * screen.dwSize.Y, topLeft, &written);
		FillConsoleOutputAttribute(
			console, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE,
			screen.dwSize.X * screen.dwSize.Y, topLeft, &written);
		SetConsoleCursorPosition(console, topLeft);
	}

	static std::string leer_cadena(const std::string etiqueta, bool permitir_vacio = false) {
		std::string leido;

		if (permitir_vacio) {
			std::getline(std::cin, leido);
		} else {
			while ((std::cout << etiqueta),
				std::getline(std::cin, leido), leido.empty())
				;
		}

		return leido;
	}

	static int leer_entero(std::string etiqueta, int minimo = INT_MIN, int maximo = INT_MAX) {
		int leido;
		bool valido;

		do {
			std::cout << etiqueta;
			std::cin >> leido;

			valido = !std::cin.fail();

			std::cin.clear();
			std::cin.ignore();
		} while (!valido || leido < minimo || leido > maximo);

		return leido;
	}

	static bool cadenas_iguales(std::string a, std::string b) {
		a = trim_cadena(cadena_minusculas(a));
		b = trim_cadena(cadena_minusculas(b));

		return a == b;
	}



	static std::string trim_cadena(std::string cadena) {
		auto wsfront = std::find_if_not(cadena.begin(), cadena.end(), [](int c) { return std::isspace(c); });
		auto wsback = std::find_if_not(cadena.rbegin(), cadena.rend(), [](int c) { return std::isspace(c); }).base();
		return (wsback <= wsfront ? std::string() : std::string(wsfront, wsback));
	}

	static std::string cadena_minusculas(std::string cadena) {
		std::string resultado(cadena);
        
		std::transform(resultado.begin(), resultado.end(), resultado.begin(), [](unsigned char c) {
			return std::tolower(c);
		});

		return resultado;
	}

	static void mostrar_mensaje(std::string mensaje) {
		std::cout
			<< std::endl
			<< "(" << mensaje << ")"
			<< std::endl;
	}

	static bool confirmar(std::string pregunta) {
		char respuesta = 'n';
		std::string entrada;

		do {
			std::cout << pregunta << " (s/n): ";
			std::cin >> entrada;

			std::cin.clear();
			std::cin.ignore(9999, '\n');

			if (entrada.length() > 1) continue;

			respuesta = std::tolower(entrada.at(0));
		} while (respuesta != 's' && respuesta != 'n');

		return (respuesta == 's');
	}

	static std::string decimal_fixed(float valor, int precision = 2) {
		std::stringstream ss;
		ss << std::fixed << std::setprecision(precision) << valor;
		return ss.str();
	}


};
