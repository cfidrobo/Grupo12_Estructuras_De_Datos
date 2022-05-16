#include<iostream>
#include<stdlib.h>
#include<string>
using namespace std;
//Implementacion de la clase Delete
class estudiante {
	private: 
	string nombre;
	int edad;
	public:
		estudiante();
		estudiante(string nombre, int edad);
		
	void salida();
    void *operator new (size_t size);
 
    void operator delete(void * p);
};
