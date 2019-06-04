/* 46450368			- 48579580 */
// Nicolás Saliba	- Gonzalo Nicolari.
// Instituto de Computación - Facultad de Ingeniería, Laboratorio de Programación 2.

#include "../include/avl.h"
#include "../include/info.h"
#include "../include/pila.h"
#include "../include/cola_avls.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <limits.h>

struct rep_avl {
	info_t dato;
	nat altura, cantidad;
	rep_avl *izq, *der;
};

avl_t crear_avl() { return NULL; }

bool es_vacio_avl(avl_t avl) { return avl == NULL; }

nat cantidad_en_avl(avl_t avl) { return es_vacio_avl(avl) ? 0 : avl->cantidad; }

nat altura_de_avl(avl_t avl) { return es_vacio_avl(avl) ? 0 : avl->altura; }

static int balance_de_avl(avl_t a) { return a == NULL ? 0 : altura_de_avl(a->izq) - altura_de_avl(a->der); }

static avl_t rotarD(avl_t a, int &fb) {
	avl_t aux		= a->izq;
	avl_t aux2		= aux->der;
	aux->der		= a;
	a->izq			= aux2;
	a->altura		= std::max(altura_de_avl(a->izq), altura_de_avl(a->der)) + 1;
	a->cantidad		= cantidad_en_avl(a->izq) + cantidad_en_avl(a->der) + 1;
	aux->altura		= std::max(altura_de_avl(aux->izq), altura_de_avl(aux->der)) + 1;
	aux->cantidad	= cantidad_en_avl(aux->izq) + cantidad_en_avl(aux->der) + 1;
	fb				= balance_de_avl(aux);
	return aux;
}

static avl_t rotarI(avl_t a, int &fb) {
	avl_t aux		= a->der;
	avl_t aux2		= aux->izq;
	aux->izq		= a;
	a->der			= aux2;
	a->altura		= std::max(altura_de_avl(a->izq), altura_de_avl(a->der)) + 1;
	a->cantidad		= cantidad_en_avl(a->izq) + cantidad_en_avl(a->der) + 1;
	aux->altura		= std::max(altura_de_avl(aux->izq), altura_de_avl(aux->der)) + 1;
	aux->cantidad	= cantidad_en_avl(aux->izq) + cantidad_en_avl(aux->der) + 1;
	fb				= balance_de_avl(aux);
	return aux;
}

/*
	Inserta `i' en `avl' respetando la propiedad de orden definida.
	Precondición: es_vacio_avl(buscar_en_avl(numero_info(i), avl).
	Precondición: numero_info(i) != INT_MAX.
	El tiempo de ejecución es O(log n), donde `n' es la cantidad de elementos de `avl'.
*/
void insertar_en_avl(info_t i, avl_t &avl) {
	assert(es_vacio_avl(buscar_en_avl(numero_info(i), avl)));
	assert(es_valida_info(i));
	if (es_vacio_avl(avl)) {
		avl				= new rep_avl;
		avl->cantidad	= 1;
		avl->altura		= 1;
		avl->dato		= i;
		avl->izq		= NULL;
		avl->der		= NULL;
	} else if (numero_info(i) < numero_info(avl->dato)) insertar_en_avl(i, avl->izq);
	else insertar_en_avl(i, avl->der);

	avl->altura		= std::max(altura_de_avl(avl->izq), altura_de_avl(avl->der)) + 1;
	avl->cantidad	= cantidad_en_avl(avl->izq) + cantidad_en_avl(avl->der) + 1;
	int fact_bal	= balance_de_avl(avl);

	// Left left case.
	if (fact_bal > 1 && numero_info(i) < numero_info(avl->izq->dato)) avl = rotarD(avl, fact_bal);

	// Right right case.
	else if (fact_bal < -1 && numero_info(i) > numero_info(avl->der->dato)) avl = rotarI(avl, fact_bal);

	// Left right case.
	else if (fact_bal > 1 && avl->izq != NULL && numero_info(i) > numero_info(avl->izq->dato)) {
		avl->izq	= rotarI(avl->izq, fact_bal);
		avl			= rotarD(avl, fact_bal);
	}

	// Left right case.
	else if (fact_bal < -1 && avl->der != NULL && numero_info(i) < numero_info(avl->der->dato)) {
		avl->der	= rotarD(avl->der, fact_bal);
		avl			= rotarI(avl, fact_bal);
	}
}

