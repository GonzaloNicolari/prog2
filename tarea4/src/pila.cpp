/* 46450368			- 48579580 */
// Nicolás Saliba	- Gonzalo Nicolari.
// Instituto de Computación - Facultad de Ingeniería, Laboratorio de Programación 2.

#include "../include/pila.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>

struct rep_pila {
	int *array;
	int tope;
	int tamanio;
};

/*
  Devuelve una pila_t vacía (sin elementos) que puede tener hasta `tamanio' elementos.
 */
pila_t crear_pila(int tamanio) {
	rep_pila *pila	= new rep_pila;
	pila -> tamanio	= tamanio;
	pila -> tope	= 0;
	pila -> array	= new int[tamanio];
	return pila;
}



/*
  Apila `num' en `p'.
  Si es_llena_pila(p) no hace nada.
 */
void apilar(int num, pila_t &p) {
	if (!es_llena_pila(p)) {
		p->array [p->tope] = num;
		p->tope++;
	}
}


/*
  Remueve de `p' el elemento que está en la cima.
  Si es_vacia_pila(p) no hace nada.
 */
void desapilar(pila_t &p) {
	if (!es_vacia_pila(p)) {
		p -> array[p->tope] = 0;
		p -> tope--;
	}
}

/* Libera la memoria asignada a `p'. */
void liberar_pila(pila_t &p) {
	delete[] p -> array;
	delete p;
}

/* Devuelve `true' si y sólo si `p' es vacía (no tiene elementos). */
bool es_vacia_pila(pila_t p) { return p -> tope == 0; }

/*
  Devuelve `true' si y sólo si la cantidad de elementos en `p' es `tamanio'
  (siendo `tamanio' el valor del parámetro con que fue creada `p').
 */
bool es_llena_pila(pila_t p) { return p -> tope == p -> tamanio; }


/*
  Devuelve el elemento que está en la cima de `p'.
  Precondición: ! es_vacia_pila(p);
 */
int cima(pila_t p) { return (p -> array[p -> tope - 1]); }
