#pragma once
#include <string>
#include "Automovil.h"

class Cliente {
public:
	Cliente() = default;
    
	Cliente(std::string cedula, std::string nombres, std::string apellidos, std::string email) {
		this->cedula = cedula;
		this->nombres = nombres;
		this->apellidos = apellidos;
		this->email = email;
	}

    Cliente(std::string cedula, std::string nombres, std::string apellidos, std::string email, Automovil automovil) {
        this->cedula = cedula;
        this->nombres = nombres;
        this->apellidos = apellidos;
        this->email = email;
        this->automovil = automovil;
    }
    
    std::string getCedula() {
        return cedula;
    }
    
    std::string getNombres() {
        return nombres;
    }

    std::string getApellidos() {
        return apellidos;
    }
    
    std::string getEmail() {
        return email;
    }
    
    Automovil getAutomovil() {
        return automovil;
    }
    
    void setCedula(std::string cedula) {
        this->cedula = cedula;
    }

    void setNombres(std::string nombres) {
        this->nombres = nombres;
    }

    void setApellidos(std::string apellidos) {
        this->apellidos = apellidos;
    }
    
    void setEmail(std::string email) {
        this->email = email;
    }

    void setAutomovil(Automovil automovil) {
        this->automovil = automovil;
    }

    std::string toString() {
		return cedula + "," + nombres + "," + apellidos + "," + email + "," + automovil.getPlaca();
    }

private:
	std::string cedula;
	std::string nombres;
	std::string apellidos;
	std::string email;
	Automovil automovil;
};
