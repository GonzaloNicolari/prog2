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



binario_t insertar_en_binario(info_t i, binario_t b) {



	if (es_vacio_binario(b)) {

		b = new rep_binario;
		b->dato = i;

		return b;

	} else {

		if (strcmp(frase_info(b -> dato), frase_info(i)) < 0) insertar_en_binario(i, derecho(b));

		else insertar_en_binario(i, izquierdo(b));

	}

	return b;

}



info_t mayor(binario_t b) {



	if (derecho(b) != NULL) mayor(derecho(b));

	else mayor(izquierdo(b));
	return (b->dato);

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

//static void auxRemover(const char *t, binario_t b, binario_t padre) {

	//insertar_al_final(mayor(izquierdo(b), ));

	

	

//}


binario_t remover_de_binario(const char *t, binario_t b) {



	if (t < frase_info(b -> dato)) {

		//binario_t prev = b;

		remover_de_binario (t, izquierdo(b));

		//ACA HAGO ALGO CON EL PADRE prev

		

	} else if (t > frase_info(b -> dato)) remover_de_binario (t, derecho(b));

	else if (t == frase_info(b -> dato)) { 

		

			// TODO: A COMPLETAR BORRAR NOD

		

	}

	return NULL;

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



/*

  Devuelve `true' si y sólo si cada nodo de `b' cumple la condición de balanceo

  AVL. El árbol vacío cumple la condición.

  Un nodo cumple la condición de balanceo AVL si el valor absoluto de la

  diferencia de las alturas de sus subárboles izquierdo y derecho en menor o

  igual a 1.

  Cada nodo se puede visitar una sola vez.

  El tiempo de ejecución es O(n), donde `n' es la cantidad de elementos de `b'.

 */

bool es_AVL(binario_t b) { return 0;}



info_t raiz(binario_t b) { return (b -> dato); }



binario_t izquierdo(binario_t b) { return (b -> izq); }



binario_t derecho(binario_t b) { return (b -> der); }



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


//static int absoluto(int n) { return (n >= 0) ? (n) : (-n); }



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

		if (((numero_info(b->dato) % 2) == 0) && (i > 0)) {

			i--;

		}

	}
	return numero_info(b->dato);

}



static void lin(binario_t b,cadena_t c) {



	if (!es_vacio_binario(b)) {

		lin(b->izq, c);

		insertar_al_final(copia_info(b->dato), c);

		lin(b->der, c);

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

      que el  subárbol derecho;

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

	else ;// TODO: COMPLETAR.

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

  las copias de todos los descendientes de `V' que cumplen la condición.

  (Ver ejemplos en LetraTarea3.pdf).

  El árbol resultado no comparte memoria con `b'. *)

  El tiempo de ejecución es O(n), donde `n' es la cantidad de elementos de `b'.

 */

binario_t menores(int clave, binario_t b) { return NULL; }



/*

  Devuelve `true' si y solo si en `b' hay un camino desde la raiz hasta una

  hoja que sea compatible con `c'.

  Decimos que una cadena y un camino son compatibles si tienen la misma

  longitud y al recorrer la cadena desde el inicio hasta el final y el camino

  desde la raíz hasta la hoja las frases de los respectivos elementos son

  iguales.

  El tiempo de ejecución es O(log n) en promedio, donde `n' es la cantidad de

  elementos de `b'.

 */

bool es_camino(cadena_t c, binario_t b) { return 0; }



/*

  Devuelve una cadena_t con los elementos del nivel `l' de 'b'.

  La raíz es el nivel 1.

  La cadena_t resultado debe estar ordenada de manera creciente según las

  frases de sus elementos.

  La cadena_t devuelta no comparte memoria con `b'.

 */

cadena_t nivel_en_binario(nat l, binario_t b) { return NULL; }



void imprimir_binario(binario_t b) {



	if (b != NULL) {

		imprimir_binario(derecho(b));

		printf("%s", info_a_texto(b->dato));

		imprimir_binario(izquierdo(b));

	}

}
