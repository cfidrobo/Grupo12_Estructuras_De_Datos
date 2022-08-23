#include "ControladorLogin.h"
#include "menu.h"
#include "funciones.h"
#include "ListaCircularDoble.h"
#include <vector>
#include <hashlib/hashlibpp.h>

void ControladorLogin::inicializar() {
	menu.agregar(MenuOpcion("Ingresar", [this]() {
		this->ingresar();
	}));
    
	menu.agregar(MenuOpcion("Registrarse", [this]() {
		this->registrarse();
	}));

    menu.agregar(MenuOpcion("Salir", [](){
		exit(0);
	}));
    
    menu.iniciar();
}

void ControladorLogin::ingresar() {
	std::string usuario = Funciones::leer_cadena("Ingrese el usuario: ");
	std::string clave = Funciones::leer_password("Ingrese la contrasenia: ");
	std::vector<std::vector<std::string>> usuarios;
	hashwrapper* md5 = new md5wrapper();

	Funciones::leer_lineas("usuarios.txt",
		[&](std::string linea, ListaCircularDoble<std::string> datos) {
			std::string usuario_archivo = datos.obtenerNodo(0)->getValor();
			std::string clave_archivo = datos.obtenerNodo(1)->getValor();
			usuarios.push_back({ usuario_archivo, clave_archivo });
	});

	bool encontrado = false;
	bool valido = false;
    
	for (auto u : usuarios) {
		auto usuario_archivo = u.at(0);
        auto clave_archivo = u.at(1);

		if (Funciones::trim_cadena(usuario) == Funciones::trim_cadena(usuario_archivo)) {
			encontrado = true;
		} else {
			continue;
		}

		std::string clave_hash = md5->getHashFromString(clave);
        
		if (clave_hash == clave_archivo) {
			valido = true;
			break;
		}
	}

	if (!encontrado) {
		Funciones::mostrar_mensaje("Usuario no encontrado");
	} else if (!valido) {
        Funciones::mostrar_mensaje("contrasenia incorrecta");
	} else {
		std::cout << "\nIngreso exitoso\n";
		menu.detener();
	}
}

void ControladorLogin::registrarse() {
	std::ofstream archivo("usuarios.txt", std::ios::app);

    std::string usuario = Funciones::leer_cadena("Ingrese el usuario: ");
	std::string clave, clave2;
    std::vector<std::vector<std::string>> usuarios;
	hashwrapper* md5 = new md5wrapper();

    Funciones::leer_lineas("usuarios.txt",
		[&](std::string linea, ListaCircularDoble<std::string> datos) {
			std::string usuario_archivo = datos.obtenerNodo(0)->getValor();
			std::string clave_archivo = datos.obtenerNodo(1)->getValor();
			usuarios.push_back({usuario_archivo, clave_archivo});
	});

	for (auto usuario_archivo : usuarios) {
		if (Funciones::cadenas_iguales(usuario_archivo[0], usuario)) {
            Funciones::mostrar_mensaje("El usuario ya existe", TipoMensaje::Error);
            return;
        }
    }
    
	do {
		clave = Funciones::leer_password("Ingrese la contrasenia: ");
		clave2 = Funciones::leer_password("Repita la contrasenia: ");

        if (clave != clave2) {
            Funciones::mostrar_mensaje("Las contrasenias no coinciden", TipoMensaje::Error);
        }
    } while (clave != clave2);

    archivo << usuario << "," << md5->getHashFromString(clave) << std::endl;
	archivo.close();
    
	std::cout << "\nRegistro exitoso\n";
}
