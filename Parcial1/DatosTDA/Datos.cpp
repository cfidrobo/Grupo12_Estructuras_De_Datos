#define _CRT_SECURE_NO_WARNINGS 1

#include "Conversion.h"
#include "DatosIngresados.h"
#include <iostream>
#include <conio.h>
#include <algorithm>
#include <stdexcept>
#include <exception>


double ConversorDatos::convertirEnReal(string cadena)
{
    double exp = 0, fact = 1;
    

    if (cadena.at(0) == '-') {
        fact = -1;
        cadena = cadena.substr(1, cadena.length() - 1);
    }

    bool punto = false;
    int indice = 0;

    for (const char c : cadena) {
        int ascii = (int)c;

        if (c == '.' || c == ',') {
            if (punto || (!punto && indice == 0)) {
                cout << "\nnumero real incorrecto";
            }

            punto = true;
            indice++;
            continue;
        }

        if (!isdigit(c)) {
            throw runtime_error("\nnumero real incorrecto");
        }

        int d = c - '0';

        if (d >= 0 && d <= 9) {
            if (punto) fact /= 10.0f;
            exp = exp * 10.0f + static_cast<double>(d);
        }

        indice++;
    }

    double resultado = exp * fact;

    return resultado;
}

int ConversorDatos::convertirEnEntero(string cadena)
{
    int numero = 0;
    int multiplo = 1;
    string cadenaReversa = cadena;

    if (cadena.find(".") != string::npos) {
        cadenaReversa = cadena.substr(0, cadena.find("."));
    }

    reverse(cadenaReversa.begin(), cadenaReversa.end());

    for (const char c : cadenaReversa) {
        if (c == '.') {
            break;
        }

        if ((c < '0' || c > '9') && c != '-') {
            if (numero)
                break;
            else
                continue;
        }

        if (c == '-') {
            if (numero) {
                numero = -numero;
                break;
            }
        }
        else {
            numero += (c - '0') * multiplo;
            multiplo *= 10;
        }
    }

    return numero;
}

    string DatosIngresados::leerCadenaNumerica(const string mensaje) {
    string resultado;
    int longitud = 0;

    cout << mensaje;

    while (true) {
        int ascii = _getch();

        if (ascii == 0) {
            ascii = _getch();
        }

        if (ascii == 8) {
            if (longitud == 0) {
                continue;
            }

            cout << "\b \b";
            resultado.pop_back();
            longitud--;
            continue;
        }
        else if (ascii == 13) {
            if (resultado.at(resultado.length() - 1) == '.') {
                continue;
            }

            break;
        }

        if ((ascii >= 48 && ascii <= 57) || ascii == 45 || ascii == 46 ) {
            /*if (ascii == 46 && resultado.find(".") != string::npos) {
                continue;
            }*/

            if (ascii == 46 && longitud == 0) {
                continue;
            }

            if (ascii == 45 && longitud != 0) {
                continue;
            }

            resultado.push_back(static_cast<char>(ascii));
            longitud++;
            cout << static_cast<char>(ascii);
        }
    }

    return resultado;
}