avl_t buscar_en_avl(int clave, avl_t avl) {
	if (es_vacio_avl(avl)) return NULL;
	else {
		if (numero_info(avl->dato) == clave) return avl;
		else if (numero_info(avl->dato) > clave) return buscar_en_avl(clave, avl->izq);
		else return buscar_en_avl(clave, avl->der);
	}
}

info_t raiz_avl(avl_t avl) {
	assert(!es_vacio_avl(b));
	return avl->dato;
}

avl_t izq_avl(avl_t avl) {
	assert(!es_vacio_avl(avl));
	return avl->izq;
}

avl_t der_avl(avl_t avl) {
	assert(!es_vacio_avl(avl));
	return avl->der;
}

static info_t *en_orden_rec(info_t *res, nat &tope, avl_t avl) {
	if (!es_vacio_avl(avl)) {
		res			= en_orden_rec(res, tope, izq_avl(avl));
		res[tope]	= raiz_avl(avl);
		tope++;
		res = en_orden_rec(res, tope, der_avl(avl));
	}
	return res;
}

/*
	Devuelve un arreglo con los elementos de `avl'.
	Los elementos en el arreglo deben estar en orden creciente según los datos numericos.
 */
info_t *en_orden_avl(avl_t avl) {
	info_t *res;
	if (es_vacio_avl(avl)) res = NULL;
	else {
		res			= new info_t[avl->cantidad];
		nat tope	= 0;
		res			= en_orden_rec(res, tope, avl);
	}
	return res;
}

static avl_t a2avl_rec(info_t *infos, int inf, int sup) {
	avl_t res;
	if (inf > sup) res = NULL;
	else {
		nat medio	= (inf + sup) / 2;
		res			= new rep_avl;
		res->dato	= infos[medio];
		res->izq	= a2avl_rec(infos, inf, medio - 1);
		res->der	= a2avl_rec(infos, medio + 1, sup);
		//res->altura	= ;
		//res->cantidad = 1.44 * altura;
	}
	//res->altura++;
	return res;
}

/*
	Devuelve un avl_t con los `n' elementos que están en el rango [0 .. n - 1] del arreglo `infos'.
	Los elementos están ordenados de manera creciente estricto (creciente y sin repetidos) según los datos numércos.
	En cada nodo del árbol resultado la cantidad de elementos de su subárbol izquierdo es igual a, o 1 menos que, la cantidad de elementos de su subárbol derecho.
	El tiempo de ejecución es O(n).
 */
avl_t arreglo_a_avl(info_t *infos, nat n) { return a2avl_rec(infos, 0, n - 1); }

struct avl_ultimo {
	avl_t avl;
	int ultimo;
};

static avl_ultimo avl_min_rec(nat h, nat primero) {
	avl_ultimo res;
	if (h == 0) {
		res.avl		= NULL;
		res.ultimo	= primero - 1;
	} else if (h == 1) {
		// TODO: completar.
		res.avl					= new rep_avl;
		//res.avl->dato->frase	= "";
		res.avl->der			= NULL;
		res.avl->izq			= new rep_avl;
		avl_t iz				= res.avl->izq;
		//iz->dato->frase		= "";
		iz->izq					= NULL;
		iz->der					= NULL;
	} else {
		// TODO: completar.
	}
	return res;
}

/*
	Devuelve un avl_t de altura `h' con `n' nodos, siendo `n' la mínima cantidad de elementos que puede tener un avl de altura `h'.
	Los datos numéricos de los elementos van desde 1 hasta `n'.
	El dato de texto de cada elemento es la cadena vacia.
	En ningún nodo puede ocurrir que el subárbol derecho tenga más nodos que el subárbol izquierdo.
	El tiempo de ejecución es O(n).
	Ver ejemplos en la letra y en el caso 408.
 */
