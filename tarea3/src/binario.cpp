/* 46450368			- 48579580 */
// Nicolás Saliba	- Gonzalo Nicolari.
// Instituto de Computación - Facultad de Ingeniería, Laboratorio de Programación 2.

#include "../include/binario.h"
#include "../include/cadena.h"
#include "../include/info.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct rep_binario {
	info_t dato;
	rep_binario *izq;
	rep_binario *der;
};

binario_t crear_binario() { return NULL; }

binario_t remover_mayor(binario_t b) {

	assert(!es_vacio_binario(n));
	if (b->der == NULL) {
		binario_t izq = b->izq;
		delete(b);
		b = izq;
	} else
		b->der = remover_mayor(b->der);
	return b;
}

bool es_vacio_binario(binario_t b) { return b == NULL; }

binario_t liberar_binario(binario_t b) {

	if (b != NULL) {
		b->izq	= liberar_binario(b->izq);
		b->der	= liberar_binario(b->der);
		liberar_info(b->dato);
		delete b;
		b = NULL;
	}
	return b;
}

static int absoluto(int n) { return (n >= 0) ? (n) : (-n); }

static int maximo(nat n1, nat n2) { return (n1 >= n2) ? (n1) : (n2); }

binario_t buscar_subarbol(const char *t, binario_t b) {

	binario_t res;
	if (es_vacio_binario(b)) res = crear_binario();
	else {
		int comp = strcmp(t, frase_info(raiz(b)));
		if (comp < 0) res = buscar_subarbol(t, izquierdo(b));
		else if (comp > 0) res = buscar_subarbol(t, derecho(b));
		else res = b;
	}
	return res;
}