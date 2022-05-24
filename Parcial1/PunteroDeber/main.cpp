/*      UNIVERSIDAD DE LAS FUERZAS ARMADAS
*       Puntero Escalar
*       Autor: Limones G. John J. - Cristian Idrobo
*       Fecha de creación: 20/05/2022
*       Fecha de modificación: 20/05/2022
*       Grupo: 12
*       Github: https://github.com/cfidrobo/Grupo12_Estructuras_De_Datos.git
*/
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include "Puntero.h"

int main(int argc, char** argv) {
	Puntero Obj; //Crea un objeto de la clase puntero
	int t;
	int *ptr=new int[10];
	std::cout<<"Ingrese el tamaño: "<<std::endl;
	std::cin>>t;
	Obj.ingreso(ptr,t);
	Obj.impresion(ptr,t);
	Obj.proceso(ptr,t);
	Obj.impresion(ptr,t);
	return 0;
}
