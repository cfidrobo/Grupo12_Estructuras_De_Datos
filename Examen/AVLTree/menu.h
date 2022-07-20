#pragma once
#include <string>
#include <functional>
#include <vector>

enum class Tecla : unsigned {
	Arriba = 72,
	Abajo = 80,
	Izquierda = 77,
	Derecha = 75,
	Escape = 27,
	Enter = 13,
};

inline constexpr unsigned operator+(Tecla const val) {
	return static_cast<unsigned>(val);
}

class MenuOpcion {
public:
	MenuOpcion() = default;
	MenuOpcion(
		std::string label,
		std::function<void()> action = [] {},
		bool must_wait = true,
		bool is_enabled = true);
	MenuOpcion(
		std::function<std::string()> label,
		std::function<void()> action = [] {},
		bool must_wait = true,
		bool is_enabled = true);

	MenuOpcion& enabled(bool value);
	MenuOpcion& enabled(std::function<bool()> callable);
	MenuOpcion& wait(bool value);
	MenuOpcion& wait(std::function<bool()> callable);
	MenuOpcion& action(std::function<void()> callback);

	void label(std::string label);

    std::string label();
    bool is_enabled();
	bool must_wait();
    void exec();

private:
	std::function<std::string()> label_ = [] { return "[unamed]"; };
	std::function<bool()> must_wait_ = [] { return true; };
	std::function<bool()> is_enabled_ = [] { return true; };
    std::function<void()> action_ = []{};
};

class Menu {
public:
    Menu(std::string title = "Menu");
    void agregar(MenuOpcion option);
    void iniciar();
	void detener();
	MenuOpcion opcion_salir(std::string label = "Exit");
	void al_presionar_f1(std::function<void()> callback) {
		f1callback = callback;
	}

private:
	bool running_ = false;
    std::string title_;
	std::vector<MenuOpcion> items_;
	std::function<void()> f1callback;
};
