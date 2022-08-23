#pragma once
#include "Cliente.h"

class Asistencia {
public:
	Asistencia() = default;
	Asistencia(Cliente cliente, std::string hora, std::string detalle, float valor) {
        this->cliente = cliente;
        this->hora = hora;
        this->detalle = detalle;
		this->valor = valor;
	}

    Cliente getCliente() {
        return cliente;
    }
    
    std::string getHora() {
        return hora;
    }

    std::string getDetalle() {
        return detalle;
    }

    void setCliente(Cliente cliente) {
        this->cliente = cliente;
    }

    void setHora(std::string hora) {
        this->hora = hora;
    }

    void setDetalle(std::string detalle) {
        this->detalle = detalle;
    }

    void setValor(float valor) {
		this->valor = valor;
    }

    std::string toString() {
		return cliente.getCedula() + "," + hora + "," + detalle + "," + std::to_string(valor);
    }

private:
	Cliente cliente;
    std::string hora;
	std::string detalle;
	float valor = 0;
};
