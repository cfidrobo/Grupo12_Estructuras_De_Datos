/*      UNIVERSIDAD DE LAS FUERZAS ARMADAS
*       Aplicativo Recursividad
*       Autor: Limones G. John J. - Cristian Idrobo
*       Fecha de creación: 16/05/2022
*       Fecha de modificación: --/--/----
*       Grupo: 12
*       Github: https://github.com/cfidrobo/Grupo12_Estructuras_De_Datos
*/

#include <iostream>
#include "Lista.h"
#include "Nodo.h"
using namespace std;
int main()
{
	Lista lst;
	lst.ingreso();
	lst.mostrar();
	lst.buscar();
	printf_s("\n");
	lst.eliminar();
	lst.mostrar();
	lst.sumaLista();
	return 0;
}
