#include "aplicacion.h"
#include <windows.h>
#pragma execution_character_set("utf-8")

int main() {
	SetConsoleOutputCP(65001);
	Aplicacion app;
	app.iniciar();
}
