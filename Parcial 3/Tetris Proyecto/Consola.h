#pragma once
#include <windows.h>
#include <iostream>

void ajustarConsola() {
	system("mode 650");
	ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);
}

void ajustarFuente(int tamano) {
	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;
	cfi.dwFontSize.X = 0;
	cfi.dwFontSize.Y = tamano;
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_NORMAL;
	std::wcscpy(cfi.FaceName, L"Consolas");
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
}

void sacarTamano(int& columns, int& rows) {
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	columns = csbi.dwMaximumWindowSize.X;;
	rows = csbi.dwMaximumWindowSize.Y;
}