avl_t avl_min(nat h) {
	avl_ultimo res = avl_min_rec(h, 1);
	return res.avl;
}

/*
	Imprime los datos numéricos de los nodos de cada nivel de `avl'.
	Imprime una línea por nivel, primero el más profundo y al final el que corresponde a la raíz.
	Cada nivel se imprime de izquierda a derecha. Se debe dejar un espacio en blanco después de cada número.
	El tiempo de ejecución es O(n), siendo `n' la cantidad de nodos de `avl'.
	Ver ejemplos en la letra y en el caso 404.
 */
void imprimir_avl(avl_t avl) {
	/*
	if (!es_vacio_avl(avl)) {
		pila_t p			= crear_pila(avl->altura + avl->cantidad);
		avl_t flag			= new rep_avl;
		flag->dato			= crear_info(INT_MAX, NULL);
		cola_avls_t cavl	= crear_cola_avls();
		encolar(avl, cavl);
		encolar(flag, cavl);
		while (!es_vacia_cola_avls(cavl)) {
			avl = frente(cavl);
			if (avl != NULL) {
				apilar(numero_info(avl->dato), p);
				if (!es_vacio_avl(avl->der)) encolar(avl->der, cavl);
				if (!es_vacio_avl(avl->izq)) encolar(avl->izq, cavl);
				desencolar(cavl);
			} else {
				encolar(flag, cavl);
				print("\n");
			}
		}
		while (!es_vacia_pila(p)) {
			if (cima(p) != INT_MAX) printf("%d ", cima(p));
			else printf("\n");
			desapilar(p);
		}
		liberar_pila(p);
		liberar_cola_avls(cavl);
	}
	*/
	
	if (!es_vacio_avl(avl)) {
		pila_t p			= crear_pila(avl->altura + avl->cantidad);
		cola_avls_t cavl	= crear_cola_avls();
		encolar(avl, cavl);
		while (!es_vacia_cola_avls(cavl)) {
			avl = frente(cavl);
			desencolar(cavl);
			apilar(numero_info(avl->dato), p);
			if (!es_vacio_avl(avl->der)) encolar(avl->der, cavl);
			if (!es_vacio_avl(avl->izq)) encolar(avl->izq, cavl);
			apilar(INT_MAX, p);
		}
		while (!es_vacia_pila(p)) {
			if (cima(p) != INT_MAX) printf("%d ", cima(p));
			else printf("\n");
			desapilar(p);
		}
		liberar_pila(p);
		liberar_cola_avls(cavl);
	}
	
}

/*
static void imprimir_nivel(avl_t a, nat n) {
    if (!es_vacio_avl(a)) { 
        if (n == 0)
            printf("\n");
        if ((a->izq == NULL) && (a->der == NULL)) {
                nat i = 0;
                while (i != n){
                    printf("%c",'-');
                    i++;
                }
                printf("(%d,%s)\n", numero_info(a->dato), frase_info(a->dato));
        }else{
            imprimir_nivel(a->der, n+1);
            nat i = 0;
            while (i != n) {
                printf("%c",'-');
                i++;
            }
            printf("(%d,%s)\n", numero_info(a->dato), frase_info(a->dato));
            imprimir_nivel(a->izq, n+1);
        }
    }
}

void imprimir_avl(avl_t avl) {
    if (avl == NULL){
        printf("\n");
    } else {
        int a = 0;
        imprimir_nivel(avl, a);
    }
}
*/

/*
	Libera la memoria asignada a `avl' y la de sus elementos.
	El tiempo de ejecución es O(n), donde `n' es la cantidad de elementos de `avl'.
 */
void liberar_avl(avl_t &avl) {
	if (!es_vacio_avl(avl)) {
		liberar_info(avl->dato);
		liberar_avl(avl->der);
		liberar_avl(avl->izq);
		delete (avl);
	}
}
