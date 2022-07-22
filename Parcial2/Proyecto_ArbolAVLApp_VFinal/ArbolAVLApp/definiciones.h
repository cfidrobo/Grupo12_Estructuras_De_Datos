#pragma once

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

enum class TipoMensaje {
	Error,
	Correcto,
	Informativo
};

#define for_indexed(...) for_indexed_v(i, __VA_ARGS__)
#define for_indexed_v(v, ...) \
	if (std::size_t v = -1)   \
		for (__VA_ARGS__)     \
			if ((++v, true))