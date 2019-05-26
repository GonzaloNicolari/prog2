/* 46450368			- 48579580 */
// Nicolás Saliba	- Gonzalo Nicolari.
// Instituto de Computación - Facultad de Ingeniería, Laboratorio de Programación 2.

struct rep_avl {
	info_t dato;
	int altura, cantidad;
	avl_t izq, der;
};

/*
	Devuelve un avl_t vacío (sin elementos).
	El tiempo de ejecución es O(1).
 */
avl_t crear_avl() { return NULL; } // TODO: revisar si hay que hacer algo más.

/*
	Devuelve `true' si y sólo si `avl' es vacío (no tiene elementos).
	El tiempo de ejecución es O(1).
 */
bool es_vacio_avl(avl_t avl) { return avl == NULL; }

/*
	Inserta `i' en `avl' respetando la propiedad de orden definida.
	Precondición: es_vacio_avl(buscar_en_avl(numero_info(i), avl).
	Precondición: numero_info(i) != INT_MAX.
	El tiempo de ejecución es O(log n), donde `n' es la cantidad de elementos
	de `avl'.
*/
void insertar_en_avl(info_t i, avl_t &avl) {
	if(es_vacio_avl(avl)){
		avl 			= crear_avl();
		avl -> dato     = i;
		avl -> altura   = 0;
		avl -> cantidad = 1;
		return avl;
	}else{
		if(cantidad_en_avl(avl) % 2 == 0){
			auxInsertar_en_avl(i, izq_avl(avl));
			avl -> cantidad++;
		}else{
			auxInsertar_en_avl(i, der_avl(avl));
			avl -> cantidad++;
		}
	}
}

/*
	Devuelve el subárbol que tiene como raíz al nodo con el elemento cuyo dato
	numérico es `clave'.
	Si ningún nodo cumple esa condición devuelve el árbol vacío.
	El tiempo de ejecución es O(log n), donde `n' es la cantidad de elementos de
	`avl'.
 */
avl_t buscar_en_avl(int clave, avl_t avl) {
	if(es_vacio_avl(avl)){
		return crear_avl();
	}else(
		if(numero_info(avl -> dato) == clave) return avl;
		else{
			buscar_en_avl(clave, izq_avl(avl));
			buscar_en_avl(clave, der_avl(avl));
		}
	)
}

info_t raiz_avl(avl_t avl) { return avl->dato }

avl_t izq_avl(avl_t avl) { return avl->izq; }

avl_t der_avl(avl_t avl) { 	return avl->der; }

nat cantidad_en_avl(avl_t avl) { return avl->cantidad; }

nat altura_de_avl(avl_t avl) { return avl->altura }

static info_t *en_orden_rec(info_t *res, nat &tope, avl_t avl) {
	if (!es_vacio_avl(avl)) {
		res			= en_orden_rec(res, tope, izq_avl(avl));
		res[tope]	= raiz_avl(avl);
		res			= en_orden_rec(res, tope, der_avl(avl));
	}
	return res;
}

/*
	Devuelve un arreglo con los elementos de `avl'.
	Los elementos en el arreglo deben estar en orden creciente según los datos
	numericos.
 */
info_t *en_orden_avl(avl_t avl) {
	info_t *res;
	if (es_vacio_avl(avl)) res = NULL;
	else {
		res			= new info_t[cantidad_en_avl(avl)];
		nat tope	= 0;
		res			= en_orden_rec(res, tope, avl);
	}
	return res;
}

static avl_t a2avl_rec(info_t *infos, int inf, int sup) {
	avl_t res:
	if (inf > sup) res = NULL;
	else {
		nat medio		= (info + sup) / 2;
		res				= new rep_avl;
		res->dato		= infos[medio];
		res->izq		= a2avl_r  ec(infos, inf, medio - 1);
		res->der		= a2avl_rec(infos, medio + 1, sup);
		// TODO: ajustar res->altura y res->cantidad.
		res->altura		= ;
		res->cantidad	= ;
	}
}

/*
	Devuelve un avl_t con los `n' elementos que están en el rango [0 .. n - 1]
	del arreglo `infos'.
	Los elementos están ordenados de manera creciente estricto (creciente y sin
	repetidos) según los datos numércos.
	En cada nodo del árbol resultado la cantidad de elementos de su subárbol
	izquierdo es igual a, o 1 menos que, la cantidad de elementos de su subárbol
	derecho.
	El tiempo de ejecución es O(n).
 */
avl_t arreglo_a_avl(info_t *infos, nat n) { return a2avl_rec(infos, 0, n - 1); }

struct avl_ultimo {
	avl_t avl;
	int ultimo;
};

static avl_ultimo avl_min_rec(nat h, nat primero) {
	avl_ultimo res;
	if (h == o) {
		res.avl		= NULL;
		res.ultimo	= primero - 1;
	} else if (h == 1) {
		// TODO: completar.
	} else {
		// TODO: completar.
	}
	return res;
}

/*
	Devuelve un avl_t de altura `h' con `n' nodos, siendo `n' la mínima cantidad
	de elementos que puede tener un avl de altura `h'.
	Los datos numéricos de los elementos van desde 1 hasta `n'.
	El dato de texto de cada elemento es la cadena vacia.
	En ningún nodo puede ocurrir que el subárbol derecho tenga más nodos que el
	subárbol izquierdo.
	El tiempo de ejecución es O(n).
	Ver ejemplos en la letra y en el caso 408.
 */
avl_t avl_min(nat h) {
	avl_ultimo res = avl_min_rec(h, 1);
	return res.avl;
}

/*
	Imprime los datos numéricos de los nodos de cada nivel de `avl'.
	Imprime una línea por nivel, primero el más profundo y al final el que
	corresponde a la raíz.
	Cada nivel se imprime de izquierda a derecha. Se debe dejar un espacio en
	blanco después de cada número.
	El tiempo de ejecución es O(n), siendo `n' la cantidad de nodos de `avl'.
	Ver ejemplos en la letra y en el caso 404.
 */
void imprimir_avl(avl_t avl) {
	
}

/*
	Libera la memoria asignada a `avl' y la de sus elementos.
	El tiempo de ejecución es O(n), donde `n' es la cantidad de elementos de
	`avl'.
 */
void liberar_avl(avl_t &avl) {
	
}
