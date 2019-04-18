/* 46450368			- 48579580 */
// Nicolás Saliba	- Gonzalo Nicolari.
// Instituto de Computación - Facultad de Ingeniería, Laboratorio de Programación 2.

#include "../include/binario.h"
#include "../include/cadena.h"
#include "../include/uso_cadena.h"
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

binario_t insertar_en_binario(info_t i, binario_t b) {
	if (es_vacio_binario(b)) {
		b = new rep_binario;
		b->dato = i;
		return b;
	} else {
		if (strcmp(frase_info(raiz(b)), frase_info(i)) < 0) insertar_en_binario(i, derecho(b));
		else insertar_en_binario(i, izquierdo(b));
	}
	return b;
}

info_t mayor(binario_t b) {
	if (!es_vacio_binario(derecho(b))) mayor(derecho(b));
	else mayor(izquierdo(b));
	return (raiz(b));
}

binario_t remover_mayor(binario_t b) {
	assert(!es_vacio_binario(n));
	if (derecho(b) == NULL) {
		binario_t izq = izquierdo(b);
		delete(b);
		b = izq;
	} else
		b->der = remover_mayor(derecho(b));
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

/* 
static binario_t auxRemover(const char *&t, binario_t &padre, binario_t &hijo) {
	if		(strcmp(frase_info(hijo->dato), t) < 0) return auxRemover(t, b, derecho(b));
	else if	(strcmp(frase_info(hijo->dato), t) > 0) return auxRemover(t, b, izquierdo(b));
	else {
	// Referencio al padre con el hijo borrado según si es hijo izq o der.
		if (hijo == derecho(padre))	padre->der = auxBorrar(hijo);
		else padre->izq = auxBorrar(hijo);
		return padre;
	}
}

static binario_t auxBorrar(binario_t &b, binario_t &aux) {
	// Si tiene nodo izq.
	if (!es_vacio_binario(izquierdo(b))) {
		aux			= mayor(izquierdo(b)); // aux->der == null por ser el mayor.
		aux->der	= b->der;
		liberar_info(b->dato);
		b->dato = aux->dato;
		// @NOTA: Actualmente solo se está poniendo a la derecha del hijo más grande del sub árbol izquierdo, el sub árbol derecho del nodo a borrar.
		// @TODO: Falta acomodar el lado izquierdo de aux.
		// @TODO: Volver a enganchar el padre de aux con el resto de la cadena.
		return b;
	// Si tiene nodo der.
	} else if (!es_vacio_binario(derecho(b)) {
		aux = derecho(b);
		liberar_info(b->dato);
		b->dato	= aux->dato;
		b->der	= aux->der;
		// @TODO: Falta acomodar el lado izquierdo de b (b->izq	= aux->izq;).
		return b;
	// Si no tiene izq ni der.
	} else {
		liberar_info(b->dato);
		return b;
	}
}

binario_t remover_de_binario(const char *t, binario_t b) {
	// Si la raíz es el nodo a borrar.
	if (strcmp(frase_info(b->dato), t) == 0) {
		// Si tiene nodo izq.
		if (!es_vacio_binario(izquierdo(b))) {
			// TODO: Buscar a mano el mayor y guardar la referencia al padre.
			binario_t aux	= mayor(izquierdo(b)); // aux->der == null por ser el mayor.
			aux->der		= b->der;
			liberar_info(b->dato);
			b->dato = aux->dato;
			// @NOTA: Actualmente solo se está poniendo a la derecha del hijo más grande del sub árbol izquierdo, el sub árbol derecho del nodo a borrar.
			// @TODO: Falta acomodar el lado izquierdo de aux.
			// @TODO: Volver a enganchar el padre de aux con el resto de la cadena (hijos de aux).
			// @NOTA: Actualmente al obtener aux con la función "mayor" perdemos referencia del padre del elemento que devuelve; y el cual necesito volver a enganchar.
			return b;
		// Si tiene nodo der.
		} else if (!es_vacio_binario(derecho(b)) {
			binario_t aux = derecho(b);
			liberar_info(b->dato);
			b->dato	= aux->dato;
			b->der	= aux->der;
			b->izq	= aux->izq;
			return b;
		// Si no tiene izq ni der.
		} else {
			liberar_info(b->dato);
			return b;
		}
		//b = auxBorrar(b, aux);
	// Si no es la raíz.
	} else if	(strcmp(frase_info(b->dato), t) < 0)	b = auxRemover(t, b, derecho(b));
	else if		(strcmp(frase_info(b->dato), t) > 0)	b = auxRemover(t, b, izquierdo(b));

	return b;
}
*/

binario_t remover_de_binario(const char *t, binario_t b) {

	binario_t *actual	= b;
	binario_t *padre	= crear_binario();
	binario_t *aux;

	// Busco el nodo a remover.
	while (!es_vacio_binario(actual)) {
		// Si encontré el valor.
		if (strcmp(t, frase_info(raiz(actual)) == 0) {
			// Si no tiene hijos (es una hoja).
			if (es_vacio_binario(derecho(b)) && es_vacio_binario(izquierdo(b))) {
				// Si no es la raíz.
				if (!es_vacio_binario(padre)) {
					if (derecho(padre) == actual) padre->der = NULL;
					else {
						assert(izquierdo(padre) == actual);
						padre->izq == NULL;
					}
				}
				delete actual;
				actual = NULL;
				return b;
			} else {
				// Si tiene hijos.
				padre = actual;
				// Busco el mayor en el subárbol izquierdo.
				if (!es_vacio_binario(izquierdo(actual))) {
					aux = izquierdo(actual);
					while (!es_vacio_binario(derecho(aux))) {
						padre	= aux;
						aux		= derecho(aux);
					}
				} else {
					// Busco el menor en el subárbol derecho.
					aux = derecho(actual);
					while (!es_vacio_binario(izquierdo(actual))) {
						padre	= aux;
						aux		= izquierdo(actual);
					}
				}
				int value		= raiz(actual);
				actual->dato	= raiz(aux);
				aux->dato		= value;
				actual			= aux;
			}
		} else {
			// Sigo buscando.
			padre = actual;
			if (strcmp(t, frase_info(raiz(actual)) > 0) actual = derecho(actual);
			else actual = izquierdo(actual);
		}
	}
	return b;
}

binario_t liberar_binario(binario_t b) {
	if (b != NULL) {
		b->izq	= liberar_binario(izquierdo(b));
		b->der	= liberar_binario(derecho(b));
		liberar_info(raiz(b));
		delete b;
		b = NULL;
	}
	return b;
}

bool es_vacio_binario(binario_t b) { return b == NULL; }

/* 
static bool avlAux(binario_t b, int diffL, int diffR) {
	if (izquierdo(b) =! NULL) return avlAux(izquierdo(b), diffL, diffR);
	else diffL++;
	if (derecho(b) =! NULL) return avlAux(derecho(b), diffL, diffR);
	else diffR++;
	if ((absoluto(diffL - diffR) == 0) || (absoluto(diffL - diffR) == 1)) return true;
	else return false;
}
 */
static bool avlAux(binario_t b, int diffL, int diffR) {
	if (!es_vacio_binario(izquierdo(b))) {
		diffL++;
		return avlAux(izquierdo(b), diffL, diffR);
	}
	if (!es_vacio_binario(derecho(b))) {
		diffR++;
		return avlAux(derecho(b), diffL, diffR);
	}
	return (absoluto(diffL - diffR) == 0) || (absoluto(diffL - diffR) == 1);
}

bool es_AVL(binario_t b) {
	if (es_vacio_binario(b)) return true;
	else {
		int i = 0;
		return avlAux(b, i, i);
	}
}

info_t raiz(binario_t b) { return (b->dato); }

binario_t izquierdo(binario_t b) { return (b->izq); }

binario_t derecho(binario_t b) { return (b->der); }

binario_t buscar_subarbol(const char *t, binario_t b) {
	binario_t res;
	if (es_vacio_binario(b)) res = crear_binario();
	else {
		if		(strcmp(t, frase_info(raiz(b))) < 0)	res = buscar_subarbol(t, izquierdo(b));
		else if	(strcmp(t, frase_info(raiz(b))) > 0)	res = buscar_subarbol(t, derecho(b));
		else res = b;
	}
	return res;
}

static int absoluto(int n) { return (n >= 0) ? (n) : (-n); }

static int maximo(nat n1, nat n2) { return (n1 >= n2) ? (n1) : (n2); }

nat altura_binario(binario_t b) {
	if (es_vacio_binario(b)) return 0;
	else return 1 + maximo(altura_binario(izquierdo(b)), altura_binario(derecho(b)));
}

nat cantidad_binario(binario_t b) {
	if (es_vacio_binario(b)) return 0;
	else return 1 + cantidad_binario(izquierdo(b)) + cantidad_binario(derecho(b));
}

int suma_ultimos_pares(nat i, binario_t b) {
	if (es_vacio_binario(b)) return 0;
	else {
		suma_ultimos_pares(i, derecho(b));
		suma_ultimos_pares(i, izquierdo(b));
		if (((numero_info(raiz(b)) % 2) == 0) && (i > 0)) i--;
	}
	return numero_info(raiz(b));
}

static void lin(binario_t b,cadena_t c) {
	if (!es_vacio_binario(b)) {
		lin(izquierdo(b), c);
		insertar_al_final(copia_info(raiz(b)), c);
		lin(derecho(b), c);
	}
}

cadena_t linealizacion(binario_t b) {
	cadena_t result = crear_cadena();
	lin(b, result);
	return result;
}

/*
	Devuelve un árbol balanceado cuyos elementos son los que están contenidos en
	`cad'.
	En esta función se dice que un árbol está balanceado si
	a) es vacío;
	o
	b)
		b1) el sub-árbol izquierdo tiene la misma cantidad de elementos o uno más
			que el	subárbol derecho;
		y
		b2) los subárboles izquierdo y derecho están balanceados.
	DEFINICIÓN ALTERNATIVA DE ÁRBOL BALANCEADO
	En esta función se dice que un árbol esta balanceado si en cada nodo, la
	cantidad de elementos de su subárbol izquierdo es igual a, o 1 más que, la
	cantidad de elementos de su subárbol derecho.
	Precondición: los elementos de `cad' están en orden lexicográfico creciente
	estricto según sus datos de texto.
	El árbol devuelto no comparte memoria con `cad'.
	El tiempo de ejecución es O(n . log n), siendo `n` la cantidad de elementos
	de `cad'.
 */

binario_t cadena_a_binario(cadena_t cad) {
	if (es_vacia_cadena(cad)) return crear_binario();
	else ; // @TODO: Completar.
	return NULL;
}

/*
	Devuelve un árbol con copias de los elementos de `b' que cumplen la condición
	"numero_info(elemento) < clave".
	La estructura del árbol resultado debe ser análoga a la de `b'. Esto
	significa que dados dos nodos `U' y `V' de `b' en los que se cumple la
	condición y tal que `U' es ancestro de `V', en el árbol resultado la copia de
	`U' debe ser ancestro de la copia de `V' cuando sea posible. Esto no siempre
	se puede lograr y al mismo tiempo mantener la propiedad de orden del árbol
	en el caso en el que en un nodo `V' no se cumple la condición y en sus dos
	subárboles hay nodos en los que se cumple. En este caso, la copia del nodo
	cuyo elemento es el mayor (según la propiedad de orden definida) de los que
	cumplen la condición en el subárbol izquierdo de `V' deberá ser ancestro de
	las copias de @TODOs los descendientes de `V' que cumplen la condición.
	(Ver ejemplos en LetraTarea3.pdf).
	El árbol resultado no comparte memoria con `b'. *)
	El tiempo de ejecución es O(n), donde `n' es la cantidad de elementos de `b'.
 */

binario_t menores(int clave, binario_t b) {
	// TODO: Completar.
	return NULL;
	}

static bool auxCamino(binario_t b, cadena_t c, localizador_t loc) {
	// Si empiezan igual.
	if (strcmp(frase_info(info_cadena(loc, c)), frase_info(raiz(b))) == 0) {
		// Compruebo si hay mas letras en la cadena.
		if (es_localizador(siguiente(loc, c))) {
			// Si debe avanzar a la izquierda o derecha en el árbol.
			if (strcmp(frase_info(info_cadena(siguiente(loc, c), c)), frase_info(raiz(b))) > 0)
				auxCamino(derecho(b), c, siguiente(loc, c));
			else
				auxCamino(izquierdo(b), c, siguiente(loc, c));

		// Compruebo si terminé en una hoja.
		} else if (es_vacio_binario(derecho(b)) && es_vacio_binario(izquierdo(b))) return true;
	}
	return false;
}

bool es_camino(cadena_t c, binario_t b) {
	// Si son de distinto largo.
	//if (altura_binario(b) != longitud(c)) return false;
	// Esto no lo podemos usar acá porque el tiempo de ejecución de altura_binario es O(n) y el de es_camino debe ser O(log n).
	// (O(n) > O(log n)).

	//int result = auxCamino(b, c, inicio_cadena(c));
	//return result == longitud(c);
	// Esto no lo podemos usar acá porque el tiempo de ejecución de longitud es O(n) y el de es_camino debe ser O(log n).
	// (O(n) > O(log n)).
	return auxCamino(b, c, inicio_cadena(c));
}

static void auxNivel(nat actual, nat l, binario_t b, cadena_t cad, localizador_t loc) {
	if (actual != l) {
		// Sigo buscando.
		actual++;
		auxNivel(actual, l, izquierdo(b), cad, loc);
		auxNivel(actual, l, derecho(b), cad, loc);
	} else
		cad = insertar_al_final(copia_info(raiz(b)), cad);
}

cadena_t nivel_en_binario(nat l, binario_t b) {
	cadena_t cad		= crear_cadena();
	localizador_t loc	= inicio_cadena(cad);
	auxNivel(1, l, b, cad, loc);
	loc = NULL;
	return cad;
}

void imprimir_binario(binario_t b) {
	if (!es_vacio_binario(b)) {
		imprimir_binario(derecho(b));
		printf("%s", info_a_texto(raiz(b)));
		imprimir_binario(izquierdo(b));
	}
}
