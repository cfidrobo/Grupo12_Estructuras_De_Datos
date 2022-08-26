#pragma once
#include "aplicacion.h"
#include "menu.h"
#include <functional>

class ControladorLogin {
public:
	virtual void inicializar();
	void ingresar();
	void registrarse();

private:
	Menu menu;
};
