/* 46450368			- 48579580 */
// Nicolás Saliba	- Gonzalo Nicolari.
// Instituto de Computación - Facultad de Ingeniería, Laboratorio de Programación 2.

#include "../include/info.h"
#include "../include/iterador.h"
#include "../include/avl.h"

struct rep_conjunto { avl_t arbol; };

/* Constructoras */

/*
  Devuelve un conjunto_t vacío (sin elementos).
  El tiempo de ejecución es O(1).
 */
conjunto_t crear_conjunto() { return NULL; }
/*
conjunto_t crear_conjunto() {
	conjunto_t conjunto = new conjunto_t;
	return conjunto;
}
*/

/*
  Devuelve un conjunto_t cuyo único elemento es `i'.
  El tiempo de ejecución es O(1).
 */
conjunto_t singleton(info_t i) {
	conjunto_t c = crear_conjunto();
	insertar_en_avl(i, conjunto);
	return conjunto;
}
/*
conjunto_t singleton(info_t i){
	conjunto_t conjunto = crear_conjunto();
	insertar_en_avl(i, conjunto->arbol);	// Conjunto ya es un árbol avl, los elementos son: dato, altura, cantidad, der, izq
	return conjunto;
}
*/

/*
  Devuelve un conjunto_t con los elementos que pertenecen a  `c1' o `c2'.
  Si en ambos conjuntos hay un elemento con el mismo dato  numérico en el
  conjunto_t devuelto se debe incluir el que pertenece a `c1'.
  El tiempo de ejecucion es O(n1 + n2 + n.log n), siendo `n1' y `n2' la
  cantidad de elementos de `c1' y `c2' respectivamente y `n' la del conjunto_t
  resultado.
  El conjunto_t devuelto no comparte memoria ni con `c1' no con `c2'.
 */
static void auxUnion_Conjunto(conjunto_t &conjunto, avl_t arbol){
	if(!es_vacio_avl(izq_avl(arbol))) { 
		auxUnion_Conjunto(conjunto, izq_avl(arbol)); 
	}
	if(!es_vacio_avl(der_avl(arbol))) { 
		auxUnion_Conjunto(conjunto, der_avl(arbol)); 
	}
	insertar_en_avl(arbol -> dato, conjunto -> arbol);
}
conjunto_t union_conjunto(conjunto_t c1, conjunto_t c2){
	conjunto_t conjunto = crear_conjunto();
	auxUnion_Conjunto(conjunto, c1);
	auxUnion_Conjunto(conjunto, c2);
	return conjunto;
}

/*
  Devuelve un conjunto_t con los elementos de `c1' cuyos datos numéricos no
  pertenecen a `c2'.
  El tiempo de ejecucion es O(n1 + n2 + n.log n), siendo `n1' y `n2' la
  cantidad de elementos de `c1' y `c2' respectivamente y `n' la del conjunto_t
  resultado.
  El conjunto_t devuelto no comparte memoria ni con `c1' no con `c2'.
 */
conjunto_t diferencia(conjunto_t c1, conjunto_t c2){
	
	
	
}

/*
  Libera la memoria asignada a `c' y la de todos sus elementos.
  El tiempo de ejecución es O(n), siendo `n' la cantidad de elementos de `c'.
 */
void liberar_conjunto(conjunto_t &c);

/*
  Devuelve `true' si y sólo si `info' es un elemento de `c'.
  El tiempo de ejecución es O(log n), siendo `n' es la cantidad de
  elementos de `c'.
 */
bool pertenece_conjunto(info_t info, conjunto_t s);

/*
  Devuelve `true' si y sólo `c' es vacío (no tiene elementos).
  El tiempo de ejecución es O(1).
 */
bool es_vacio_conjunto(conjunto_t c);

/*
  Devuelve un conjunto_t con los `n' elementos que están en en el rango
  [0 .. n - 1] del arreglo `infos'.
  Los elementos están ordenados de manera creciente estricto (creciente y sin
  repetidos) según los datos numércos.
  El tiempo de ejecución es O(n).
 */
conjunto_t arreglo_a_conjunto(info_t *infos, nat n);

/*
  Devuelve un iterador_t de los elementos de `c'.
  En la recorrida del iterador devuelto los datos numéricos aparecerán en orden
  creciente.
  El tiempo de ejecución es O(n), siendo `n' es la cantidad de elementos de `c'.
  El iterador_t resultado NO comparte memoria con `c'.
 */
iterador_t iterador_conjunto(conjunto_t c) {
	iterador_t res	= crear_iterador();
	info_t *infos	= en_orden_avl(c->arbol);
	for (nat i = 0; i < cantidad_en_avl(c->arbol); i++) agregar_a_iterador(infos[i], res);
	bloquear_iterador(res);
	delete[] infos;
	return res;
}
