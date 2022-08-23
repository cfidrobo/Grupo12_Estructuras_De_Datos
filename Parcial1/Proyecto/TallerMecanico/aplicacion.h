#pragma once
#include "menu.h"
#include "servicio.h"

class Aplicacion {
public:
	Aplicacion();
	void iniciar();
	Menu* get_menu();

private:
	void mostrarManual();
	void pixelarImagen();

	Menu* menu;
};
