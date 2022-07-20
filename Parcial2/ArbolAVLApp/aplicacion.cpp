#include "aplicacion.h"
#include "ControladorLogin.h"
#include "Marquesina.h"
#include <fstream>
#include <thread>
#include "Pixelador.h"
#include "arbol_avl.h"
#include "visualizador.h"
#include "funciones.h"
#include "Windows.h"

Aplicacion::Aplicacion() {
	menu = new Menu("Arbol AVL");
	menu->al_presionar_f1([]() {
		MessageBox(NULL, "manual de ayuda", "Ayuda", MB_OK | MB_ICONQUESTION);
	});
}

void Aplicacion::iniciar() {
	Marquesina marquee;
	ControladorLogin login;

	marquee.ejecutar("Universidad de las fuerzas armadas ESPE - Arbol AVL");
	login.inicializar();

    /////////////////////////////////////////////////////////////////
    Menu menu3("Extras");
	menu3.agregar(MenuOpcion("Manual ayuda", [&]() {
		mostrarManual();
	}));
	menu3.agregar(MenuOpcion("Pixelar imagen", [&]() {
		pixelarImagen();
	}));
	menu3.agregar(MenuOpcion("Generar reporte", [&]() {
		generarReporte();
	}));
	menu3.agregar(MenuOpcion("Backup", [&]() {
		Menu menuBackup("Backups");

		menuBackup.agregar(MenuOpcion("Respaldar", [&](){
			std::string nombre = Funciones::generar_formato_hora("", ".backup.txt");
			arbol.serializar(nombre);
			std::cout << "[" << nombre << " guardado con exito]\n";
		}));

		menuBackup.agregar(MenuOpcion("Cargar", [&]() {
			std::string seleccionado = "";

            Menu archivos("Archivos de respaldo");
			std::vector<std::string> lista = Funciones::listar_archivos(".backup.txt");

			for (const std::string& nombre : lista) {
				archivos.agregar(MenuOpcion(nombre, [nombre, this]() {

					// check if file exists
					std::string ruta(nombre);
					std::ifstream infile(ruta);
                    
                    if (infile.good()) {
						arbol.deserializar(ruta, [&](std::string valor) {
							return std::stoi(valor);
						});
						std::cout << "[" << ruta << " cargado con exito]\n";
                    } else {
						std::cout << "['" << ruta << "' no existe]\n";
                    }
                }));
			}

			archivos.agregar(archivos.opcion_salir("Cancelar"));
			archivos.iniciar();
		}).wait(false));
		menuBackup.agregar(menuBackup.opcion_salir("Regresar"));
		menuBackup.iniciar();
	}));
	menu3.agregar(menu3.opcion_salir("Regresar"));

	menu->agregar(MenuOpcion(
		"Arbol AVL", [&]() {
			menuArbolAVL();
		},
		false));

	menu->agregar(MenuOpcion(
		"Extras", [&]() {
			menu3.iniciar();
		},
		false));

	menu->agregar(menu->opcion_salir("Salir"));
	menu->iniciar();
}

void Aplicacion::menuArbolAVL() {
	Menu menu1("Arbol AVL");
	ArbolVisualizador<int> visualizador;
    

	menu1.agregar(MenuOpcion("Insertar", [&]() {
		int valor = Funciones::leer_entero("ingrese un valor: ");
		arbol.insertar(valor);
		visualizador.imprimir(arbol);
	}));

	menu1.agregar(MenuOpcion("Eliminar", [&]() {
		int valor = Funciones::leer_entero("ingrese un valor: ");
		arbol.eliminar(valor);
		visualizador.imprimir(arbol);
	}));

	menu1.agregar(MenuOpcion("Buscar", [&]() {
		int valor = Funciones::leer_entero("ingrese un valor: ");
		NodoAVL<int>* encontrado = arbol.buscar(valor);

		std::cout << std::endl
				  << std::endl;

		if (encontrado == nullptr) {
            std::cout << "[no se encontro el valor]" << std::endl;
        } else {
			std::cout << "[se encontro el valor]" << std::endl;
			visualizador.imprimir(arbol);
		}
	}));

	menu1.agregar(MenuOpcion("Mostrar", [&]() {
		visualizador.imprimir(arbol);
	}));

	menu1.agregar(menu1.opcion_salir("Regresar"));
	menu1.iniciar();
}

void Aplicacion::mostrarManual() {
	system("HH.EXE ms-its:manual.chm");
}

void Aplicacion::pixelarImagen() {
	Pixelador pixelador("grupo.bmp");
	pixelador.pixelar();
}

void Aplicacion::generarReporte() {
	std::string sufijo = std::to_string(Funciones::generar_aleatorio(1000, 9999));
	std::string in = "inp_" + sufijo + ".html";
	std::string out = "reporte_" + sufijo + ".pdf";
	std::ofstream inFile(in);
	std::stringstream inSrc;

	std::stringstream inorden;

	arbol.recorrer([&](int v) {
		inorden << v << "  ";
	}, TipoRecorrido::INORDEN);

	inSrc << "<html><body><h1>ARBOL AVL</h1><br>";
	inSrc << "<div>";
	inSrc << "<strong>INORDEN: </strong><code>" << inorden.str() << "</code><br>";
	inSrc << "</div><br><br>";
	inSrc << "</body></html>";
	inFile << inSrc.str();
	inFile.close();

	system((std::string("pdfgen ") + in + " ./" + out).c_str());
}

Menu* Aplicacion::get_menu() {
	return menu;
}