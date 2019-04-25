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
	if (!es_vacio_binario(b)) 
		if (!es_vacio_binario(derecho(b))) return mayor(derecho(b));
	return (raiz(b));
}

binario_t remover_mayor(binario_t b) {
	assert(!es_vacio_binario(b));
	if (derecho(b) == NULL) {
		binario_t izq = izquierdo(b);
		delete(b);
		b = izq;
	} else
		b->der = remover_mayor(derecho(b));
	return b;
}

static binario_t masDerecho(binario_t braiz, binario_t &padre, binario_t actual, binario_t result) {
	// Avanzo hasta el más derecho.
	if (!es_vacio_binario(derecho(actual))) result = masDerecho(braiz, actual, derecho(actual), result);
	else result = actual;
	// Arreglo el resto del árbol.
	if ((actual == result) && (padre != braiz)) padre->der = izquierdo(actual);
	return result;
}

static binario_t masIzquierdo(binario_t &padre, binario_t actual) {
	if (!es_vacio_binario(izquierdo(actual)))		actual = masIzquierdo(actual, izquierdo(actual));
	else if (!es_vacio_binario(derecho(actual)))	padre->izq = derecho(actual);
	return actual;
}

binario_t remover_de_binario(const char *t, binario_t b) {
	if (strcmp(t, frase_info(raiz(b))) == 0) {
		if (es_vacio_binario(derecho(b)) && es_vacio_binario(izquierdo(b))) b = liberar_binario(b);
		else if (!es_vacio_binario(izquierdo(b))) {
			binario_t aux	= crear_binario();
			aux				= masDerecho(b, b, izquierdo(b), aux);
			if (aux != izquierdo(b)) aux->izq = izquierdo(b);
			else {
				if (!es_vacio_binario(izquierdo(aux))) {
					binario_t aux2	= crear_binario();
					aux2			= masDerecho(b, b, aux, aux2);
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
					binario_t aux2	= crear_binario();
					aux2			= masDerecho(b, b, aux, aux2);
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

static nat auxSumaUltimosPares(binario_t actual, nat i, nat pos ,nat &cont, nat sumaPares) {
	if (!es_vacio_binario(actual)) {
		pos++;
		sumaPares = auxSumaUltimosPares(derecho(actual), i, pos, cont, sumaPares);
		if ((cont < i) && (numero_info(raiz(actual)) % 2) == 0) {
			cont++;
			sumaPares += numero_info(raiz(actual));
		}
		sumaPares = auxSumaUltimosPares(izquierdo(actual), i, pos, cont, sumaPares);
	}
	return sumaPares;
}

int suma_ultimos_pares(nat i, binario_t b) {
	nat cont = 0;
	return auxSumaUltimosPares(b, i, 0, cont, 0);
}

static void lin(binario_t b, cadena_t c) {
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

/* Devuelve la mitad de la cadena. */
static nat medioCadena(nat ini, nat fin) { return ceil(((double)ini + (double)fin) / 2); }

static binario_t auxCadenaABinario(nat inicio, cadena_t cad, nat largo) {
	if (inicio > largo) return NULL;
	else {
		// Obtengo el elemento posicionado en la mitad de la cadena.
		binario_t result	= new rep_binario;
		result->dato		= copia_info(info_cadena(kesimo(medioCadena(inicio, largo), cad), cad));
		// Divido la cadena y sigo con los hijos.
		result->izq	= auxCadenaABinario(inicio, cad, medioCadena(inicio, largo) - 1);
		result->der	= auxCadenaABinario(medioCadena(inicio, largo) + 1, cad, largo);
		return result;
	}
}

binario_t cadena_a_binario(cadena_t cad) {
	return !es_vacia_cadena(cad) ? auxCadenaABinario(1, cad, longitud(cad)) : crear_binario();
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
			if (strcmp(frase_info(info_cadena(siguiente(loc, c), c)), frase_info(raiz(b))) > 0) {
				if (!es_vacio_binario(derecho(b))) return auxCamino(derecho(b), c, siguiente(loc, c));
				else return false;
			} else {
				if (!es_vacio_binario(izquierdo(b))) return auxCamino(izquierdo(b), c, siguiente(loc, c));
				else return false;
			}
		// Compruebo si terminé en una hoja.
		} else if (es_vacio_binario(derecho(b)) && es_vacio_binario(izquierdo(b))) return true;
	}
	return false;
}

bool es_camino(cadena_t c, binario_t b) {
	return (!es_vacio_binario(b)) ? auxCamino(b, c, inicio_cadena(c)) : false;
}

static cadena_t auxNivel(binario_t b, cadena_t cad, localizador_t loc, nat actual, nat l) {
	if (!es_vacio_binario(b)) {
		actual++;
		if (actual == l) cad = insertar_al_final(copia_info(raiz(b)), cad);
		else {
			// Sigo buscando.
			cad = auxNivel(izquierdo(b), cad, loc, actual, l);
			cad = auxNivel(derecho(b), cad, loc, actual, l);
		}
	}
	return cad;
}

cadena_t nivel_en_binario(nat l, binario_t b) {
	cadena_t cad	= crear_cadena();
	cad				= auxNivel(b, cad, inicio_cadena(cad), 0, l);
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
