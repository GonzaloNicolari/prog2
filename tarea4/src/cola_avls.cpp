/* 46450368			- 48579580 */
// Nicolás Saliba	- Gonzalo Nicolari.
// Instituto de Computación - Facultad de Ingeniería, Laboratorio de Programación 2.

#include "../include/avl.h"
#include "../include/info.h"
#include "../include/cola_avls.h"

#include <stdlib.h>

struct nodo {
	nodo	*anterior;
	avl_t	arbol;
	nodo	*siguiente;
};

struct rep_cola_avls {
    nodo *inicio;
    nodo *final;
};


/*
struct rep_cola_avls {
	avl_t arbol;
	cola_avls_t *siguiente;
};
*/

/*  Devuelve una cola_avls_t vacía (sin elementos). */
cola_avls_t crear_cola_avls() {
	cola_avls_t c	= new rep_cola_avls;
	c->inicio		= NULL;
	c->final		= NULL;
	return c;
}

/* Encola `avl' en `c'. */
void encolar(avl_t b, cola_avls_t &c) {
	if (!es_vacio_avl(b)) {
		cola_avls_t *cavl	= new nodo;
		cavl->arbol			= b;
		cavl->siguiente		= NULL;
		cavl->anterior		= c->final;

		if (c->inicio == NULL) c->inicio = cavl;
		else c->final->siguiente = cavl;
		c->final = cavl;
	}
}
/*
void encolar(avl_t b, cola_avls_t &c) {
	if (!es_vacio_avl(b)) {
		if (!es_vacia_cola_avls(c)) encolar(b, c->siguiente->arbol);
		else {
			cola_avls_t cavl	= crear_cola_avls();
			cavl->arbol			= b;
		}
	}
}
*/

/*
  Remueve de `c' el elemento que está en el frente.
  NO libera la memoria del elemento removido.
  Si es_vacia_cola_binarios(c) no hace nada.
 */
void desencolar(cola_avls_t &c) { c->inicio = c->inicio->siguiente; }

/* Libera la memoria asignada a `c', pero NO la de sus elementos. */
void liberar_cola_avls(cola_avls_t &c) {
	cola_avls_t a_borrar;
	while (c->arbol != NULL) {
		a_borrar	= c;
		c			= c->siguiente;
		delete(a_borrar);
	}
	delete c;
}

/* Devuelve `true' si y sólo si `c' es vacía (no tiene elementos). */
bool es_vacia_cola_avls(cola_avls_t c) { return (c->inicio == NULL) && (c->final == NULL); }

/*
  Devuelve el elemento que está en el frente de `c'.
  Precondición: ! es_vacia_cola_binarios(c);
 */
avl_t frente(cola_avls_t c) { return c->arbol; }
