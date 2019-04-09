/*
  Módulo de definición de `uso_cadena_s'.

  Se definen funciones sobre cadenas.

  Laboratorio de Programación 2.
  InCo-FIng-UDELAR
 */

#ifndef _USO_CADENA_H
#define _USO_CADENA_H

#include "cadena.h"
#include "info.h"

/*
  Devuelve `true' si y sólo si en `cad' hay un elemento cuyo dato numérico es
  `i'.
  El tiempo de ejecución es O(n), siendo `n' la cantidad de elementos en la
  cadena.
 */
bool pertenece(int i, cadena_t cad);

/*
   Devuelve la cantidad de elementos de `cad'.
  El tiempo de ejecución es O(n), siendo `n' la cantidad de elementos en la
  cadena.
 */
nat longitud(cadena_t cad);

/*
  Devuelve `true' si y sólo si `cad' está ordenada de forma no decreciente
  (= creciente de manera no estricta) según los datos numéricos de sus
  elementos.
  Si es_vacia_cadena (cad) devuelve `true'.
  El tiempo de ejecución es O(n), siendo `n' la cantidad de elementos en la
  cadena.
 */
bool esta_ordenada(cadena_t cad);

/*
  Devuelve una cadena_t con todos los elementos de `c1' y `c2' ordenada de
  manera  creciente segun sus datos numéricos.
  Si hay elementos cuyos datos numéricos son iguales los elementos de `c1'
  quedan antes de los de `c2'.
  La cadena_t resultado no comparte memoria ni con `c1' ni con `c2'.
  Precondición: esta_ordenada (c1) y esta_ordenada (c2).
  El tiempo de ejecución es O(n), siendo `n' la cantidad de elementos en la
  cadena resultado.
 */
cadena_t mezcla(cadena_t c1, cadena_t c2);

/*
  Devuelve el resultado de concatenar `c2' después de `c1'.
  La cadena_t resultado no comparte memoria ni con `c1' ni con `c2'.
  El tiempo de ejecución es O(n), siendo `n' la cantidad de elementos en la
  cadena resultado.
 */
cadena_t concatenar(cadena_t c1, cadena_t c2);

/*
  Se ordena `cad' de manera creciente según los datos numéricos de sus
  elementos.
  Devuelve `cad'.
  No se debe obtener ni devolver memoria de manera dinámica.
  Si es_vacia_cadena (cad) no hace nada.
  El tiempo de ejecución es O(n^2), siendo `n' la cantidad de elementos en
  la cadena resultado.
 */
cadena_t ordenar(cadena_t cad);

/*
  Cambia todas las ocurrencias de `original' por `nuevo' en los elementos
   de `cad'. No debe quedar memoria inaccesible.
  Devuelve `cad'.
  El tiempo de ejecución es O(n), siendo `n' la cantidad de elementos en
  la cadena resultado.
 */
cadena_t cambiar_todos(int original, int nuevo, cadena_t cad);

#endif
