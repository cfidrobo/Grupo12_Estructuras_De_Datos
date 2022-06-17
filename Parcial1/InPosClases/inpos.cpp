#include <iostream>
#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>
#include "inpos.h"
using namespace std;


void inpos::Posfija(){
	system("cls");
	printf("\n Ingrese la expresion en notacion Infija (sin espacios): ");
	scanf("%s",&expinf);
	

	
	tope=-1;
	pos=-1;
  	tamexp=strlen(expinf);
  	for(int i=0 ;i<tamexp; i++){
  		simbolo=expinf[i];
  		if(simbolo=='('){
  			tope=tope+1;
  			pila[tope]=simbolo;
  		}
  		else if(simbolo==')'){
  			while(pila[tope]!='('){
  				pos=pos+1;
  				epos[pos]=pila[tope];
  				tope=tope-1;
  			}
  			tope=tope-1;
  		}
  		else if((simbolo>='a')&&(simbolo<='z')||(simbolo>='A')&&(simbolo<='Z')){
  			pos=pos+1;
  			epos[pos]=simbolo; 
  		}
  		else{ 
  			while(tope>-1 && (prioridad(simbolo)<=prioridad(pila[tope]))){
  				pos=pos+1;
  				epos[pos]=pila[tope];
  				tope=tope-1;
  						
  			}
  			tope=tope+1;
  			pila[tope]=simbolo;
  				
  		}
  	}
  	while(tope>-1){
  		pos=pos+1;
  		epos[pos]=pila[tope];
  		tope=tope-1;
  	}
  	printf("\n La expresion en postfija es: ");
  	for(int i=0; i<=pos; i++){
  		printf("%c",epos[i]);
  	}
  	getch();
}

void inpos::Prefija(){
	system("cls");
			printf("\n Ingrese la expresion en notacion Infija (sin espacios): ");
			scanf("%s",&expinf);
			
			tope=-1;
  			pos=-1;
  			tamexp=strlen(expinf);
  			for(int i=tamexp-1 ;i>=0; i--){
  				simbolo=expinf[i];
  				if(simbolo==')'){
  					tope=tope+1;
  					pila[tope]=simbolo;
  				}
  				else if(simbolo=='('){
  					while(pila[tope]!=')'){
  						pos=pos+1;
  						epre[pos]=pila[tope];
  						tope=tope-1;
  					}
  					tope=tope-1;
  				}
  				else if((simbolo>='a')&&(simbolo<='z')||(simbolo>='A')&&(simbolo<='Z')){
  					pos=pos+1;
  					epre[pos]=simbolo; 
  				}
  				else{ 
  					while((prioridad(simbolo)<prioridad(pila[tope]))){
  						pos=pos+1;
  						epre[pos]=pila[tope];
  						tope=tope-1;
  						
  					}
  					tope=tope+1;
  					pila[tope]=simbolo;
  				
  				}
  			}
  			while(tope>-1){
  				pos=pos+1;
  				epre[pos]=pila[tope];
  				tope=tope-1;
  			}
  			printf("\n La expresion en prefija es: ");
  			for(int i=pos; i>=0; i--){
  				printf("%c",epre[i]);
  			}
  			getch();
	
}
int inpos::prioridad(char simbolo){
	int priori;
	switch(simbolo){
		case '^':priori =3 ; break;
		case '/':priori =2 ; break;
		case '*':priori =2 ; break;
		case '-':priori =1 ; break;
		case '+':priori =1 ; break;
		case ')':priori =0 ; break;
		case '(':priori =0 ; break;
	}
	return priori;
}
  			
	
  			
  			
  			
	
  		
