/* 46450368			- 48579580 */
// Nicolás Saliba	- Gonzalo Nicolari.
// Instituto de Computación - Facultad de Ingeniería, Laboratorio de Programación 2.

#include "../include/avl.h"
#include "../include/info.h"
#include "../include/cola_avls.h"

#include <stdlib.h>

struct rep_cola_avls {
	avl_t arbol;
	cola_avls_t *siguiente;
};

/*  Devuelve una cola_avls_t vacía (sin elementos). */
cola_avls_t crear_cola_avls() {
	cola_avls_t cola	= new rep_cola_avls;
	cola->arbol			= NULL;
	cola->siguiente		= NULL;
	return cola;
}

/* Encola `avl' en `c'. */
void encolar(avl_t b, cola_avls_t &c) {
	if (!es_vacio_avl(b)) {
		if (!es_vacia_cola_avls(c)) encolar(b, c->siguiente->arbol);
		else {
			cola_avls_t cavl	= crear_cola_avls();
			cavl->arbol			= b;
		}
	}
}
/*
void encolar(avl_t b, cola_avls_t &c) {
	if (es_vacia_cola_avls(c->siguiente)) c->siguiente->arbol = b;
	else encolar(b, siguienteEnCola(c));
}
*/

/*
  Remueve de `c' el elemento que está en el frente.
  NO libera la memoria del elemento removido.
  Si es_vacia_cola_binarios(c) no hace nada.
 */
void desencolar(cola_avls_t &c) { c = c->siguiente; }

/* Libera la memoria asignada a `c', pero NO la de sus elementos. */
void liberar_cola_avls(cola_avls_t &c) {
	cola_avls_t *a_borrar;
	while (c->arbol != NULL) {
		a_borrar	= c;
		c			= c->siguiente;
		delete(a_borrar);
	}
	delete c;
}

/* Devuelve `true' si y sólo si `c' es vacía (no tiene elementos). */
bool es_vacia_cola_avls(cola_avls_t c) { return c == NULL; }

/*
  Devuelve el elemento que está en el frente de `c'.
  Precondición: ! es_vacia_cola_binarios(c);
 */
avl_t frente(cola_avls_t c) { return c->arbol; }
