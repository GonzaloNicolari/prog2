/*
  Módulo de definición de `binario_t'.

  Se definen los árboles binarios de búsqueda de elementos de tipo `info_t'.
  La propiedad de orden de los árboles es definida por la frase de sus
  elementos.

  Laboratorio de Programación 2.
  InCo-FIng-UDELAR
 */

#ifndef _BINARIO_H
#define _BINARIO_H

#include "cadena.h"
#include "info.h"

// representación de `binario_t'. Se debe definir en binario.cpp
struct rep_binario;
typedef rep_binario *binario_t;

/*
  Devuelve un binario_t vacío (sin elementos).
  El tiempo de ejecución es O(1).
 */
binario_t crear_binario();

/*
  Inserta `i' en `b' respetando la propiedad de orden definida.
  Devuelve `b'.
  Precondición: es_vacio_binario(buscar_subarbol(frase_info(i), b).
  El tiempo de ejecución es O(log n) en promedio, donde `n' es la cantidad de
  elementos de `b'.
 */
binario_t insertar_en_binario(info_t i, binario_t b);

/*
  Devuelve el elemento mayor (según la propiedad de orden definida) de `b'.
  Precondición: ! es_vacio_binario(b).
  El tiempo de ejecución es O(log n) en promedio, donde `n' es la cantidad de
  elementos de `b'.
 */
info_t mayor(binario_t b);

/*
  Remueve el nodo en el que se localiza el elemento mayor de `b'
  (libera la memoria  asignada al nodo, pero no la del elemento).
  Devuelve `b'.
  Precondición: ! es_vacio_binario(b).
  El tiempo de ejecución es O(log n) en promedio, donde `n' es la cantidad de
  elementos de `b'.
 */
binario_t remover_mayor(binario_t b);

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
binario_t remover_de_binario(const char *t, binario_t b);

/*
  Libera la memoria asociada a `b' y todos sus elementos.
  Devuelve `b'.
  El tiempo de ejecución es O(n), donde `n' es la cantidad de elementos de `b'.
 */
binario_t liberar_binario(binario_t b);

/*
  Devuelve `true' si y sólo si `b' es vacío (no tiene elementos).
  El tiempo de ejecución es O(1).
 */
bool es_vacio_binario(binario_t b);

/*
  Devuelve `true' si y sólo si cada nodo de `b' cumple la condición de balanceo
  AVL. El árbol vacío cumple la condición.
  Un nodo cumple la condición de balanceo AVL si el valor absoluto de la
  diferencia de las alturas de sus subárboles izquierdo y derecho en menor o
  igual a 1.
  Cada nodo se puede visitar una sola vez.
  El tiempo de ejecución es O(n), donde `n' es la cantidad de elementos de `b'.
 */
bool es_AVL(binario_t b);

/*
  Devuelve el elemento asociado a la raíz de `b'.
  Precondición: ! es_vacio_binario(b).
  El tiempo de ejecución es O(1).
 */
info_t raiz(binario_t b);

/*
  Devuelve el subárbol izquierdo de `b'.
  Precondición: ! es_vacio_binario(b).
  El tiempo de ejecución es O(1).
 */
binario_t izquierdo(binario_t b);

/*
  Devuelve el subárbol derecho de `b'.
  Precondición: ! es_vacio_binario(b).
  El tiempo de ejecución es O(1).
 */
binario_t derecho(binario_t b);

/*
  Devuelve el subárbol que tiene como raíz al nodo con el elemento cuyo dato de
  texto es `t'.
  Si `t' no pertenece a `b', devuelve el árbol vacío.
  El tiempo de ejecución es O(log n) en promedio, donde `n' es la cantidad de
  elementos de `b'.
 */
binario_t buscar_subarbol(const char *t, binario_t b);

/*
  Devuelve la altura de `b'.
  La altura de un árbol vacío es 0.
  El tiempo de ejecución es O(n), donde `n' es la cantidad de elementos de `b'.
 */
nat altura_binario(binario_t b);

/*
  Devuelve la cantidad de elementos de `b'.
  El tiempo de ejecución es O(n), donde `n' es la cantidad de elementos de `b'.
 */
nat cantidad_binario(binario_t b);

/*
  Devuelve la suma de los datos numéricos de los últimos `i' elementos
  (considerados según la propiedad de orden de los árboles binario_t)
  de `b' cuyos datos numéericos sean pares.
  Si en `b' hay menos de `i' elementos con dato numérico par devuelve la
  suma de todos los datos numéricos pares de `b'.
  No se deben crear estructuras auxiliares.
  No se deben visitar nuevos nodos después que se hayan encontrado los
  `i' elementos.
  El tiempo de ejecución es O(n), donde `n' es la cantidad de elementos de `b'.
 */
int suma_ultimos_pares(nat i, binario_t b);

/*
  Devuelve una cadena_t con los elementos de `b' en orden lexicográfico
  creciente según sus datos de texto.
  La cadena_t devuelta no comparte memoria con `b'.
  El tiempo de ejecución es O(n), donde `n' es la cantidad de elementos de `b'.
 */
cadena_t linealizacion(binario_t b);

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
binario_t cadena_a_binario(cadena_t cad);

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
binario_t menores(int clave, binario_t b);

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
bool es_camino(cadena_t c, binario_t b);

/*
  Devuelve una cadena_t con los elementos del nivel `l' de 'b'.
  La raíz es el nivel 1.
  La cadena_t resultado debe estar ordenada de manera creciente según las
  frases de sus elementos.
  La cadena_t devuelta no comparte memoria con `b'.
 */
cadena_t nivel_en_binario(nat l, binario_t b);

/*
  Imprime los elementos de `b', uno por línea, en orden descendente de la
  propiedad de orden de los árboles `binario_t'.
  Antes del elemento imprime una cantidad de guiones igual a su nivel.
  El elemento se imprime según la especificación dada en `info_a_texto'.
  El nivel de la raíz es 0.
  Antes de terminar, se debe imprimir un fin de linea.
  Si es_vacio_binario(b) sólo se imprime el fin de línea.
  El tiempo de ejecución es O(n . log n) en promedio, donde `n' es la cantidad
  de elementos de `b'.
 */
void imprimir_binario(binario_t b);

#endif
