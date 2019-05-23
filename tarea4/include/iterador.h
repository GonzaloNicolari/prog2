/*
  Módulo de definición de `iterador_t'.

  Estructura para recorrer una colección de info_t.
  Tiene implcícita una posición actual.

  Se puede bloquear para que no se le puedan agregar más elementos.
  Al crearse no está bloqueado.

  Laboratorio de Programación 2.
  InCo-FIng-UDELAR
 */

#ifndef _ITERADOR_H
#define _ITERADOR_H

#include "info.h"

// Representación de `iterador_t',
// Se debe definir en iterador.cpp
struct rep_iterador;
// Declaración del tipo `iterador_t'
typedef struct rep_iterador *iterador_t;

/*
  Crea un iterador_t vacío (sin elementos) cuya posición actual no está
  definida.
  No está bloqueado.
  El tiempo de ejecución es O(1).
 */
iterador_t crear_iterador();

/*
  Bloquea `iter'.
  No se podrán agregar más elementos.
  El tiempo de ejecución es O(1).
 */
void bloquear_iterador(iterador_t &iter);

/*
  Agrega una copia de `info' al final de `iter' si y solo si `iter' no ha sido
  bloqueado.
  No se modifica la posición actual.
  El tiempo de ejecución es O(1).
 */
void agregar_a_iterador(info_t info, iterador_t &iter);

/*
  Mueve la posición actual al primero.
  Si en `iter' no hay elementos no hace nada.
  El tiempo de ejecución es O(1).
 */
void reiniciar_iterador(iterador_t &iter);

/*
  Avanza la posición actual hacia el siguiente.
  Si ! hay_siguiente_en_iter(iter) la posición actual queda indefinida;
  Si la posición actual no está definida no hace nada.
  El tiempo de ejecución es O(1).
 */
void avanzar_iterador(iterador_t &iter);

/*
  Devuelve el elemento de la posición actual.
  Precondición: esta_definida_actual(iter).
  El tiempo de ejecución es O(1).
 */
info_t actual_en_iterador(iterador_t &iter);

/*
  Devuelve `true' si y sólo si en `iter' hay un elemento siguiente al de la
  posición actual.
  Precondición: esta_definida_actual(iter).
  El tiempo de ejecución es O(1).
 */
bool hay_siguiente_en_iterador(iterador_t iter);

/*
  Devuelve `true' si y sólo si la posición actual de `iter' está definida.
  El tiempo de ejecución es O(1).
 */
bool esta_definida_actual(iterador_t iter);

/*
  Libera la memoria asignada a `iter' y a sus elementos.
  El tiempo de ejecución es O(n), donde `n' es la cantidad de elementos de
  `iter'.
 */
void liberar_iterador(iterador_t &iter);

#endif
