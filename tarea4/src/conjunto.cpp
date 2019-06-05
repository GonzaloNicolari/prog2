/* 46450368			- 48579580 */
// Nicolás Saliba	- Gonzalo Nicolari.
// Instituto de Computación - Facultad de Ingeniería, Laboratorio de Programación 2.

#include "../include/avl.h"
#include "../include/info.h"
#include "../include/iterador.h"
#include "../include/conjunto.h"

#include <stdlib.h>
#include <limits.h>

struct rep_conjunto { avl_t arbol; };

/* Constructoras */

/*
  Devuelve un conjunto_t vacío (sin elementos).
  El tiempo de ejecución es O(1).
 */
conjunto_t crear_conjunto() { return NULL; }

/*
  Devuelve un conjunto_t cuyo único elemento es `i'.
  El tiempo de ejecución es O(1).
 */
conjunto_t singleton(info_t i) {
	conjunto_t c = new rep_conjunto();
	if (i != NULL && es_valida_info(i)) insertar_en_avl(i, c->arbol);
	return c;
}

/*
  Devuelve un conjunto_t con los elementos que pertenecen a `c1' o `c2'.
  Si en ambos conjuntos hay un elemento con el mismo dato  numérico en el conjunto_t devuelto se debe incluir el que pertenece a `c1'.
  El tiempo de ejecucion es O(n1 + n2 + n.log n), siendo `n1' y `n2' la cantidad de elementos de `c1' y `c2' respectivamente y `n' la del conjunto_t resultado.
  El conjunto_t devuelto no comparte memoria ni con `c1' no con `c2'.
 */
conjunto_t union_conjunto(conjunto_t c1, conjunto_t c2) {
	conjunto_t c = new rep_conjunto();
	if (c1 != NULL) {
		iterador_t it1 = iterador_conjunto(c1);
		reiniciar_iterador(it1);
		while (esta_definida_actual(it1)) {
			insertar_en_avl(copia_info(actual_en_iterador(it1)), c->arbol);
			avanzar_iterador(it1);
		}
		liberar_iterador(it1);
	}
	if (c2 != NULL) {
		iterador_t it2 = iterador_conjunto(c2);
		reiniciar_iterador(it2);
		while (esta_definida_actual(it2)) {
			if (buscar_en_avl(numero_info(actual_en_iterador(it2)), c->arbol) == NULL) insertar_en_avl(copia_info(actual_en_iterador(it2)), c->arbol);
			avanzar_iterador(it2);
		}
		liberar_iterador(it2);
	}
	return c;
}

/*
  Devuelve un conjunto_t con los elementos de `c1' cuyos datos numéricos no pertenecen a `c2'.
  El tiempo de ejecucion es O(n1 + n2 + n.log n), siendo `n1' y `n2' la cantidad de elementos de `c1' y `c2' respectivamente y `n' la del conjunto_t resultado.
  El conjunto_t devuelto no comparte memoria ni con `c1' no con `c2'.
 */
conjunto_t diferencia(conjunto_t c1, conjunto_t c2) {
	conjunto_t c = new rep_conjunto();
	if (c1 != NULL) {
		iterador_t it = iterador_conjunto(c1);
		reiniciar_iterador(it);
		if (c2 != NULL) {
			while (esta_definida_actual(it)) {
				if (buscar_en_avl(numero_info(actual_en_iterador(it)), c2->arbol) == NULL) insertar_en_avl(copia_info(actual_en_iterador(it)), c->arbol);
				avanzar_iterador(it);
			}
		} else {
			while (esta_definida_actual(it)) {
				insertar_en_avl(copia_info(actual_en_iterador(it)), c->arbol);
				avanzar_iterador(it);
			}
		}
		liberar_iterador(it);
	}
	return c;
}

/*
  Libera la memoria asignada a `c' y la de todos sus elementos.
  El tiempo de ejecución es O(n), siendo `n' la cantidad de elementos de `c'.
 */
void liberar_conjunto(conjunto_t &c) {
	if (!es_vacio_conjunto(c)) {
		liberar_avl(c->arbol);
		delete c;
	}
}

/*
  Devuelve `true' si y sólo si `info' es un elemento de `c'.
  El tiempo de ejecución es O(log n), siendo `n' es la cantidad de elementos de `c'.
 */
bool pertenece_conjunto(info_t info, conjunto_t s) {
	if (s == NULL) return false;
	avl_t a = buscar_en_avl(numero_info(info), s->arbol);
	return (es_vacio_avl(a)) ? false : son_iguales(info, raiz_avl(a)) ;
}

/*
  Devuelve `true' si y sólo `c' es vacío (no tiene elementos).
  El tiempo de ejecución es O(1).
 */
bool es_vacio_conjunto(conjunto_t c) { return c == NULL; }

/*
  Devuelve un conjunto_t con los `n' elementos que están en en el rango [0 .. n - 1] del arreglo `infos'.
  Los elementos están ordenados de manera creciente estricto (creciente y sin repetidos) según los datos numércos.
  El tiempo de ejecución es O(n).
 */
conjunto_t arreglo_a_conjunto(info_t *infos, nat n) {
	conjunto_t c = new rep_conjunto();
	for (nat i = 0; i < n; i++)
		if (es_valida_info(infos[i])) insertar_en_avl(infos[i], c->arbol);
	return c;
}

/*
  Devuelve un iterador_t de los elementos de `c'.
  En la recorrida del iterador devuelto los datos numéricos aparecerán en orden creciente.
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
