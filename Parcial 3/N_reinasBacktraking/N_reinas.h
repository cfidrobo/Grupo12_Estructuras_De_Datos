#include <windows.h>
#pragma execution_character_set("utf-8")

using namespace std;
int x = 0;
int k = 0;
//Aca comprobamos si la reina esta colocado en una posicion valida
//para que la posicion sea valida las reinas no deben en la misma columna
//y tampoco pueden estar en la misma fila, ni diagonal

bool comprobar(int reinas[], int n, int k) {
	int i;
	for (i = 0; i < k; i++) {
		if ((reinas[i] == reinas[k]) or (abs(k - i) == abs(reinas[k] - reinas[i]))) {
			return false;
		}
	}
	return true;
}

void Nreinas(int reinas[], int n, int k) {
	//este es el caso base que me indica que se ha encontrado una solucion
	//por lo cual ya no hay mas reinas por colocar.Hemos logrado poner
	//todas las reinas en el tablero deajerdrez
	if (k == n) {
		//print(reinas,n);
		x++;
		cout << "Solucion " << x << " :\n";
		for (int i = 0; i < n; i++) {
			cout << reinas[i]+1 << " , ";
		}
		cout << endl;

	}
	//aun quedan reinas por colocar y el algoritmo debe seguir buscando
	else {
		for (reinas[k] = 0; reinas[k] < n; reinas[k]++) {
			if (comprobar(reinas, n, k)) {
				Nreinas(reinas, n, k + 1);
			}
		}
	}
}

//Una reina es segura si no hay una reina horizontal, vertical y diagonal en ambos lados de los elementos.
bool AsegurarReina(int tablero[][10], int fil, int col, int cant) {
    //almacenar la posición en xey como referencia; 
    int x = fil;
    int y = col;
    //comprobando diogonal izquierda
    while (x >= 0 && y >= 0) {
        if (tablero[x][y] == 1) {
            //si alguna reina ya está presente en esa diagonal, no podemos colocar la reina
            return false;
        }
        //cordinadas podemos obtener de fila restando 1 y de columna restando 1;
        x--;
        y--;
    }
    //Nuevamente almacenando la posición en x e y como referencia
    x = fil;
    y = col;
    //comprobando la diagonal derecha
    while (x >= 0 && y < cant) {
        if (tablero[x][y] == 1) {
            //si alguna reina ya está presente en esa diagonal, no podemos colocar la reina
            return false;
        }
        //coordenadas podemos obtener de fila reduciendo 1 y de columna aumentando 1;
        x--;
        y++;
    }
    //Por fin comprobando verticalmente, si hay alguna reina o no.
    //solo verificando hasta la fila (no n) porque estamos colocando la fila de la reina sabiamente, por lo que no hay posibilidad de que haya una reina después de que la fila pase en función
    for (int i = 0; i < fil; i++)
    {
        if (tablero[i][col] == 1) {
            // si la reina está presente verticalmente, entonces la reina no se puede colocar y devolver falso
            return false;
        }
    }
    //si hasta ahora no se ha encontrado ningún falso, entonces se puede colocar la reina, así que devuelva verdadero
    return true;
}
//este es un enfoque recursivo usando backtracking
bool backtrackingRecursividad(int tablero[][10], int fil, int cant) {
    //condición base para la recusación (cuando se hayan llenado todas las filas, la fila será n)
    if (fil == cant) {
        //ya que todas las reinas han sido colocadas
        //imprimir la solución
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                //si el tablero de ajedrez[i][j]==1 entonces la reina está presente
                if (tablero[i][j] == 1) {
                    // imprimir ╬
                    system("color DB"); 
                    cout << "♣ ";
                }
                else {
                    //si el tablero de ajedrez[i][j] es igual a cero
                    // eso significa que la reina no está presente aquí
                    // impromir ■
                    cout << "■ ";
                }
            }
            cout << endl;
        }
        cout << endl;

        // devolver falso imprimirá todas las soluciones posibles
        return false;
    }
    //retroceder y colocar reinas

    for (int j = 0; j < cant; j++) {
        //verificar si una reina puede colocarse en esa fila o columna en particular o no
        if (AsegurarReina(tablero, fil, j, cant)) {
            //ya que es seguro
            //coloca la reina, es decir, pon 1 en ese lugar
            tablero[fil][j] = 1;
            //verificar si la próxima reina podemos colocarla o no en la siguiente fila
            bool nextQueen = backtrackingRecursividad(tablero, fil + 1, cant);
            // si somos capaces de colocar entonces continuamos colocando reinas
            if (nextQueen) {
                return true;
            }
            // si la próxima reina no se puede colocar en ninguna columna, entonces eliminamos la reina que hemos colocado anteriormente e intentamos colocarla en una columna diferente de esta fila
            tablero[fil][j] = 0;
        }
    }
    // si el control viene aquí, eso significa que no podemos colocar toda la reina
    // Así que devuelve falso
    return false;

}