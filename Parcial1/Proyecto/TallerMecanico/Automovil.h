#pragma once
#include <string>

class Automovil {
public:
	Automovil() = default;
    Automovil(std::string marca, std::string modelo, std::string color, std::string placa) {
        this->marca = marca;
        this->modelo = modelo;
        this->color = color;
        this->placa = placa;
    }

    std::string getMarca() {
        return marca;
    }

    std::string getModelo() {
        return modelo;
    }

    std::string getColor() {
        return color;
    }

    std::string getPlaca() {
        return placa;
    }
    
    void setMarca(std::string marca) {
        this->marca = marca;
    }

    void setModelo(std::string modelo) {
        this->modelo = modelo;
    }

    void setColor(std::string color) {
        this->color = color;
    }

    void setPlaca(std::string placa) {
        this->placa = placa;
    }

    std::string toString() {
        return marca + "," + modelo + "," + color + "," + placa;
    }

private:
    std::string marca;
	std::string modelo;
	std::string color;
	std::string placa;
};
