/*
  Módulo de definición de `cola_avls_t'.

  `cola_avls_t' es una estructura lineal con comportamiento FIFO cuyos
   elementos son de tipo `avl'.

  Laboratorio de Programación 2.
  InCo-FIng-UDELAR
 */

#ifndef _COLA_AVLS_H
#define _COLA_AVLS_H

#include "avl.h"

// Representación de `cola_avls_t'.
// Se debe definir en cola_avls.cpp
struct rep_cola_avls;
// Declaración del tipo `cola_avls_t'
typedef struct rep_cola_avls *cola_avls_t;

/*  Devuelve una cola_avls_t vacía (sin elementos). */
cola_avls_t crear_cola_avls();

/* Encola `avl' en `c'. */
void encolar(avl_t b, cola_avls_t &c);

/*
  Remueve de `c' el elemento que está en el frente.
  NO libera la memoria del elemento removido.
  Si es_vacia_cola_binarios(c) no hace nada.
 */
void desencolar(cola_avls_t &c);

/* Libera la memoria asignada a `c', pero NO la de sus elementos. */
void liberar_cola_avls(cola_avls_t &c);

/* Devuelve `true' si y sólo si `c' es vacía (no tiene elementos). */
bool es_vacia_cola_avls(cola_avls_t c);

/*
  Devuelve el elemento que está en el frente de `c'.
  Precondición: ! es_vacia_cola_binarios(c);
 */
avl_t frente(cola_avls_t c);

#endif
