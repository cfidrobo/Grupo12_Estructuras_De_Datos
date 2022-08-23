#pragma once
#include <string>
#include <conio.h>
#include <pixelbmp/pixelbmp.h>

class Pixelador {
public:
	Pixelador(std::string image) : _image(image) {}
    
	void pixelar() {
		HWND console = GetConsoleWindow();
		HANDLE output = ::GetStdHandle(STD_OUTPUT_HANDLE);
		HDC dc = GetDC(console);

		CONSOLE_FONT_INFOEX Font = { sizeof(Font) };
		GetCurrentConsoleFontEx(output, FALSE, &Font);

		CONSOLE_FONT_INFOEX cfi;
		cfi.cbSize = sizeof(cfi);
		cfi.nFont = 0;
		cfi.dwFontSize.X = 1;
		cfi.dwFontSize.Y = 1;
		cfi.FontFamily = FF_DONTCARE;
		cfi.FontWeight = FW_NORMAL;
		wcscpy_s(cfi.FaceName, L"Consolas");
		SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);

		ShowWindow(console, SW_SHOWMAXIMIZED);

		// COORD pos = { 0, 15 };
		// SetConsoleCursorPosition(output, pos);

		std::cout << std::endl;
		dibujar(&dc);
		_getch();

		SetCurrentConsoleFontEx(output, FALSE, &Font);
		system("cls");
	}

	void dibujar(HDC* console) {
		BMP image;
		image.ReadFromFile(_image.c_str());

		double original_width = image.TellWidth();
		double original_height = image.TellHeight();
		double ratio = ratio = original_width / original_height;

		double max_width = 500;
		double width = original_width;
		double height = original_height;

		if (original_width > max_width) {
			height = max_width / ratio;
		}

		for (int y = 0; y < height; y++) {
			for (int x = 0; x < width; x++) {
				int r = image.GetPixel(x, y).Red;
				int g = image.GetPixel(x, y).Green;
				int b = image.GetPixel(x, y).Blue;
				int a = image.GetPixel(x, y).Alpha;
				COLORREF COLOUR = RGB(r, g, b);
                
				if (a == 0) {
					std::cout << "\033["
							  << 48
							  << ";2;"
							  << r << ";" << g << ";" << b << "m"
							  << '##'
							  << "\033[0;00m";

					if (x == width - 1) {
						std::cout << std::endl;
					}
				}
			}
		}
	}

private:
	std::string _image;
};
