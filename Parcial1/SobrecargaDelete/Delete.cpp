#include <iostream>
#include "Delete.h"

using namespace std;
estudiante::estudiante(){
	cout<<"Se llama constructor";
	}
	estudiante::estudiante(string nombre, int edad){
		this->nombre=nombre;
		this->edad=edad;
	}
	void estudiante::salida(){
		cout<< "Nombre:" << nombre << endl;
        cout<< "Edad:" << edad << endl;
    }
    void *estudiante::operator new (size_t size){
        cout<< "Sobrecarga de operador new con tamaño: " << size << endl;
        void * p = ::operator new(size);
        return p;
    }
 
    void estudiante::operator delete(void * p){
        cout<< "Sobrecarga de operador Delete " << endl;
        free(p);
    }
	
