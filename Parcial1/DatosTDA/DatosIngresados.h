#pragma once
#include <string>

class LeerDatos
{
public:
    virtual string leerCadenaNumerica(const string mensaje) = 0;
};

class DatosIngresados : public LeerDatos {
public:
    virtual string leerCadenaNumerica(const string mensaje);
};