/* 46450368			- 48579580 */
// Nicol�s Saliba	- Gonzalo Nicolari.
// Instituto de Computaci�n - Facultad de Ingenier�a, Laboratorio de Programaci�n 2.

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

binario_t insertar_en_binario(info_t i, binario_t b){

	if(es_vacio_binario(b)){
		b = new rep_binario;
		b -> dato -> frase = i -> frase;
		return b;
	}else{
		if (b -> dato -> frase < numero_info(i)){
			
			insertar_en_binario(i,derecho(b));
		}else if (b -> dato -> frase > numero_info(i)){
			insertar_en_binario(i,izquierdo(b));
        }
	}
	return b;
}

info_t mayor(binario_t b){
	if (derecho(b) != NULL){
		mayor(b);
	}else{
		return (b -> dato);
	}
}

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


/*
  Remueve de `b' el nodo en el que el dato de texto de su elemento es `t'.
  Si los dos subárboles del nodo a remover son no vacíos, en sustitución del
  elemento removido debe quedar el que es el mayor (segun la propiedad de orden
  definida) en el subárbol izquierdo.
  Devuelve `b'.
  Precondición: !es_vacio_binario(buscar_subarbol(frase_info(i), b).
  Libera la memoria del nodo y del elemento.
  El tiempo de ejecución es O(log n) en promedio, donde `n' es la cantidad de
  elementos de `b'.
 */
binario_t remover_de_binario(const char *t, binario_t b){
	if(t < frase_info(b -> dato)){
		remover_de_binario (t, izquierdo(b));
	}else if (t > frase_info(b -> dato)){
		remover_de_binario (t, derecho(b));
	}else if (t == frase_info(b -> dato)){

			//A COMPLETAR BORRAR NODO
			
	}
}

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


bool es_vacio_binario(binario_t b) { return b == NULL; }




info_t raiz(binario_t b) {return (b -> dato);}


binario_t izquierdo(binario_t b) {return (b -> izq);}

binario_t derecho(binario_t b) {return (b -> der);}

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
o
nat altura_binario(binario_t b){
	if (es_vacio_binario(b)) return 0;
	else{
		return 1+maximo(altura_binario(izquierdo(b)), altura_binario(derecho(b)));
	}
}


static int absoluto(int n) { return (n >= 0) ? (n) : (-n); }

static int maximo(nat n1, nat n2) { return (n1 >= n2) ? (n1) : (n2); }


void imprimir_binario(binario_t b){
	if (b != NULL) {
		imprimir_binario(derecho(b));
		printf(info_a_texto(b -> dato));
		imprimir_binario(izquierdo(b));
	};
};
