#pragma once
#include "ControladorRegistro.h"

class ControladorReportes {
public:

	void mostrarClientes();
	void buscarCliente();
	void buscarAutomovil();
	void generarReporte();

private:
	ControladorRegistro controladorRegistro;
};
