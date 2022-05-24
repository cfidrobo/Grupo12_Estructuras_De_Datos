#include "Puntero.h"
void Puntero::ingreso(int *p,int t){
	int i;
	for(i=0;i<t;i++){
	scanf("%d",*(&p)+i);
	}
}
void Puntero::impresion(int *p,int t){
	int i;
	printf("{ ");
	for(i=0;i<t;i++){
		printf("%d ",*(&(*p)));
		*(p++);
	}
	printf(" }");
}
void Puntero::proceso(int *p,int t){
	int i,e;
	printf("\nIngrese el escalar ");
	scanf("%d",&e);
	for(i=0;i<t;i++){
		*p=(*(&(*p)))*e;
		*(p++);
	}
}
