#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>
#include "inpos.h"
#define tam 20

int main()
{
	inpos ip;
 	 
	int opcion;
	
	do{
		system("cls");
	 	printf("\n --------------------------------------------------");
		printf("\n         	Menu de Opciones           ");
		printf("\n  1.-->Convertir una Expresion de Infija a Postfija");
		printf("\n  2.-->Convertir una Expresion de Infija a Prefija");
		printf("\n  3.-->Salir del Menu");
		printf("\n --------------------------------------------------");
		printf("\n Ingrese su opcion: ");
		scanf("%d",&opcion);
		switch(opcion)
 		{
		case 1:
			ip.Posfija();
  			
    	
    	
		break;
	
		case 2:
			ip.Prefija();
    	
    	
		break;
	
		case 3:
		break;
	
		default: printf("\n Por favor seleccione una opcion valida...");
		getch();
		break;
		}
	
	}while(opcion!=3);
	getch();
}




