#define tam 20
class inpos {
	private:
		int opcion, tope=-1,pos=-1,tamexp;
		int pila[tam],epos[tam],epre[tam];
		char expinf[tam],simbolo;
	public:
		void Posfija();
		void Prefija();
		int prioridad(char simbolo);
};
