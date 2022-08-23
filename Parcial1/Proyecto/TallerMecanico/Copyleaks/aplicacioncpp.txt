#include "aplicacion.h"
#include "ControladorLogin.h"
#include "Marquesina.h"
#include "ControladorReportes.h"
#include "ControladorRegistro.h"
#include <fstream>
#include "Pixelador.h"

Aplicacion::Aplicacion() {
	menu = new Menu("Taller mecanico");
}

void Aplicacion::iniciar() {
	Marquesina marquee;
	ControladorLogin login;

	marquee.ejecutar("Universidad de las fuerzas armadas ESPE - Taller mecanico");
	login.inicializar();

    Menu menu1("Registro");

    ControladorRegistro controladorRegistro;
	ControladorReportes controladorReportes;
	
	menu1.agregar(MenuOpcion("Registrar cliente", [&](){
		controladorRegistro.registrarCliente();
	}));
    
	menu1.agregar(MenuOpcion("Registrar asistencia", [&]() {
		controladorRegistro.registrarAsistencia();
	}));
	
	menu1.agregar(menu1.opcion_salir("Regresar"));

    /////////////////////////////////////////////////////////////////

	Menu menu2("Reportes");
	menu2.agregar(MenuOpcion("Ver clientes", [&]() {
		controladorReportes.mostrarClientes();
	}));
	menu2.agregar(MenuOpcion("Buscar cliente", [&]() {
		controladorReportes.buscarCliente();
	}));
	menu2.agregar(MenuOpcion("Buscar auto", [&]() {
		controladorReportes.buscarAutomovil();
	}));
	menu2.agregar(MenuOpcion("Generar reporte", [&]() {
		controladorReportes.generarReporte();
	}));
	menu2.agregar(menu2.opcion_salir("Regresar"));
    
    Menu menu3("Ayuda");
	menu3.agregar(MenuOpcion("Manual ayuda", [&]() {
		mostrarManual();
	}));
	menu3.agregar(MenuOpcion("Desarrolladores", [&]() {
		std::cout << 
			"------------------------Informacion del Programa------------------------\n\n"
			"este programa fue desarrollado para llevar un registro de los clientes\n"
			"en una mecanica por parte de los empleados, registrar su asistencia y generar archivos pdf\n\n"
			"desarrolladores:\n"
			"-Cristian Idrobo"
			"-John Limones" << std::endl;
	}));
	menu3.agregar(MenuOpcion("Pixelar imagen", [&]() {
		pixelarImagen();
	}));
	menu3.agregar(menu3.opcion_salir("Regresar"));

	menu->agregar(MenuOpcion(
		"Registro", [&]() {
            menu1.iniciar();
		},
		false));

	menu->agregar(MenuOpcion(
		"Reportes", [&]() {
			menu2.iniciar();
		},
		false));

	menu->agregar(MenuOpcion(
		"Ayuda", [&]() {
			menu3.iniciar();
		},
		false));

	menu->agregar(menu->opcion_salir("Salir"));
	menu->iniciar();
}

Menu* Aplicacion::get_menu() {
	return menu;
}

void Aplicacion::mostrarManual() {
    std::ifstream file("manual.txt");
    std::string line;
    
    while (std::getline(file, line)) {
        std::cout << line << std::endl;
    }
    
    file.close();
}

void Aplicacion::pixelarImagen() {
	Pixelador pixelador("grupo.bmp");
	pixelador.pixelar();
}
