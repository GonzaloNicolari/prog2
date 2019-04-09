/*
  Módulo de definición de `cadena_t'.

  Lista doblemente enlazada de elementos de tipo `info_t', con cabezal con
  punteros al inicio y al final.

  Laboratorio de Programación 2.
  InCo-FIng-UDELAR
 */

#ifndef _CADENA_H
#define _CADENA_H

#include "info.h"

typedef unsigned int nat;

/*
  Las variables de tipo localizador_t permiten acceder a los elementos en las
  estructuras que los contienen. En el caso de una cadena enlazada esas
  variables son punteros a los nodos.
 */
// struct nodo es la representación de `localizador', definida en `cadena.cpp'.
typedef struct nodo *localizador_t;

// struct rep_cadena es la representación de `cadena_t', definida en
// `cadena.cpp'.
typedef struct rep_cadena *cadena_t;

/*
  Devuelve la cadena_t vacía (sin elementos).
  El tiempo de ejecución es O(1).
 */
cadena_t crear_cadena();

/*
  Se inserta `i' como último elemento de `cad'.
  Devuelve `cad'.
  Si es_vacia_cadena (cad) `i' se inserta como único elemento de `cad'.
  El tiempo de ejecución es O(1).
 */
cadena_t insertar_al_final(info_t i, cadena_t cad);

/*
  Se inserta `i' como un nuevo elemento inmediatamente antes de `loc'.
  Devuelve `cad'.
  Precondición: localizador_en_cadena(loc, cad).
  El tiempo de ejecución es O(1).
 */
cadena_t insertar_antes(info_t i, localizador_t loc, cadena_t cad);

/*
  Se inserta la cadena_t `sgm' inmediatamente después de `loc' en `cad',
  manteniendo los elementos originales y el orden relativo entre ellos.
  Devuelve `cad'.
  No se debe obtener memoria (los nodos de `sgm' pasan a ser parte de `cad').
  Al terminar, `sgm' queda vacía.
  Si es_vacia_cadena(cad) `loc' es ignorado y el segmento queda insertado.
  Precondición: es_vacia_cadena(cad) o localizador_en_cadena(loc, cad).
  El tiempo de ejecución es O(1).
 */
cadena_t insertar_segmento_despues(cadena_t &sgm, localizador_t loc,
                                   cadena_t cad);

/*
  Devuelve una cadena_t con los elementos de `cad' que se encuentran entre
  `desde' y `hasta', incluidos.
  La cadena_t resultado no comparte memoria con `cad'.
  Si es_vacia_cadena(cad) devuelve la cadena_t vacia.
  Precondición: es_vacia_cadena(cad) o precede_en_cadena(desde, hasta, cad).
  El tiempo de ejecución es O(n), siendo `n' la cantidad de elementos en la
  cadena resultado.
  El tiempo de ejecución es O(n), siendo `n' la cantidad de elementos en la
  cadena resultado.
 */
cadena_t copiar_segmento(localizador_t desde, localizador_t hasta,
                         cadena_t cad);

/*
  Remueve de `cad' los elementos que se encuentran  entre `desde' y `hasta',
  incluidos y libera la memoria que tenían asignada y la de sus nodos.
  Devuelve `cad'.
  Si es_vacia_cadena(cad) devuelve la cadena_t vacía.
  Precondición: es_vacia_cadena(cad) o precede_en_cadena(desde, hasta, cad).
  El tiempo de ejecución es O(n), siendo `n' la cantidad de elementos en la
  cadena resultado.
 */
cadena_t cortar_segmento(localizador_t desde, localizador_t hasta,
                         cadena_t cad);

/*
  Se quita el elemento al que se accede desde `loc' y se libera la memoria
  asignada al mismo y al nodo apuntado por el localizador.
  Devuelve `cad'.
  El valor de `loc' queda indeterminado.
  Precondición: localizador_en_cadena(loc, cad).
  El tiempo de ejecución es O(1).
 */
cadena_t remover_de_cadena(localizador_t &loc, cadena_t cad);

/*
  Libera la memoria asignada a `cad' y la de todos sus elementos.
  Devuelve `cad'.
  El tiempo de ejecución es O(n), siendo `n' la cantidad de elementos en la
  cadena.
 */
cadena_t liberar_cadena(cadena_t cad);

/*
  Devuelve `true' si y sólo si `loc' es un localizador_t válido.
  En cadenas enlazadas un localizador_t no es válido si es `NULL'.
  El tiempo de ejecución es O(1).
*/
bool es_localizador(localizador_t loc);

/*
  Devuelve `true' si y sólo si `cad' es vacía (no tiene elementos).
  El tiempo de ejecución es O(1).
 */
bool es_vacia_cadena(cadena_t cad);

/*
  Devuelve `true' si y sólo si con `loc' se accede al último elemento de `cad'.
  Si es_vacia_cadena (cad) devuelve `false'.
  El tiempo de ejecución es O(1).
 */
bool es_final_cadena(localizador_t loc, cadena_t cad);

/*
  Devuelve `true' si y sólo si con `loc' se accede al primer elemento de `cad'.
  Si es_vacia_cadena (cad) devuelve `false'.
  El tiempo de ejecución es O(1).
 */
