#include "ControladorRegistro.h"
#include <string>
#include "funciones.h"

void ControladorRegistro::registrarCliente() {
	std::string cedula;
	std::string nombres;
	std::string apellidos;
	std::string email;

	std::cout << "Registrar cliente:" << std::endl << std::endl;

	apellidos = Funciones::leer_cadena_regex("Ingrese los apellidos: ", "^[a-zA-Z]{2,}(\\s[a-zA-Z]{2,})?$");
	nombres = Funciones::leer_cadena_regex("Ingrese los nombres: ", "^[a-zA-Z]{2,}(\\s[a-zA-Z]{2,})?$");

	auto clientes = leerClientes();

	do {
		cedula = Funciones::leer_cadena_regex("Ingrese la cedula: ", "^[0-9]{10}$");

		if (!Funciones::cedula_valida(cedula)) {
			Funciones::mostrar_mensaje("Cedula invalida", TipoMensaje::Error);
			continue;
		}

		auto encontrado = clientes.buscar([cedula](Cliente c) {
			return c.getCedula() == cedula;
		});

		if (encontrado) {
			Funciones::mostrar_mensaje("Cedula ya registrada", TipoMensaje::Error);
			continue;
		}

		break;
	} while (true);

	std::string marca;
	std::string modelo;
	std::string placa;
	std::string color;

	std::cout 
		<< std::endl << std::endl
		<< "Registrar automovil: " << std::endl << std::endl;
	marca = Funciones::leer_cadena("Ingrese la marca: ");
	modelo = Funciones::leer_cadena("Ingrese el modelo: ");
	
	do {
		placa = Funciones::leer_cadena_regex("Ingresa la placa (AAA-####): ", "^[a-zA-Z]{3}-[0-9]{4}$");

		auto encontrado = clientes.buscar([placa](Cliente c) {
			return c.getAutomovil().getPlaca() == placa;	
		});

		if (encontrado) {
			Funciones::mostrar_mensaje("Placa ya registrada", TipoMensaje::Error);
			continue;
		}

		break;
	} while (true);

	color = Funciones::leer_cadena("Ingrese el color: ");

	Automovil automovil(marca, modelo, color, placa);
	Cliente cliente(cedula, nombres, apellidos, generarEmail(automovil), automovil);

	guardarAutomovil(automovil);
	guardarCliente(cliente);
	Funciones::mostrar_mensaje("Datos guardados", TipoMensaje::Correcto);
}

void ControladorRegistro::registrarAsistencia() {
	std::string cedula;
	auto clientes = leerClientes();
	Nodo<Cliente>* encontrado;

	if (clientes.estaVacio()) {
		Funciones::mostrar_mensaje("No existen clientes registrados", TipoMensaje::Error);
		return;
	}

	do {
		cedula = Funciones::leer_cadena_regex("Ingrese la cedula: ", "^[0-9]{10}$");

		if (!Funciones::cedula_valida(cedula)) {
			Funciones::mostrar_mensaje("Cedula invalida", TipoMensaje::Error);
			continue;
		}

		encontrado = clientes.buscar([cedula](Cliente c) {
			return c.getCedula() == cedula;
		});

		if (!encontrado) {
			Funciones::mostrar_mensaje("Cedula no registrada", TipoMensaje::Error);
			continue;
		}

		break;
	} while (true);

	std::string hora = Funciones::leer_cadena_regex("Ingrese la hora (hh:mm): ", "^([0-1]?[0-9]|2[0-3]):[0-5][0-9]$");
	std::string detalle = Funciones::leer_cadena("Ingrese el detalle: ");
	float valor = Funciones::leer_flotante("Ingrese el costo total: ", 0.f);

	Cliente cliente = encontrado->getValor();
	Asistencia asistencia(cliente, hora, detalle, valor);
	guardarAsistencia(asistencia);
	Funciones::mostrar_mensaje("Datos guardados", TipoMensaje::Correcto);
}

