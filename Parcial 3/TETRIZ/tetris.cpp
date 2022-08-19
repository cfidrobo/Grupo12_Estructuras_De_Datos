/*      UNIVERSIDAD DE LAS FUERZAS ARMADAS
*       Laberinto - Mover en todas las direcciones.
*       Autor: Limones G. John J. - Cristian Idrobo -Santiago Chasiluisa 
*       Fecha de creación: 19/08/2022
*       Fecha de modificación: --/--/----
*       Grupo: 12
*       Github: https://github.com/cfidrobo/Grupo12_Estructuras_De_Datos.git
*/


#include <iostream>
#include "ListaDoble.h"
#include "TetrisFuncion.h"
#include "Posicion.h"

int main(int argc, char** argv) {
	int n=6;
	int m=0;
	if(n>=11){
		m=9;
	}
	else{
		m=n;
	}
	int maxh=0;
	bool escape=true;
	int cont=0;
	int maxv=0;
	maxh=3*(n-1)+8;
	maxv=(int)(1*maxh);
	Posicion *pos =new Posicion();
	ListaDoble lista = ListaDoble();
	lista.listaDobleTetris(maxh-7);
	system("color F6");
	TetrisFuncion tetris=TetrisFuncion(m+1,3);
	tetris.ocultarCursor();
	tetris.cuadro(maxv,maxh);
	do{
		if(lista.gano(n)==false){
			escape=false;
		}
		if(lista.perdio(n)==false){
			escape=false;
		}		
		tetris.imprimir(maxv,maxh,pos);
		tetris.gotoxy(3,maxv-1);
		lista.imprimirLista();
		lista.insertarEnLista(pos,pos->getNum(),maxv,maxh);
		Sleep(400);
	}while(escape);
	tetris.gotoxy(0,maxv+10);
	return 0;
}