bool es_inicio_cadena(localizador_t loc, cadena_t cad);

/*
  Devuelve `true' si y sólo si con `loc' se accede a un elemento de `cad',
  (o sea, si apunta a un nodo de `cad').
  Si es_vacia_cadena (cad) devuelve `false'.
  El tiempo de ejecución es O(n), siendo `n' la cantidad de elementos en la
  cadena.
 */
bool localizador_en_cadena(localizador_t loc, cadena_t cad);

/*
  Devuelve `true' si y sólo si `loc1' es igual o precede a `loc2` en `cad`.
  Si es_vacia_cadena (cad) devuelve `false'.
  El tiempo de ejecución es O(n), siendo `n' la cantidad de elementos en la
  cadena.
 */
bool precede_en_cadena(localizador_t loc1, localizador_t loc2, cadena_t cad);

/*
  Devuelve el localizador_t con el que se accede al inicio de `cad`.
  Si es_vacia_cadena(cad) devuelve un localizador_t no válido.
  El tiempo de ejecución es O(1).
 */
localizador_t inicio_cadena(cadena_t cad);

/*
  Devuelve el localizador_t con el que se accede al final de `cad'.
  Si es_vacia_cadena(cad) devuelve un localizador_t no válido.
  El tiempo de ejecución es O(1).
 */
localizador_t final_cadena(cadena_t cad);

/*
  Devuelve el localizador_t con el que se accede al k-esimo elemento de `cad'.
  Si `k' es 0 o mayor a la cantidad de elementos de `cad' devuelve un localizdor
  no válido.
  El tiempo de ejecución es O(n), siendo `n' la cantidad de elementos en la
  cadena.
 */
localizador_t kesimo(nat k, cadena_t cad);

/*
  Devuelve el localizador_t con el que se accede al elemento de `cad'
  inmediatamente siguiente a `loc'.
  Si es_final_cadena(loc, cad) devuelve un localizador_t no válido.
  Precondición: localizador_en_cadena(loc, cad).
  El tiempo de ejecución es O(1).
 */
localizador_t siguiente(localizador_t loc, cadena_t cad);

/*
  Devuelve el localizador_t con el que se accede al elemento de `cad'
  inmediatamente anterior a `loc'.
  Si es_inicio_cadena(loc, cad) devuelve un localizador_t no válido.
  Precondición: localizador_en_cadena(loc, cad).
  El tiempo de ejecución es O(1).
 */
localizador_t anterior(localizador_t loc, cadena_t cad);

/*
  Devuelve el localizador_t con el que se accede al elemento cuyo dato numérico
  es el menor en el segmento que va desde `loc' hasta el final_cadena(cad).
  Si hay más de un elemento cuyo valor es el menor el resultado accede al que
  precede a los otros.
  Precondición: localizador_en_cadena(loc, cad).
  El tiempo de ejecución es O(n), siendo `n' la cantidad de elementos en la
  cadena.
 */
localizador_t menor_en_cadena(localizador_t loc, cadena_t cad);

/*
  Devuelve el primer localizador_t con el que se accede a un elemento cuyo dato
  numérico es igual a `clave', buscando desde `loc' (inclusive) hacia el final
  de `cad'.
  Si no se encuentra o `cad' es vacía devuelve un localizador_t no válido.
  Precondición: es_vacia_cadena(cad) o localizador_en_cadena(loc, cad).
  El tiempo de ejecución es O(n), siendo `n' la cantidad de elementos en la
  cadena.
 */
localizador_t siguiente_clave(int clave, localizador_t loc, cadena_t cad);

/*
  Devuelve el elemento de `cad' al que se accede con `loc'.
  Precondición: localizador_en_cadena(loc, cad).
  El tiempo de ejecución es O(1).
 */
info_t info_cadena(localizador_t loc, cadena_t cad);

/*
  Sustituye con `i' el elemento de `cad' al que se accede con `loc'.
  Devuelve `cad'.
  No destruye el elemento al que antes se accedía con `loc'.
  Precondición: localizador_en_cadena(loc, cad).
  El tiempo de ejecución es O(1).
 */
cadena_t cambiar_en_cadena(info_t i, localizador_t loc, cadena_t cad);

/*
  Intercambia los elementos a los que se accede con `loc1' y `loc2'.
  `loc1' y `loc2' mantienen su relación de precedencia.
  Devuelve `cad'.
  Precondición:
    localizador_en_cadena (loc1, cad)
  y localizador_en_cadena (loc2, cad).
  El tiempo de ejecución es O(1).
 */
cadena_t intercambiar(localizador_t loc1, localizador_t loc2, cadena_t cad);

/*
  Imprime los elementos de `cad` de la siguiente forma:
  (dn de pos1,fr de pos1)(dn de pos2,fr de pos2) ...
  donce `dn` es el dato numérico y `fr` es la frase.
  Antes de terminar, se debe imprimir un fin de linea.
  Si es_vacia_cadena(cad) sólo se imprime el fin de línea.
  El tiempo de ejecución es O(n), siendo `n' la cantidad de elementos en la
  cadena.
 */
void imprimir_cadena(cadena_t cad);

#endif
