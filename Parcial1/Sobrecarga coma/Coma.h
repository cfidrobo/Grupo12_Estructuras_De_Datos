#include <iostream>
using namespace std;
class coma {
    int x, y;
    
  	//Metodos
	public:
	    coma() {}//Cosntructor1 sin parametros
	  
	    coma(int X, int Y){  //Cosntructor2 con dos parametros
	        x = X;
	        y = Y;
	    }
	  
	    void salida(){
	        cout << "x=" << x << " ";
	        cout << "y=" << y << " ";
	    }
	  
	    coma operator+(coma obj2);
	    coma operator, (coma obj2);
	};
