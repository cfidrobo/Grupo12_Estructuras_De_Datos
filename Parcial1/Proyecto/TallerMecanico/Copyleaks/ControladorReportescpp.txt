#include "ControladorReportes.h"
#include "funciones.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

void ControladorReportes::mostrarClientes() {
	auto clientes = controladorRegistro.leerClientes();
    
    clientes.recorrer([](Cliente cliente) {
		std::cout << "CEDULA: " << cliente.getCedula() << std::endl;
		std::cout << "NOMBRES: " << cliente.getNombres() << std::endl;
		std::cout << "APELLIDOS: " << cliente.getApellidos() << std::endl;
		std::cout << "EMAIL: " << cliente.getEmail() << std::endl;
		std::cout << "AUTOMOVIL:" << std::endl;
		std::cout << "    MARCA: " << cliente.getAutomovil().getMarca() << std::endl;
		std::cout << "    MODELO: " << cliente.getAutomovil().getModelo() << std::endl;
		std::cout << "    PLACA: " << cliente.getAutomovil().getPlaca() << std::endl;
		std::cout << "    COLOR: " << cliente.getAutomovil().getColor() << std::endl;
		std::cout << "---------------------------------------------------------------" << std::endl;
    });
}

void ControladorReportes::buscarCliente() {
	auto clientes = controladorRegistro.leerClientes();
	std::string cedula;
	Nodo<Cliente>* encontrado;

	if (clientes.estaVacio()) {
		Funciones::mostrar_mensaje("No se encontraron clientes registrados", TipoMensaje::Error);
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

	Cliente cliente = encontrado->getValor();

	std::cout << "CEDULA: " << cliente.getCedula() << std::endl;
	std::cout << "NOMBRES: " << cliente.getNombres() << std::endl;
	std::cout << "APELLIDOS: " << cliente.getApellidos() << std::endl;
	std::cout << "EMAIL: " << cliente.getEmail() << std::endl;
	std::cout << "AUTOMOVIL:" << std::endl;
	std::cout << "    MARCA: " << cliente.getAutomovil().getMarca() << std::endl;
	std::cout << "    MODELO: " << cliente.getAutomovil().getModelo() << std::endl;
	std::cout << "    PLACA: " << cliente.getAutomovil().getPlaca() << std::endl;
	std::cout << "    COLOR: " << cliente.getAutomovil().getColor() << std::endl;
}


void ControladorReportes::buscarAutomovil() {
	auto asistencias = controladorRegistro.leerAsistencias();
	auto clientes = controladorRegistro.leerClientes();
    std::string placa;
	Nodo<Cliente>* encontrado;

	if (clientes.estaVacio()) {
		Funciones::mostrar_mensaje("No existen clientes registrados", TipoMensaje::Error);
		return;
	}

    do {
		placa = Funciones::leer_cadena_regex("Ingresa la placa (AAA-####): ", "^[a-zA-Z]{3}-[0-9]{4}$");

		encontrado = clientes.buscar([placa](Cliente c) {
			return c.getAutomovil().getPlaca() == placa;
		});

		if (!encontrado) {
			Funciones::mostrar_mensaje("Placa no registrada", TipoMensaje::Error);
			continue;
		}

		break;
	} while (true);

	Cliente cliente = encontrado->getValor();
	int totalAsistencias = 0;
    
    asistencias.recorrer([&](Asistencia asistencia) {
		if (placa == asistencia.getCliente().getAutomovil().getPlaca()) {
			totalAsistencias++;
		}
	});

    std::cout << "AUTOMOVIL:" << std::endl;
	std::cout << "    MARCA: " << cliente.getAutomovil().getMarca() << std::endl;
	std::cout << "    MODELO: " << cliente.getAutomovil().getModelo() << std::endl;
	std::cout << "    PLACA: " << cliente.getAutomovil().getPlaca() << std::endl;
	std::cout << "    COLOR: " << cliente.getAutomovil().getColor() << std::endl;
	std::cout << "    ASISTENCIAS: " << totalAsistencias;
}

void ControladorReportes::generarReporte() {
	std::string sufijo = std::to_string(Funciones::generar_aleatorio(1000, 9999));
	std::string in = "inp_" + sufijo + ".html";
	std::string out = "reporte_" + sufijo + ".pdf";
	std::ofstream inFile(in);
	auto asistencias = controladorRegistro.leerAsistencias();
	std::stringstream inSrc;

	inSrc << "<html><body><h1>Reporte</h1><br>";
    
	asistencias.recorrer([&](Asistencia asistencia) {
		inSrc << "<div>";
		inSrc << "<strong>HORA:</strong> " << asistencia.getHora() << "<br>";
		inSrc << "DETALLE: " << asistencia.getDetalle() << "<br>";
		inSrc << "<strong>CLIENTE: </strong><code>" << asistencia.getCliente().getNombres() << " ";
		inSrc << asistencia.getCliente().getApellidos() << "</code><br>";
		inSrc << "</div><br><br>";
	});
	inSrc << "</body></html>";
    inFile << inSrc.str();
	inFile.close();

	system((std::string("pdfgen ") + in + " ./" + out).c_str());
}
