/*
  Módulo de definición de `pila_t'.

  `pila_t' es una estructura lineal acotada con comportamiento LIFO cuyos
   elementos son enteros.

  La cantidad de elementos que puede mantener se establece en el parámetro
  de `crear_pila'.


  Laboratorio de Programación 2.
  InCo-FIng-UDELAR
 */

#ifndef _PILA_H
#define _PILA_H

// Representación de `pila_t'.
// Se debe definir en pila.cpp.
struct rep_pila;
// Declaración del tipo `pila_t'
typedef struct rep_pila *pila_t;

/*
  Devuelve una pila_t vacía (sin elementos) que puede tener hasta `tamanio'
  elementos.
 */
pila_t crear_pila(int tamanio);

/*
  Apila `num' en `p'.
  Si es_llena_pila(p) no hace nada.
 */
void apilar(int num, pila_t &p);

/*
  Remueve de `p' el elemento que está en la cima.
  Si es_vacia_pila(p) no hace nada.
 */
void desapilar(pila_t &p);

/* Libera la memoria asignada a `p'. */
void liberar_pila(pila_t &p);

/* Devuelve `true' si y sólo si `p' es vacía (no tiene elementos). */
bool es_vacia_pila(pila_t p);

/*
  Devuelve `true' si y sólo si la cantidad de elementos en `p' es `tamanio'
  (siendo `tamanio' el valor del parámetro con que fue creada `p').
 */
bool es_llena_pila(pila_t p);

/*
  Devuelve el elemento que está en la cima de `p'.
  Precondición: ! es_vacia_pila(p);
 */
int cima(pila_t p);

#endif