ListaCircularDoble<Cliente> ControladorRegistro::leerClientes() {
	ListaCircularDoble<Cliente> clientes;
	auto automoviles = leerAutomoviles();

	Funciones::leer_lineas("clientes.txt", [&](std::string linea, ListaCircularDoble<std::string> columnas) {
		std::string cedula = columnas.obtenerNodo(0)->getValor();
		std::string nombres = columnas.obtenerNodo(1)->getValor();
		std::string apellidos = columnas.obtenerNodo(2)->getValor();
		std::string email = columnas.obtenerNodo(3)->getValor();
		std::string placa = columnas.obtenerNodo(4)->getValor();

		auto automovil = automoviles.buscar([placa](Automovil a) {
			return a.getPlaca() == placa;	
		});

		if (!automovil) {
			return;
		}

		Cliente cliente(cedula, nombres, apellidos, email, automovil->getValor());
		clientes.insertarFinal(cliente);
	});

	return clientes;
}

void ControladorRegistro::guardarCliente(Cliente cliente) {
	auto clientes = leerClientes();
	std::ofstream archivo("clientes.txt", std::ios::trunc);

	clientes.recorrer([&](Cliente c) {
		archivo << c.toString() << std::endl;		
	});

	archivo << cliente.toString() << std::endl;
	archivo.close();
}

void ControladorRegistro::mostrarClientes() {
}

ListaCircularDoble<Automovil> ControladorRegistro::leerAutomoviles() {
	ListaCircularDoble<Automovil> automoviles;

	Funciones::leer_lineas("automoviles.txt", [&](std::string linea, ListaCircularDoble<std::string> columnas) {
		std::string marca = columnas.obtenerNodo(0)->getValor();
		std::string modelo = columnas.obtenerNodo(1)->getValor();
		std::string color = columnas.obtenerNodo(2)->getValor();
		std::string placa = columnas.obtenerNodo(3)->getValor();

		Automovil automovil(marca, modelo, color, placa);
		automoviles.insertarFinal(automovil);
	});

	return automoviles;
}

void ControladorRegistro::guardarAutomovil(Automovil automovil) {
	auto automoviles = leerAutomoviles();
	std::ofstream archivo("automoviles.txt", std::ios::trunc);

	automoviles.recorrer([&](Automovil a) {
		archivo << a.toString() << std::endl;
	});

	archivo << automovil.toString() << std::endl;
	archivo.close();
}

void ControladorRegistro::mostrarAutomoviles() {
}

ListaCircularDoble<Asistencia> ControladorRegistro::leerAsistencias() {
	ListaCircularDoble<Asistencia> asistencias;
	auto clientes = leerClientes();

	Funciones::leer_lineas("asistencias.txt", [&](std::string linea, ListaCircularDoble<std::string> columnas) {
		std::string cedula = columnas.obtenerNodo(0)->getValor();
		std::string hora = columnas.obtenerNodo(1)->getValor();
		std::string detalle = columnas.obtenerNodo(2)->getValor();
		std::string valorStr = columnas.obtenerNodo(3)->getValor();
		float valor = std::stof(valorStr);

		auto encontrado = clientes.buscar([&](Cliente cliente) {
			return cliente.getCedula() == cedula;	
		});

		if (!encontrado) {
			return;
		}

		Cliente cliente = encontrado->getValor();
		Asistencia asistencia(cliente, hora, detalle, valor);
		asistencias.insertarFinal(asistencia);
	});

	return asistencias;
}

void ControladorRegistro::guardarAsistencia(Asistencia asistencia) {
	auto asistencias = leerAsistencias();
	std::ofstream archivo("asistencias.txt", std::ios::trunc);

	asistencias.recorrer([&](Asistencia a) {
		archivo << a.toString() << std::endl;
	});

	archivo << asistencia.toString() << std::endl;
	archivo.close();
}

std::string ControladorRegistro::generarEmail(Automovil automovil) {
	std::string prefijo = 
		Funciones::cadena_minusculas(automovil.getPlaca()) +
		std::string(1, std::tolower(automovil.getColor()[0])) +
		Funciones::cadena_minusculas(automovil.getMarca());
	std::string sufijo = "@evaluacion.com";
	std::string email = prefijo + sufijo;

	return email;
}
