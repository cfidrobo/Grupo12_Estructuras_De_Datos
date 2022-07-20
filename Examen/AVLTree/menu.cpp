#include "menu.h"
#include "funciones.h"
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <conio.h>

MenuOpcion::MenuOpcion(
	std::string label, std::function<void()> callable, bool must_wait, bool is_enabled) {
	label_ = [label] { return label; };
	action(callable);
	wait(must_wait);
	enabled(is_enabled);
}

MenuOpcion::MenuOpcion(
	std::function<std::string()> label, std::function<void()> callable, bool must_wait, bool is_enabled) {
	label_ = label;
	action(callable);
	wait(must_wait);
	enabled(is_enabled);
}

MenuOpcion& MenuOpcion::enabled(bool value) {
	is_enabled_ = [value] { return value; };
	return *this;
}

MenuOpcion& MenuOpcion::enabled(std::function<bool()> callable) {
	is_enabled_ = callable;
	return *this;
}

MenuOpcion& MenuOpcion::action(std::function<void()> callback) {
    action_ = callback;
    return *this;
}

MenuOpcion& MenuOpcion::wait(bool value) {
	must_wait_ = [value] { return value; };
    return *this;
}

MenuOpcion& MenuOpcion::wait(std::function<bool()> callable) {
	action_ = callable;
	return *this;
}

void MenuOpcion::label(std::string label) {
	label_ = [label] { return label; };
}

std::string MenuOpcion::label() {
	return label_();
}

bool MenuOpcion::is_enabled() {
	return is_enabled_();
}

bool MenuOpcion::must_wait() {
	return must_wait_();
}

void MenuOpcion::exec() {
	if (action_ != nullptr) {
		action_();
	}
}

//////////////////////////////////////////////////////////////////

Menu::Menu(std::string title) {
	title_ = title;
}

void Menu::agregar(MenuOpcion option) {
    items_.push_back(option);
}

void Menu::iniciar() {
	int selected = 0;

	if (items_.empty()) {
		return;
	}

	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = FALSE;
	SetConsoleCursorInfo(consoleHandle, &info);

	running_ = true;
	int margen_izq = 50;

	while (running_) {
		system("cls");

		std::cout << std::endl
				  << std::endl
				  << title_ << std::endl;

		for (int i = 0; i < title_.length(); i++) {
			std::cout << "-";
		}

		std::cout << std::endl
				  << std::endl;

		int i = 0;
		for (MenuOpcion item : items_) {
			if (selected == i) {
				std::cout << "> ";
			} else {
				std::cout << "  ";
			}

			std::cout << (i + 1) << ": " << item.label() << std::endl;
			i++;
		}

		int key;

		do {
			key = _getch();

			if (key == 0) {
				key = _getch();
			}

			if (key == 59) {
				if (f1callback) {
					f1callback();
				}
			}
		} while (key != +Tecla::Abajo 
			&& key != +Tecla::Arriba
			&& key != +Tecla::Enter);

		if (key == +Tecla::Arriba) {
			selected--;
		} else if (key == +Tecla::Abajo) {
			selected++;
		}

		selected = (selected < 0 
			? 0 
			: (int)(selected >= items_.size() ? (items_.size() - 1) : selected));

		if (key == +Tecla::Enter) {
			std::cout << std::endl
					  << std::endl;

			MenuOpcion item = items_.at(selected);
			item.exec();

			if (item.must_wait()) {
				std::cout
					<< std::endl << std::endl
					<< "\n\n[presione cualquier tecla]";
				_getch();
			}
		}
	}
}

MenuOpcion Menu::opcion_salir(std::string label) {
	return MenuOpcion(label)
		.action(std::bind(&Menu::detener, this))
		.wait(false);
}

void Menu::detener() {
	running_ = false;
}
