#pragma once
#include "ListaCircularDoble.h"
#include "definiciones.h"

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
#include <rang/rang.hpp>
#include <cfloat>
#include <Windows.h>
#include <conio.h>
#include <filesystem>

class Funciones {
public:
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

	// generate string with format dd-mm-yyyy_hh:mm_{string}
	static std::string generar_formato_hora(std::string prefix = "", std::string postfix = "") {
        std::string fecha_hora = "";
        time_t tiempo = time(0);
        struct tm *tlocal = localtime(&tiempo);
        char output[128];

        strftime(output, 128, "%Y%m%d%H%M%S", tlocal);
        fecha_hora = prefix + std::string(output) + postfix;
        return fecha_hora;
    }

	// list filenames from directory
	static std::vector<std::string> listar_archivos(std::string busqueda) {
        std::vector<std::string> archivos;
        std::string path = "./";
        for (auto & p : std::filesystem::directory_iterator(path)) {
            if (p.path().string().find(busqueda) != std::string::npos) {
				std::string ruta = p.path().string();
                ruta.erase(0, 2);
                archivos.push_back(ruta);
            }
        }
        return archivos;
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

	static std::string leer_cadena_regex(const std::string etiqueta, std::string regex) {
		std::string leido;
		std::regex cadena_regex(regex);

		do {
			leido = leer_cadena(etiqueta);

			if (!std::regex_match(leido, cadena_regex)) {
				mostrar_mensaje("Formato invalido", TipoMensaje::Error);
			}
		} while (!std::regex_match(leido, cadena_regex));

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

	static double leer_flotante(std::string etiqueta, double minimo = DBL_MIN, double maximo = DBL_MAX) {
		double leido;
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

	static bool cedula_valida(const std::string cedula) {
		if (cedula.length() != 10) {
			return false;
		}

		int sum_par = 0;
		int sum_impar = 0;
		int sum;
		int i = 1;

		std::string digits = cedula.substr(0, cedula.size() - 1);

		for (char& c : digits) {
			int digit = c - '0';
			if (i % 2 == 0) {
				sum_par += digit;
			} else {
				if ((digit * 2) > 9) {
					sum_impar += (digit * 2) - 9;
				} else {
					sum_impar += (digit * 2);
				}
			}
			i++;
		}

		sum = sum_par + sum_impar;

		int verifier = cedula.at(cedula.size() - 1) - '0';
		int higher = (10 - (sum % 10)) + sum;

		if (sum % 10 == 0) {
			return verifier == 0;
		}

		return (higher - sum) == verifier;
	}

	static ListaCircularDoble<std::string> dividir_cadena(std::string cadena, std::string delimitador) {
		ListaCircularDoble<std::string> partes;
		size_t start = 0;
		auto end = cadena.find(delimitador);

		while (end != std::string::npos) {
			std::string parte = cadena.substr(start, end - start);
			partes.insertarFinal(parte);
			start = end + delimitador.length();
			end = cadena.find(delimitador, start);
		}

		partes.insertarFinal(cadena.substr(start, end));
		return partes;
	}

	static std::string trim_cadena(std::string cadena) {
		auto wsfront = std::find_if_not(cadena.begin(), cadena.end(), [](int c) { return std::isspace(c); });
		auto wsback = std::find_if_not(cadena.rbegin(), cadena.rend(), [](int c) { return std::isspace(c); }).base();
		return (wsback <= wsfront ? std::string() : std::string(wsfront, wsback));
	}

	static void leer_lineas(
		std::string nombre_archivo,
		std::function<void(std::string linea, ListaCircularDoble<std::string> datos)> callback) {
		std::ifstream archivo(nombre_archivo);
		std::string linea;

		while (std::getline(archivo, linea)) {
			linea = Funciones::trim_cadena(linea);

			if (linea.empty()) {
				continue;
			}

			auto columnas = Funciones::dividir_cadena(linea, ",");
			int indice = 0;
            
			columnas.recorrer([&](std::string token) {
				columnas.obtenerNodo(indice)->setValor(Funciones::trim_cadena(token));
				indice++;
			});

			callback(linea, columnas);
		}

		archivo.close();
	}

	static std::string cadena_minusculas(std::string cadena) {
		std::string resultado(cadena);
        
		std::transform(resultado.begin(), resultado.end(), resultado.begin(), [](unsigned char c) {
			return std::tolower(c);
		});

		return resultado;
	}

	static void mostrar_mensaje(std::string mensaje, TipoMensaje tipo = TipoMensaje::Informativo) {
		rang::fg color;

		if (tipo == TipoMensaje::Informativo) {
			color = rang::fg::cyan;
		} else if (tipo == TipoMensaje::Correcto) {
			color = rang::fg::green;
		} else if (tipo == TipoMensaje::Error) {
			color = rang::fg::red;
		} else {
			color = rang::fg::cyan;
		}

		std::cout
			<< std::endl << rang::style::bold << color
			<< "(" << mensaje << ")"
			<< std::endl << rang::style::reset;
	}

	static bool existe_archivo(std::string nombre_archivo) {
		return std::ifstream(nombre_archivo.c_str()).good();
	}

	static int generar_aleatorio(int minimo = INT_MIN, int maximo = INT_MAX) {
		std::random_device rd;
		static std::mt19937 gen(rd());
		std::uniform_int_distribution<> dis(minimo, maximo);

		return dis(gen);
	}

	static bool confirmar(std::string pregunta) {
		char respuesta = 'n';
		std::string entrada;

		do {
			std::cout << pregunta << " (s/n): ";
			std::cin >> entrada;

			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

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

	static std::string leer_password(std::string prompt) {
		std::string password;
		int i = 0;
		int ch;

		std::cout << prompt;

		while (true) {
			ch = _getch();

			if (ch == ' ' || ch == 27) {
				continue;
			} else if (ch == 8) {
				if (i > 0) {
					std::cout << "\b \b";
					password.pop_back();
					--i;
				} else {
					continue;
				}
			} else if (ch == '\r' || ch == '\t') {
				break;
			} else if (ch == 0 || ch == 224) {
				ch = _getch();
				continue;
			} else {
				password.push_back(ch);
				i++;
				std::cout << "*";
			}
		}

		std::cout << std::endl
				  << std::endl;

		return password;
	}
};
