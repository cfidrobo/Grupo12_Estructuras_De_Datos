/*      UNIVERSIDAD DE LAS FUERZAS ARMADAS
*       SobrecargaComa - Sobrecarga del operador ","
*       Autor: Limones G. John J. - Cristian Idrobo
*       Fecha de creación: 15/05/2022
*       Fecha de modificación: --/--/----
*       Grupo: 12
*       Github: https://github.com/cfidrobo/Grupo12_Estructuras_De_Datos.git
*/
#include <iostream>
#include "Coma.h"
using namespace std;

	int main(){
	    coma obj1(10, 20), obj2(5, 30), obj3(2, 1);
	    
	  //Salida sin operador ,
	  cout<<"Salida sin el operador ','"<<endl;
	    obj1.salida();
	    obj2.salida();
	    obj3.salida();
	    cout << endl;
	    
	  //Salida con operador ,
	  cout<<"Salida con el operador ','"<<endl;
	    obj1 = (obj1 , obj2+obj2, obj3);
	  //Ultima salida de objeto 1
	  cout<<"Ultima salida de objeto 1"<<endl;
	    obj1.salida();
	  
	    return 0;
	}
