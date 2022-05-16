#include <iostream>
#include "Coma.h"
coma coma::operator+(coma obj2){
	    coma numero;
	  
	    numero.x = obj2.x + x;
	    numero.y = obj2.y + y;
	  
	    return numero;
	}
	  
	coma coma::operator, (coma obj2){
	    coma numero;

	    numero.x = obj2.x;
	    numero.y = obj2.y;

	    cout << "x=" << obj2.x << " "
	         << "y=" << obj2.y << endl;

	    return numero;
	}
