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
#include <math.h>		/* ceil */
#include <algorithm>	/* max */



struct rep_binario {
	info_t dato;
	rep_binario *izq;
	rep_binario *der;
};

binario_t crear_binario() { return NULL; }

binario_t insertar_en_binario(info_t i, binario_t b) {
	if (es_vacio_binario(b)) {
		b			= new rep_binario;
		b->dato		= i;
		b->der		= NULL;
		b->izq		= NULL;
	} else {
		if (strcmp(frase_info(raiz(b)), frase_info(i)) < 0) b->der = insertar_en_binario(i, derecho(b));
		else b->izq = insertar_en_binario(i, izquierdo(b));
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

static binario_t masDerecho(binario_t padre, binario_t actual) {
	if (!es_vacio_binario(derecho(actual)))			actual = masDerecho(actual, derecho(actual));
	else if (!es_vacio_binario(izquierdo(actual)))	padre->der = izquierdo(actual);
	return actual;
}

static binario_t masIzquierdo(binario_t padre, binario_t actual) {
	if (!es_vacio_binario(izquierdo(actual)))		actual = masIzquierdo(actual, izquierdo(actual));
	else if (!es_vacio_binario(derecho(actual)))	padre->izq = derecho(actual);
	return actual;
}

binario_t remover_de_binario(const char *t, binario_t b) {
	if (strcmp(t, frase_info(raiz(b))) == 0) {
		if (es_vacio_binario(derecho(b)) && es_vacio_binario(izquierdo(b))) b = liberar_binario(b);
		else if (!es_vacio_binario(izquierdo(b))) {
			binario_t aux = masDerecho(b, izquierdo(b));
			if (aux != izquierdo(b)) aux->izq = izquierdo(b);
			else {
				if (!es_vacio_binario(izquierdo(aux))) {
					binario_t aux2	= masDerecho(b, aux);
					aux2->izq		= izquierdo(aux);
					aux2->der		= derecho(aux);
					aux->izq		= aux2;
				} else b->izq = NULL;
			}
			aux->der = derecho(b);
			info_t a_borrar	= raiz(b);
			liberar_info(a_borrar);
			delete b;
			return aux;
		} else {
			binario_t aux = masIzquierdo(b, derecho(b));
			if (aux != derecho(b)) {
				aux->izq	= izquierdo(b);
				aux->der	= derecho(b);
			} else {
				if (!es_vacio_binario(derecho(aux))) {
					binario_t aux2	= masDerecho(b, aux);
					aux2->izq		= izquierdo(aux);
					aux2->der		= derecho(aux);
					aux->izq		= aux2;
				} else b->der = NULL;
			}
			info_t a_borrar	= raiz(b);
			liberar_info(a_borrar);
			delete b;
			return aux;
		}
	} else if (strcmp(t, frase_info(raiz(b))) < 0) {
		if (!es_vacio_binario(izquierdo(b)))	b->izq = remover_de_binario(t, izquierdo(b));
	} else if (!es_vacio_binario(derecho(b)))	b->der = remover_de_binario(t, derecho(b));
	return b;
}

binario_t liberar_binario(binario_t b) {
	if (b != NULL) {
		b->izq	= liberar_binario(izquierdo(b));
		b->der	= liberar_binario(derecho(b));
		info_t a_borrar = raiz(b);
		liberar_info(a_borrar);
		delete b;
		b = NULL;
	}
	return b;
}

bool es_vacio_binario(binario_t b) { return b == NULL; }

static int absoluto(int n) { return (n >= 0) ? (n) : (-n); }

static bool auxEsAVL(binario_t actual, nat &altura) {
	bool esIzqAVL	= false;
	bool esDerAVL	= false;
	nat alturaIzq	= 0;
	nat alturaDer	= 0;

	if (!es_vacio_binario(actual)) {
		// Compruebo si los hijos son AVL.
		esIzqAVL	= auxEsAVL(actual->izq, alturaIzq);
		esDerAVL	= auxEsAVL(actual->der, alturaDer);
		altura		= 1 + std::max(alturaDer, alturaIzq);

		return (absoluto(alturaIzq - alturaDer) <= 1) ? (esIzqAVL && esDerAVL) : false;
	} else {
		altura = 0;
		return true;
	}
}

bool es_AVL(binario_t b) {
	if (!es_vacio_binario(b)) {
		nat aux = 0;
		return auxEsAVL(b, aux);
	} else return true;
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

static int maximo(nat n1, nat n2) { return (n1 >= n2) ? (n1) : (n2); }

nat altura_binario(binario_t b) {
	if (es_vacio_binario(b)) return 0;
	else return 1 + maximo(altura_binario(izquierdo(b)), altura_binario(derecho(b)));
}

/*
static int auxCantBin(binario_t b, int &cont) {
	if (!es_vacio_binario(b)) {
		cont++;
		if (!es_vacio_binario(izquierdo(b)))	cont = auxCantBin(izquierdo(b), cont);
		if (!es_vacio_binario(derecho(b)))		cont = auxCantBin(derecho(b), cont);
	}
	//printf("%d", cont);
	return cont;
}

nat cantidad_binario(binario_t b) {
	int cont	= 0;
	cont		= auxCantBin(b, cont);
	return cont;
}
*/

static int auxCantBin(binario_t b, int cont) {
	if (!es_vacio_binario(izquierdo(b))) {
		cont++;
		cont = auxCantBin(izquierdo(b), cont);
	}
	if (!es_vacio_binario(derecho(b))) {
		cont++;
		cont = auxCantBin(derecho(b), cont);
	}
	return cont;
}

nat cantidad_binario(binario_t b) {
	if (es_vacio_binario(b)) return 0;
	else return auxCantBin(b, 1);
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
/*	
static binario_t insertarElementoDeCadenaEnBinario(binario_t raiz, binario_t *padre, binario_t *actual; cadena_t cad) {

	// Se resuelve mediante el método de bipartición.
	localizador_t loc;
	// Si hay mas de un elemento.
	if (largo > 1) {
		// Voy al elemento posicionado en la mitad de la cadena si la misma es de largo impar, o al anterior a éste si es par. Ese elemento será la raíz del árbol.
		if ((i % 2) == 0) loc = kesimo(i - 1, cad);
		else loc = kesimo(i, cad);
		i--;
	}

	actual->dato = info_cadena(loc, cad);

	// Separo la cadena en dos partes (al medio) haciendo lo mismo para cada segmento obtenido.
	cadena_t cad1	= copiar_segmento(inicio_cadena(cad), loc, cad);
	cadena_t cad2	= copiar_segmento(loc, final_cadena(cad), cad);

	if (!es_vacio_binario(padre)) {
		if (!es_vacia_cadena(cad1)) {
			padre->izq	= actual;
			actual->izq	= insertarElementoDeCadenaEnBinario(b, padre, actual, cad1);
		}
		if (!es_vacia_cadena(cad2)) {
			padre->der	= actual;
			actual->der	= insertarElementoDeCadenaEnBinario(b, padre, actual, cad1);
		}
	} else {
		// TODO: Completar para el caso en que es la primera ejecución.
		if (!es_vacia_cadena(cad1)) actual->izq	= insertarElementoDeCadenaEnBinario(b, padre, actual, cad1);
		if (!es_vacia_cadena(cad2)) actual->der	= insertarElementoDeCadenaEnBinario(b, padre, actual, cad1);
	}

	liberar_cadena(cad1);
	liberar_cadena(cad2);

	return raiz;
}
*/
/*
static binario_t auxCadABin(binario_t raiz, cadena_t cad, binario_t actual, nat largo, int cont) {
	if (es_vacio_binario(actual)) actual = insertar_en_binario(kesimo(ceil((largo + cont) / 2), cad));
	else {
		actual	= auxCadABin(raiz, cad, derecho(actual), largo, ceil((largo + cont) / 2) + 1);
		actual	= auxCadABin(raiz, cad, izquierdo(actual), ceil((largo + cont) / 2) - 1, cont);
	}
	return raiz;
}

binario_t cadena_a_binario(cadena_t cad) {
	binario_t b = crear_binario()
	if (es_vacia_cadena(cad)) return b;
	else return auxCadABin(b, cad, b, longitud(cad), 0);
}
*/
/*
binario_t cadena_a_binario(cadena_t cad) {

	binario_t b = crear_binario();
	if (es_vacia_cadena(cad)) return b;
	else return aux_cadena_a_binario(b, cad, longitud(cad));
}
*/

/*
static binario_t aux_CadABin_izq(binario_t raiz, cadena_t cad, localizador_t loc, nat padre, nat largo) {
	if (padre > 1) {
		if ((padre % 2) == 0) actual = padre / 2;
		else actual = ceil(largo / 2);

		loc		= kesimo(actual, cad);
		b->dato	= info_cadena(loc, cad);

		if (((actual > 0) raiz = aux_CadABin_izq(raiz, cad, loc, actual, largo);
		if (((padre - actual) / 2) > 0) raiz = aux_CadABin_der(raiz, cad, loc, actual, largo);
	}
	return raiz;
}

static binario_t aux_CadABin_der(binario_t raiz, cadena_t cad, localizador_t loc, nat prev, nat largo) {
	if (padre < largo) {
		if (((padre + largo) % 2) == 0) actual	= (padre + largo) / 2;	
		else actual	= ceil((largo + padre) / 2);

		loc		= kesimo(actual, cad);
		b->dato	= info_cadena(loc, cad);

		if (((actual < 0) raiz = aux_CadABin_izq(raiz, cad, loc, actual);
		if (((padre - actual) / 2) > 0) raiz = aux_CadABin_der(raiz, cad, loc, actual);
	}
	return raiz;
}

binario_t cadena_a_binario(cadena_t cad) {
	binario_t raiz = crear_binario();
	if (es_vacia_cadena(cad)) return raiz;
	else {
		localizador_t loc = inicio_cadena(cad);
		// Si cad tiene solo un elemento.
		if (!es_localizador(siguiente(loc))) {
			raiz->dato	= info_cadena(loc, cad);
			loc			= NULL;
			return raiz;
		} else {
			// Si hay más de un elemento en cad.
			// Voy al elemento posicionado en la mitad de la cadena si la misma es de largo impar, o al anterior a éste si es par. Ese elemento será la raíz del árbol.
			nat largo = longitud(cad);
			nat actual;
			if ((largo % 2) == 0) {
				actual = largo / 2;
				loc = kesimo(actual, cad);
			} else {
				actual	= ceil(largo / 2);
				loc		= kesimo(actual, cad);
			}

			raiz->dato	= info_cadena(loc, cad);
			raiz->izq	= aux_CadABin_izq(crear_binario(), cad, loc, actual, largo);
			raiz->der	= aux_CadABin_der(crear_binario(), cad, loc, actual, largo);
		}
	}
	return raiz;
}
*/

/*
static binario_t auxCadABin(info_t arr[], binario_t b, int max, int inicio) {
	if (es_vacio_binario(b)) {
		b = insertar_en_binario(arr[ceil((max + inicio) / 2)]);
		if (inicio >= max) return b;
	} else {
		b->der = auxCadABin(arr, derecho(b), max, ceil((max+inicio)/2));
		b->izq = auxCadABin(arr, izquierdo(b), ceil((max+inicio)/2), inicio);
	}
}

binario_t cadena_a_binario(cadena_t cad) {
	if (es_vacia_cadena(cad)) return crear_binario();
	else {
		int largo = longitud(cad);
		info_t arr [largo];
		localizador_t loc = inicio_cadena (cad);
		for (int i = 0; i < largo; i++) {
			arr[i] = info_cadena(loc, cad);
			loc	= siguiente(loc);
		}
		binario_t b = crear_binario();
		return auxCadABin(arr, b, largo, 0);
	} 
}
*/

static binario_t auxCadABin(cadena_t cad, binario_t b, int max, int inicio) {
	if (es_vacio_binario(b)) {
		b = insertar_en_binario(info_cadena(kesimo(ceil((max + inicio) / 2), cad), cad), b);
		if (inicio >= max) return b;
	} else {
		b->der = auxCadABin(cad, derecho(b), max, ceil((max + inicio) / 2));
		b->izq = auxCadABin(cad, izquierdo(b), ceil((max + inicio) / 2), inicio);
	}
	return b;
}

binario_t cadena_a_binario(cadena_t cad) {
	binario_t raiz = crear_binario();
	if (es_vacia_cadena(cad)) return raiz;
	else {
		localizador_t loc = inicio_cadena(cad);
		// Si cad tiene solo un elemento.
		if (!es_localizador(siguiente(loc, cad))) {
			raiz->dato	= info_cadena(loc, cad);
			loc			= NULL;
			return raiz;
		} else {
			// Si hay más de un elemento en cad.
			// Voy al elemento posicionado en la mitad de la cadena si la misma es de largo impar, o al anterior a éste si es par. Ese elemento será la raíz del árbol.
			nat largo = longitud(cad);
			nat actual;
			if ((largo % 2) == 0) {
				actual = largo / 2;
				loc = kesimo(actual, cad);
			} else {
				actual	= ceil(largo / 2);
				loc		= kesimo(actual, cad);
			}
			raiz = auxCadABin(cad, raiz, largo, 0);
		}
	}
	return raiz;
}

/* Compara el elemento numérico de b con la clave y devuelve un booleano con el resultado de la comparación. */
static bool esMenor(binario_t b, int clave) { return numero_info(raiz(b)) < clave; }

/*
	Busca la nueva raíz para el árbol de elementos que cumplen la condición (resultado).
	Si lo encuentra devuelve el elemento, si no devuelve NULL.
*/
static binario_t buscarNuevaRaiz(binario_t actual, int clave) {
	if (!es_vacio_binario(derecho(actual))) actual = buscarNuevaRaiz(derecho(actual), clave);
	if (esMenor(actual, clave)) return actual;
	// Si no encontré una nueva raíz busco en el hijo izquierdo.
	if (!es_vacio_binario(izquierdo(actual))) actual = buscarNuevaRaiz(izquierdo(actual), clave);
	return NULL;
}

static binario_t auxMenoresRecorrer(binario_t result, binario_t actual, int clave) {
	if (!es_vacio_binario(actual)) {
		if (esMenor(actual, clave))
			// Verifico que no esté agregado porque podría llegar a ser una raíz obtenida en buscarNuevaRaiz.
			if (es_vacio_binario(buscar_subarbol(frase_info(raiz(actual)), result))) result = insertar_en_binario(copia_info(raiz(actual)), result);
		result	= auxMenoresRecorrer(result, izquierdo(actual), clave);
		result	= auxMenoresRecorrer(result, derecho(actual), clave);
	}
	return result;
}

static binario_t auxMenores(binario_t result, binario_t actual, int clave) {
	if (!es_vacio_binario(actual)) {
		if (esMenor(actual, clave)) {
			// Verifico que no esté agregado porque podría llegar a ser una raíz obtenida en buscarNuevaRaiz.
			if (es_vacio_binario(buscar_subarbol(frase_info(raiz(actual)), result))) result = insertar_en_binario(copia_info(raiz(actual)), result);
		} else if (!es_vacio_binario(izquierdo(actual))) {
			binario_t nuevaRaiz = buscarNuevaRaiz(izquierdo(actual), clave);
			if (!es_vacio_binario(nuevaRaiz)) {
				// Verifico que no esté agregado porque podría llegar a ser una raíz obtenida en buscarNuevaRaiz.
				if (es_vacio_binario(buscar_subarbol(frase_info(raiz(nuevaRaiz)), result))) result = insertar_en_binario(copia_info(raiz(nuevaRaiz)), result);
			}
		}
		result	= auxMenoresRecorrer(result, derecho(actual), clave);
		result	= auxMenoresRecorrer(result, izquierdo(actual), clave);
	}
	return result;
}

binario_t menores(int clave, binario_t b) {
	binario_t result = crear_binario();
	if (!es_vacio_binario(b)) {
		if (esMenor(b, clave)) result = insertar_en_binario(copia_info(raiz(b)), result);
		else if (!es_vacio_binario(izquierdo(b))) {
			// Obtengo la nueva raiz del árbol a retornar.
			binario_t nuevaRaiz = buscarNuevaRaiz(izquierdo(b), clave);
			if (!es_vacio_binario(nuevaRaiz)) result = insertar_en_binario(copia_info(raiz(nuevaRaiz)), result);
		}
		// Ahora sigo con el resto del árbol.
		result	= auxMenoresRecorrer(result, derecho(b), clave);
		result	= auxMenores(result, izquierdo(b), clave);
	}
	return result;
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
	cadena_t cad = crear_cadena();
	auxNivel(1, l, b, cad, inicio_cadena(cad));
	return cad;
}

static void auxImprimirBinario(binario_t b, int cont) {
	if (!es_vacio_binario(derecho(b))) auxImprimirBinario(derecho(b), cont + 1);
	char *infoText = info_a_texto(raiz(b));
	for (int i = 0; i < cont; i++) printf("-");
	printf("%s", infoText);
	printf("\n");
	delete[] infoText;
	if (!es_vacio_binario(izquierdo(b))) auxImprimirBinario(izquierdo(b), cont + 1);
}

void imprimir_binario(binario_t b) {
	printf("\n");
	if (!es_vacio_binario(b)) auxImprimirBinario(b, 0);
}
