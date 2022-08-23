#pragma once
#include <string>

class Persona {
public:
	Persona() = default;
	Persona(std::string cedula, std::string nombres, std::string apellidos, std::string email) {
		this->cedula = cedula;
		this->nombres = nombres;
		this->apellidos = apellidos;
		this->email = email;
	}

	std::string get_cedula() { return cedula; }
	void set_cedula(std::string cedula) { this->cedula = cedula; }

	std::string get_nombres() { return nombres; }
	void set_nombres(std::string nombres) { this->nombres = nombres; }

	std::string get_apellidos() { return apellidos; }
	void set_apellidos(std::string apellidos) { this->apellidos = apellidos; }

	std::string get_email() { return email; }
	void set_email(std::string email) { this->email = email; }

private:
	std::string cedula;
	std::string nombres;
	std::string apellidos;
	std::string email;
};
