



struct rep_pila{
	int* array;
	int tope, tamanio;
}
typedef struct rep_pila * pila_t;


pila_t crear_pila(int tamanio){
	rep_pila pila   = new rep_pila;
	pila -> tamanio = tamanio;
	pila -> tope    = 0;
	pila -> array   = new int[tamanio];
	return pila;
}

void apilar (int num, pila_t &p){
	if (!es_vacia_pila(p)){
		p -> array[(p -> tope) + 1] = dato;
		p -> tope = (p -> tope) + 1;
	}	
}

void desapilar(pila_t &p){
	if (!es_vacia_pila(p){	
		p -> array[p -> tope] = NULL;
		p -> tope = (p -> tope) +1;
	}
}

void liberar_pila(pila_t &p) { delete p; }

bool es_vacia_pila(pila_t){ return pila -> tope == 0;}	

bool es_llena_pila(pila_t p){
	return ((pila->tope)+1 == pila->tamanio); 
}

int cima (pila_t p){
	return (p -> array[p -> tope]);
}
#endif