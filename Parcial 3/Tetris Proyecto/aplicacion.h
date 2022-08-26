#pragma once
#include "menu.h"
#include "servicio.h"
#include "arbol_avl.h"
#include "visualizador.h"


class Aplicacion {
public:
	Aplicacion();
	void iniciar();
	Menu* get_menu();

private:
	void menuArbolAVL();
	void mostrarManual();
	void pixelarImagen();
	void generarReporte();

	ArbolAVL<int> arbol;
	Menu* menu;
	bool salir = false;
};
