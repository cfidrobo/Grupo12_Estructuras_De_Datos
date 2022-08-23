#pragma once
#include "ListaCircularDoble.h"
#include "Cliente.h"
#include "Automovil.h"
#include "Asistencia.h"

class ControladorRegistro {
public:
	void registrarCliente();
	void registrarAsistencia();

	ListaCircularDoble<Cliente> leerClientes();
	void guardarCliente(Cliente cliente);
	void mostrarClientes();
    
    ListaCircularDoble<Automovil> leerAutomoviles();
    void guardarAutomovil(Automovil automovil);
    void mostrarAutomoviles();
    
    ListaCircularDoble<Asistencia> leerAsistencias();
    void guardarAsistencia(Asistencia asistencia);

    std::string generarEmail(Automovil automovil);
};
