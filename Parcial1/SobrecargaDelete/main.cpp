/*      UNIVERSIDAD DE LAS FUERZAS ARMADAS
*       SobrecargaComa - Sobrecarga del operador "delete"
*       Autor: Limones G. John J. - Cristian Idrobo
*       Fecha de creación: 15/05/2022
*       Fecha de modificación: --/--/----
*       Grupo: 12
*       Github: https://github.com/cfidrobo/Grupo12_Estructuras_De_Datos.git
*/
#include<iostream>
#include<stdlib.h>
#include "Delete.h"
using namespace std;

int main(int argc, char** argv) {
	estudiante *p=new estudiante("Carlos", 24);
	
	p->salida();
	delete p;
}
