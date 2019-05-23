/*
  Módulo principal de la tarea 4.

Intérprete de comandos para probar los módulos.

Están creados una cadena_t `cad', un localizador_t `loc' y un binario_t `b'.

Cada comando tiene un nombre y una secuencia (posiblemente vacía) de parámetros.
Se asume que los comandos están bien formados. Esto implica que:
- el nombre es uno de los descritos más abajo;
- la cantidad y tipo de los parámetros cumplen con lo requerido.

Si un parámetro debe ser de tipo info_t su formato cumple con lo descrito en
`info_a_texto' del módulo `info', con el agregado de que no puede incluir el
 símbolo ')'.

Si un parámetro es una secuencia de elementos de algún tipo termina con un
espacio en blanco y un punto.


El comando
Fin
termina el programa

El comando
# comentario
imprime comentario.

El comando
reiniciar
libera la memoria asignada a `cad' y `b' y los vuelve a crear.

  Laboratorio de Programación 2.
  InCo-FIng-UDELAR
*/

#include "include/pila.h"
#include "include/avl.h"
#include "include/cola_avls.h"
#include "include/iterador.h"
#include "include/conjunto.h"
#include "include/binario.h"
#include "include/cadena.h"
#include "include/info.h"
#include "include/uso_cadena.h"

#include <stdio.h>
#include <string.h>
#include <time.h>

#define MAX_PALABRA 32
#define MAX_LINEA 256
#define MAX_PILA 10

/*
 Convierte `n' a string.
 */
char *int_a_texto(int n) {
  char *res = new char[11];
  sprintf(res, "%d", n);
  return res;
}

/*
  Lee una cadena_t de info_t desde la entrada estándar.
  Después de cada elemento hay un espacio en blanco.
  Termina con un punto.
 */
cadena_t leer_cadena() {
  cadena_t res = crear_cadena();
  info_t info = leer_info(MAX_PALABRA);
  while (es_valida_info(info)) {
    insertar_al_final(info, res);
    info = leer_info(MAX_PALABRA);
  }
  liberar_info(info);
  return res;
} // leer_cadena

struct arreglo_tope {
  info_t *datos;
  nat tope;
};

/*
  Lee una secuencia de info_t desde la entrada estándar y las devuelve en un
  arreglo con tope.
  Primero lee la cantidad máxima que puede tener.
  Después de cada elemento hay un espacio en blanco.
  La secuencia termina con un punto.
  Lee hasta que encuentra el punto o se llegue a la cantidad máxima.
  La secuencia está ordenada de manera creciente estricta  según los datos
  numéricos.
  Ajusta el valor del tope.
 */
arreglo_tope leer_arreglo_ordenado() {
  nat n;
  arreglo_tope res;
  scanf("%d", &n);
  res.tope = 0;
  if (n == 0) {
    res.datos = NULL;
  } else {
    res.datos = new info_t[n];
    info_t info = leer_info(MAX_PALABRA);
    while (es_valida_info(info) && (res.tope < n)) {
      res.datos[res.tope] = info;
      res.tope++;
      info = leer_info(MAX_PALABRA);
    }
    if (res.tope <= n)
      liberar_info(info);
  }

  bool esta_ordenado = true;
  nat cont = 0;
  while (esta_ordenado && cont + 1 < res.tope) {
    if (numero_info(res.datos[cont]) < numero_info(res.datos[cont + 1]))
      cont++;
    else
      esta_ordenado = false;
  }
  if (!esta_ordenado) {
    printf("Secuencia no ordenada. ");
    for (nat i = 0; i < res.tope; i++)
      liberar_info(res.datos[i]);
    delete[] res.datos;
    res.tope = 0;
  }
  return res;
}

bool esta_ordenada_por_frase(cadena_t cad) {
  bool res = true;
  if (!es_vacia_cadena(cad)) {
    localizador_t loc = inicio_cadena(cad);
    while (res && es_localizador(siguiente(loc, cad))) {
      localizador_t sig_loc = siguiente(loc, cad);
      if (strcmp(frase_info(info_cadena(loc, cad)),
                 frase_info(info_cadena(sig_loc, cad))) >= 0)
        res = false;
      else
        loc = siguiente(loc, cad);
    }
  }
  return res;
} // esta_ordenada_por_frase

/* Inserta subárboles. */
void ins_sub_arbol(nat dato, nat inc, binario_t &a) {
  a = insertar_en_binario(crear_info(dato, int_a_texto(dato)), a);
  if (inc > 1) {
    inc >>= 1;
    ins_sub_arbol(dato - inc, inc, a);
    ins_sub_arbol(dato + inc, inc, a);
  }
} // ins_sub_arbol

// Libera la memoria de `cb' y de sus binarios. //
void destruir_cola_avls(cola_avls_t cavl) {
  while (!es_vacia_cola_avls(cavl)) {
    avl_t f = frente(cavl);
    desencolar(cavl);
    liberar_avl(f);
  }
  liberar_cola_avls(cavl);
} // destruir_cola_avls

// programa principal
int main() {

  pila_t p = crear_pila(MAX_PILA);
  avl_t avl = crear_avl();
  cola_avls_t cavl = crear_cola_avls();
  iterador_t it = crear_iterador();
  conjunto_t conj = crear_conjunto();

  binario_t b = crear_binario();

  cadena_t cad = crear_cadena();
  localizador_t loc = inicio_cadena(cad); // no válido porque cad es vacía

  char resto_linea[MAX_LINEA];

  int cont_comandos = 0;
  bool salir = false;
  while (!salir) {
    // mostrar el prompt
    cont_comandos++;
    printf("%u>", cont_comandos);

    // leer el comando
    char nom_comando[MAX_PALABRA];
    scanf("%s", nom_comando);

    // procesar el comando
    if (!strcmp(nom_comando, "Fin")) {
      salir = true;
      printf("Fin.\n");
      // comentario
    } else if (!strcmp(nom_comando, "#")) {
      scanf("%[^\n]", resto_linea);
      printf("# %s.\n", resto_linea);

      // operaciones de pila

    } else if (!strcmp(nom_comando, "apilar")) {
      if (es_llena_pila(p))
        printf("p está llena.\n");
      else {
        int num;
        scanf("%d", &num);
        apilar(num, p);
        printf("Apilado.\n");
      }

    } else if (!strcmp(nom_comando, "cima")) {
      if (es_vacia_pila(p))
        printf("p está vacía.\n");
      else {
        printf("%d.\n", cima(p));
      }

    } else if (!strcmp(nom_comando, "desapilar")) {
      if (es_vacia_pila(p))
        printf("p está vacía.\n");
      else {
        desapilar(p);
        printf("Desapilado.\n");
      }

    } else if (!strcmp(nom_comando, "es_vacia_pila")) {
      printf("p %s vacia.\n", es_vacia_pila(p) ? "está" : "NO está");

    } else if (!strcmp(nom_comando, "es_llena_pila")) {
      printf("p %s llena.\n", es_llena_pila(p) ? "está" : "NO está");

      // operaciones de avl
    } else if (!strcmp(nom_comando, "es_vacio_avl")) {
      printf("%s.\n", es_vacio_avl(avl) ? "Vacio" : "No vacío");

    } else if (!strcmp(nom_comando, "insertar_en_avl")) {
      info_t info = leer_info(MAX_PALABRA);
      if (!es_vacio_avl(buscar_en_avl(numero_info(info), avl))) {
        printf("Ya estaba el número en 'b'.\n");
        liberar_info(info);
      } else {
        insertar_en_avl(info, avl);
        printf("Insertado.\n");
      }

    } else if (!strcmp(nom_comando, "buscar_en_avl")) {
      int num;
      scanf("%d", &num);
      avl_t sub = buscar_en_avl(num, avl);
      if (es_vacio_avl(sub))
        printf("sub es vacío.\n");
      else {
        char *txt_info;
        txt_info = info_a_texto(raiz_avl(sub));
        printf("%s\n", txt_info);
        delete[] txt_info;
        avl_t hijo;
        hijo = izq_avl(sub);
        if (es_vacio_avl(hijo))
          printf(" | ");
        else {
          txt_info = info_a_texto(raiz_avl(hijo));
          printf("%s", txt_info);
          delete[] txt_info;
        }
        printf(" - ");
        hijo = der_avl(sub);
        if (es_vacio_avl(hijo))
          printf(" | ");
        else {
          txt_info = info_a_texto(raiz_avl(hijo));
          printf("%s", txt_info);
          delete[] txt_info;
        }
        printf("\n");
      }

    } else if (!strcmp(nom_comando, "raiz_avl")) {
      if (es_vacio_avl(avl))
        printf("avl es vacío.\n");
      else {
        info_t info = raiz_avl(avl);
        char *txt_info = info_a_texto(info);
        printf("%s\n", txt_info);
        delete[] txt_info;
      }

    } else if (!strcmp(nom_comando, "izq_avl")) {
      if (es_vacio_avl(avl))
        printf("avl es vacío.\n");
      else {
        avl_t sub_izq = izq_avl(avl);
        if (es_vacio_avl(sub_izq))
          printf("Izquierdo es vacío\n");
        else {
          info_t info = raiz_avl(sub_izq);
          char *txt_info = info_a_texto(info);
          printf("%s\n", txt_info);
          delete[] txt_info;
        }
      }

    } else if (!strcmp(nom_comando, "der_avl")) {
      if (es_vacio_avl(avl))
        printf("avl es vacío.\n");
      else {
        avl_t sub_der = der_avl(avl);
        if (es_vacio_avl(sub_der))
          printf("Derecho es vacío\n");
        else {
          info_t info = raiz_avl(sub_der);
          char *txt_info = info_a_texto(info);
          printf("%s\n", txt_info);
          delete[] txt_info;
        }
      }

    } else if (!strcmp(nom_comando, "cantidad_en_avl")) {
      printf("Cantidad en avl: %d.\n", cantidad_en_avl(avl));

    } else if (!strcmp(nom_comando, "altura_de_avl")) {
      printf("Altura de avl: %d.\n", altura_de_avl(avl));

    } else if (!strcmp(nom_comando, "en_orden_avl")) {
      info_t *en_orden = en_orden_avl(avl);
      for (nat i = 0; i < cantidad_en_avl(avl); i++)
        printf("%d ", numero_info(en_orden[i]));
      printf("\n");
      delete[] en_orden;

    } else if (!strcmp(nom_comando, "arreglo_a_avl")) {
      arreglo_tope infos = leer_arreglo_ordenado();
      printf("\n");
      if (infos.tope > 0) {
        avl_t a2a = arreglo_a_avl(infos.datos, infos.tope);
        imprimir_avl(a2a);
        liberar_avl(a2a);
        delete[] infos.datos;
      }

    } else if (!strcmp(nom_comando, "avl_min")) {
      nat h;
      scanf("%d", &h);
      avl_t min = avl_min(h);
      printf("\n");
      imprimir_avl(min);
      printf("Cantidad: %d.\n", cantidad_en_avl(min));
      liberar_avl(min);

    } else if (!strcmp(nom_comando, "imprimir_avl")) {
      printf("\n");
      imprimir_avl(avl);

      // operaciones de cola_avl

    } else if (!strcmp(nom_comando, "encolar")) {
      avl_t nuevo = crear_avl();
      cadena_t infos = leer_cadena();
      localizador_t loc = inicio_cadena(infos);
      while (localizador_en_cadena(loc, infos)) {
        info_t info = copia_info(info_cadena(loc, infos));
        insertar_en_avl(info, nuevo);
        loc = siguiente(loc, infos);
      }
      encolar(nuevo, cavl);
      printf("Encolado.\n");
      liberar_cadena(infos);

    } else if (!strcmp(nom_comando, "frente")) {
      if (es_vacia_cola_avls(cavl))
        printf("cavl está vacía.\n");
      else {
        avl_t f = frente(cavl);
        if (es_vacio_avl(f))
          printf("Avl vacío.\n");
        else {
          info_t info = raiz_avl(f);
          char *txt_info = info_a_texto(info);
          printf("%s\n", txt_info);
          delete[] txt_info;
        }
      }

    } else if (!strcmp(nom_comando, "desencolar")) {
      if (es_vacia_cola_avls(cavl))
        printf("cb está vacía.\n");
      else {
        avl_t f = frente(cavl);
        desencolar(cavl);
        liberar_avl(f);
        printf("Desencolado.\n");
      }

    } else if (!strcmp(nom_comando, "es_vacia_cola_avls")) {
      printf("cavl %s vacia.\n", es_vacia_cola_avls(cavl) ? "está" : "NO está");

      // operaciones de iterador

    } else if (!strcmp(nom_comando, "agregar_a_iterador")) {
      info_t info = leer_info(MAX_PALABRA);
      agregar_a_iterador(info, it);
      printf("Agregando.\n");
      liberar_info(info);

    } else if (!strcmp(nom_comando, "reiniciar_iterador")) {
      reiniciar_iterador(it);
      printf("Reiniciado.\n");

    } else if (!strcmp(nom_comando, "avanzar_iterador")) {
      avanzar_iterador(it);
      printf("Avanzando.\n");

    } else if (!strcmp(nom_comando, "actual_en_iterador")) {
      if (!esta_definida_actual(it))
        printf("Actual no definida.\n");
      else {
        char *txt_info = info_a_texto(actual_en_iterador(it));
        printf("%s\n", txt_info);
        delete[] txt_info;
      }

    } else if (!strcmp(nom_comando, "hay_siguiente_en_iterador")) {
      if (!esta_definida_actual(it))
        printf("Actual no definida.\n");
      else
        printf("%s siguiente.\n",
               hay_siguiente_en_iterador(it) ? "Hay" : "No hay");

    } else if (!strcmp(nom_comando, "esta_definida_actual")) {
      printf("Actual de it %s definida.\n",
             esta_definida_actual(it) ? "está" : "NO está");

    } else if (!strcmp(nom_comando, "bloquear_iterador")) {
      bloquear_iterador(it);
      printf("Iterador bloqueado.\n");

      // operaciones de conjunto

    } else if (!strcmp(nom_comando, "es_vacio_conjunto")) {
      printf("%s.\n", es_vacio_conjunto(conj) ? "Vacio" : "No vacío");

    } else if (!strcmp(nom_comando, "pertenece_conjunto")) {
      info_t info = leer_info(MAX_PALABRA);
      printf("%s.\n",
             pertenece_conjunto(info, conj) ? "Pertenece" : "No pertenece");
      liberar_info(info);

    } else if (!strcmp(nom_comando, "singleton")) {
      info_t info = leer_info(MAX_PALABRA);
      liberar_conjunto(conj);
      conj = singleton(info);
      printf("Creado el singleton.\n");

    } else if (!strcmp(nom_comando, "arreglo_a_conjunto")) {
      arreglo_tope infos = leer_arreglo_ordenado();
      if (infos.tope > 0) {
        liberar_conjunto(conj);
        conj = arreglo_a_conjunto(infos.datos, infos.tope);
      }
      printf("Arreglo a conjunto con %d elementos.\n", infos.tope);
      delete[] infos.datos;

    } else if (!strcmp(nom_comando, "union_conjunto")) {
      arreglo_tope infos = leer_arreglo_ordenado();
      if (infos.tope > 0) {
        conjunto_t b = arreglo_a_conjunto(infos.datos, infos.tope);
        conjunto_t alias = conj;
        conj = union_conjunto(alias, b);
        liberar_conjunto(alias);
        liberar_conjunto(b);
      }
      printf("Union.\n");
      delete[] infos.datos;

    } else if (!strcmp(nom_comando, "diferencia")) {
      arreglo_tope infos = leer_arreglo_ordenado();
      if (infos.tope > 0) {
        conjunto_t b = arreglo_a_conjunto(infos.datos, infos.tope);
        conjunto_t alias = conj;
        conj = diferencia(alias, b);
        liberar_conjunto(alias);
        liberar_conjunto(b);
      }
      printf("Diferencia.\n");
      delete[] infos.datos;

    } else if (!strcmp(nom_comando, "iterador_conjunto")) {
      iterador_t it_c = iterador_conjunto(conj);
      reiniciar_iterador(it_c);
      if (!esta_definida_actual(it_c)) {
        printf("No hay elementos en el conjunto.\n");
      } else {
        do {
          char *txt_info = info_a_texto(actual_en_iterador(it_c));
          printf("%s ", txt_info);
          delete[] txt_info;
          avanzar_iterador(it_c);
        } while (esta_definida_actual(it_c));
        printf("\n");
      }
      liberar_iterador(it_c);

      // operaciones de binario

    } else if (!strcmp(nom_comando, "insertar_en_binario")) {
      info_t info = leer_info(MAX_PALABRA);
      if (!es_vacio_binario(buscar_subarbol(frase_info(info), b))) {
        printf("Ya estaba la frase en 'b'.\n");
        liberar_info(info);
      } else {
        b = insertar_en_binario(info, b);
        printf("Insertado.\n");
      }

    } else if (!strcmp(nom_comando, "mayor")) {
      if (es_vacio_binario(b))
        printf("b es vacío.\n");
      else {
        char *txt_info = info_a_texto(mayor(b));
        printf("%s\n", txt_info);
        delete[] txt_info;
      }

    } else if (!strcmp(nom_comando, "remover_mayor")) {
      if (es_vacio_binario(b))
        printf("b es vacío.\n");
      else {
        info_t info = mayor(b);
        b = remover_mayor(b);
        liberar_info(info);
        printf("Removido el mayor.\n");
      }

    } else if (!strcmp(nom_comando, "remover_de_binario")) {
      char *txt = new char[MAX_PALABRA];
      scanf("%s", txt);
      if (es_vacio_binario(buscar_subarbol(txt, b))) {
        printf("No estaba la frase en 'b'.\n");
      } else {
        b = remover_de_binario(txt, b);
        printf("Removido.\n");
      }
      delete[] txt;

    } else if (!strcmp(nom_comando, "es_vacio_binario")) {
      printf("%s.\n", es_vacio_binario(b) ? "Vacio" : "No vacío");

    } else if (!strcmp(nom_comando, "es_AVL")) {
      printf("%s.\n", es_AVL(b) ? "AVL" : "No AVL");

    } else if (!strcmp(nom_comando, "raiz")) {
      if (es_vacio_binario(b))
        printf("b es vacío.\n");
      else {
        info_t info = raiz(b);
        char *txt_info = info_a_texto(info);
        printf("%s\n", txt_info);
        delete[] txt_info;
      }

    } else if (!strcmp(nom_comando, "izquierdo")) {
      if (es_vacio_binario(b))
        printf("b es vacío.\n");
      else
        imprimir_binario(izquierdo(b));

    } else if (!strcmp(nom_comando, "derecho")) {
      if (es_vacio_binario(b))
        printf("b es vacío.\n");
      else
        imprimir_binario(derecho(b));

    } else if (!strcmp(nom_comando, "buscar_subarbol")) {
      char *txt = new char[MAX_PALABRA];
      scanf("%s", txt);
      binario_t sub = buscar_subarbol(txt, b);
      if (es_vacio_binario(sub))
        printf("sub es vacío.\n");
      else {
        char *txt_info = info_a_texto(raiz(sub));
        printf("%s\n", txt_info);
        delete[] txt_info;
      }
      delete[] txt;

    } else if (!strcmp(nom_comando, "altura_binario")) {
      printf("%d.\n", altura_binario(b));

    } else if (!strcmp(nom_comando, "cantidad_binario")) {
      printf("%d.\n", cantidad_binario(b));

    } else if (!strcmp(nom_comando, "suma_ultimos_pares")) {
      nat i;
      scanf("%u", &i);
      printf("%d\n", suma_ultimos_pares(i, b));

    } else if (!strcmp(nom_comando, "linealizacion")) {
      cadena_t lineal = linealizacion(b);
      imprimir_cadena(lineal);
      liberar_cadena(lineal);

    } else if (!strcmp(nom_comando, "cadena_a_binario")) {
      cadena_t ord = leer_cadena();
      if (!esta_ordenada_por_frase(ord)) {
        printf("Cadena no ordenada.\n");
      } else {
        liberar_binario(b);
        b = cadena_a_binario(ord);
        imprimir_binario(b);
      }
      liberar_cadena(ord);

    } else if (!strcmp(nom_comando, "menores")) {
      nat clave;
      scanf("%u", &clave);
      binario_t filtro = menores(clave, b);
      imprimir_binario(filtro);
      liberar_binario(filtro);

    } else if (!strcmp(nom_comando, "es_camino")) {
      cadena_t camino = leer_cadena();
      printf("%s camino.\n", es_camino(camino, b) ? "Es" : "NO es");
      liberar_cadena(camino);

    } else if (!strcmp(nom_comando, "nivel_en_binario")) {
      nat l;
      scanf("%u", &l);
      if (l == 0) {
        printf("l = 0.\n");
      } else {
        cadena_t nivel = nivel_en_binario(l, b);
        imprimir_cadena(nivel);
        liberar_cadena(nivel);
      }

    } else if (!strcmp(nom_comando, "imprimir_binario")) {
      imprimir_binario(b);

      // operaciones de cadena

    } else if (!strcmp(nom_comando, "insertar_al_final")) {
      info_t info = leer_info(MAX_LINEA);
      cad = insertar_al_final(info, cad);
      printf("Insertado al final.\n");

    } else if (!strcmp(nom_comando, "insertar_antes")) {
      info_t info = leer_info(MAX_LINEA);
      if (!localizador_en_cadena(loc, cad)) {
        liberar_info(info);
        printf("Localizador no válido.\n");
      } else {
        cad = insertar_antes(info, loc, cad);
        printf("Insertado antes de loc.\n");
      }

    } else if (!strcmp(nom_comando, "insertar_segmento_despues")) {
      if (!es_vacia_cadena(cad) && !localizador_en_cadena(loc, cad))
        printf("Localizador no válido.\n");
      else {
        cadena_t sgm = leer_cadena();
        cad = insertar_segmento_despues(sgm, loc, cad);
        sgm = liberar_cadena(sgm);
        printf("Segmento insertado después de loc.\n");
      }

    } else if (!strcmp(nom_comando, "copiar_segmento")) {
      nat k1, k2;
      scanf("%u %u", &k1, &k2);
      nat cantidad = longitud(cad);
      if (!es_vacia_cadena(cad) && ((k1 < 1) || (k2 < k1) || (k2 > cantidad)))
        printf("Posiciones fuera de rango.\n");
      else {
        localizador_t loc_desde = kesimo(k1, cad);
        localizador_t loc_hasta = kesimo(k2, cad);
        cadena_t sgm = copiar_segmento(loc_desde, loc_hasta, cad);
        imprimir_cadena(sgm);
        sgm = liberar_cadena(sgm);
      }

    } else if (!strcmp(nom_comando, "cortar_segmento")) {
      nat k1, k2;
      scanf("%u %u", &k1, &k2);
      nat cantidad = longitud(cad);
      if (!es_vacia_cadena(cad) && ((k1 < 1) || (k2 < k1) || (k2 > cantidad)))
        printf("Posiciones fuera de rango.\n");
      else {
        localizador_t loc_desde = kesimo(k1, cad);
        localizador_t loc_hasta = kesimo(k2, cad);
        cad = cortar_segmento(loc_desde, loc_hasta, cad);
        imprimir_cadena(cad);
      }

    } else if (!strcmp(nom_comando, "remover_de_cadena")) {
      if (!localizador_en_cadena(loc, cad))
        printf("Localizador no válido.\n");
      else {
        cad = remover_de_cadena(loc, cad);
        printf("Removido.\n");
      }

    } else if (!strcmp(nom_comando, "es_localizador")) {
      printf("loc%s válido.\n", es_localizador(loc) ? "" : " no");

    } else if (!strcmp(nom_comando, "es_vacia_cadena")) {
      printf("cad%s.\n", es_vacia_cadena(cad) ? " vacia" : " no vacia");

    } else if (!strcmp(nom_comando, "es_final_cadena")) {
      printf("loc%s es final de cad.\n",
             es_final_cadena(loc, cad) ? "" : " no");

    } else if (!strcmp(nom_comando, "es_inicio_cadena")) {
      printf("loc%s es incio de cad.\n",
             es_inicio_cadena(loc, cad) ? "" : " no");

    } else if (!strcmp(nom_comando, "localizador_en_cadena")) {
      printf("loc%s pertenece a cad.\n",
             localizador_en_cadena(loc, cad) ? "" : " no");

    } else if (!strcmp(nom_comando, "precede_en_cadena")) {
      nat k1;
      scanf("%u", &k1);
      nat cantidad = longitud(cad);
      if ((k1 < 1) || (k1 > cantidad))
        printf("Posición fuera de rango.\n");
      else if (!localizador_en_cadena(loc, cad))
        printf("loc no pertenece a cad.\n");
      else {
        localizador_t loc1 = kesimo(k1, cad);
        printf("loc1%s precede a loc.\n",
               precede_en_cadena(loc1, loc, cad) ? "" : " no");
      }

    } else if (!strcmp(nom_comando, "inicio_cadena")) {
      if (es_vacia_cadena(cad))
        printf("Cadena vacía.\n");
      else {
        loc = inicio_cadena(cad);
        printf("loc al inicio.\n");
      }

    } else if (!strcmp(nom_comando, "final_cadena")) {
      if (es_vacia_cadena(cad))
        printf("Cadena vacía.\n");
      else {
        loc = final_cadena(cad);
        printf("loc al final.\n");
      }

    } else if (!strcmp(nom_comando, "kesimo")) {
      nat k;
      scanf("%u", &k);
      loc = kesimo(k, cad);
      printf("loc en la posición %u.\n", k);

    } else if (!strcmp(nom_comando, "siguiente")) {
      if (!localizador_en_cadena(loc, cad))
        printf("Localizador no válido.\n");
      else {
        loc = siguiente(loc, cad);
        printf("loc al siguiente.\n");
      }

    } else if (!strcmp(nom_comando, "anterior")) {
      if (!localizador_en_cadena(loc, cad))
        printf("Localizador no válido.\n");
      else {
        loc = anterior(loc, cad);
        printf("loc al anterior.\n");
      }

    } else if (!strcmp(nom_comando, "menor_en_cadena")) {
      if (!localizador_en_cadena(loc, cad))
        printf("Localizador no válido.\n");
      else {
        loc = menor_en_cadena(loc, cad);
        printf("loc avanzó hasta el menor.\n");
      }

    } else if (!strcmp(nom_comando, "siguiente_clave")) {
      if (!es_vacia_cadena(cad) && !localizador_en_cadena(loc, cad))
        printf("Localizador no válido.\n");
      else {
        int clave;
        scanf("%d", &clave);
        loc = siguiente_clave(clave, loc, cad);
        printf("loc avanzó buscando %d.\n", clave);
      }

    } else if (!strcmp(nom_comando, "info_cadena")) {
      if (!localizador_en_cadena(loc, cad))
        printf("Localizador no válido.\n");
      else {
        char *txt_info = info_a_texto(info_cadena(loc, cad));
        printf("%s\n", txt_info);
        delete[] txt_info;
      }

    } else if (!strcmp(nom_comando, "cambiar_en_cadena")) {
      if (!localizador_en_cadena(loc, cad))
        printf("Localizador no válido.\n");
      else {
        info_t nueva_info = leer_info(MAX_PALABRA);
        info_t anterior_info = info_cadena(loc, cad);
        cad = cambiar_en_cadena(nueva_info, loc, cad);
        liberar_info(anterior_info);
        printf("Cambio.\n");
      }

    } else if (!strcmp(nom_comando, "intercambiar")) {
      nat k1, k2;
      scanf("%u %u", &k1, &k2);
      nat cantidad = longitud(cad);
      if ((k1 < 1) || (k1 > cantidad) || (k2 < 1) || (k2 > cantidad))
        printf("Posición fuera de rango.\n");
      else {
        localizador_t loc1 = kesimo(k1, cad);
        localizador_t loc2 = kesimo(k2, cad);
        cad = intercambiar(loc1, loc2, cad);
        printf("Intercambio.\n");
      }

    } else if (!strcmp(nom_comando, "imprimir_cadena")) {
      imprimir_cadena(cad);

      // operaciones de uso_cadena

    } else if (!strcmp(nom_comando, "pertenece")) {
      int i;
      scanf("%d", &i);
      printf("%d%s pertenece a cad.\n", i, pertenece(i, cad) ? "" : " no");

    } else if (!strcmp(nom_comando, "longitud")) {
      printf("Longitud: %u\n", longitud(cad));

    } else if (!strcmp(nom_comando, "esta_ordenada")) {
      printf("cad%s.\n", esta_ordenada(cad) ? " ordenada" : " no ordenada");

    } else if (!strcmp(nom_comando, "mezcla")) {
      cadena_t otra = leer_cadena();
      if (!esta_ordenada(cad) || !esta_ordenada(otra))
        printf("Cadena no ordenada.\n");
      else {
        cadena_t mzc = mezcla(cad, otra);
        imprimir_cadena(mzc);
        mzc = liberar_cadena(mzc);
      }
      otra = liberar_cadena(otra);

    } else if (!strcmp(nom_comando, "concatenar")) {
      cadena_t otra = leer_cadena();
      cadena_t conc = concatenar(cad, otra);
      imprimir_cadena(conc);
      conc = liberar_cadena(conc);
      otra = liberar_cadena(otra);

    } else if (!strcmp(nom_comando, "ordenar")) {
      cad = ordenar(cad);
      printf("Ordenada.\n");

    } else if (!strcmp(nom_comando, "cambiar_todos")) {
      int original, nuevo;
      scanf("%d %d", &original, &nuevo);
      cad = cambiar_todos(original, nuevo, cad);
      printf("Cambiados.\n");

    } else if (!strcmp(nom_comando, "reiniciar")) {
      cad = liberar_cadena(cad);
      cad = crear_cadena();
      loc = inicio_cadena(cad);
      b = liberar_binario(b);
      b = crear_binario();
      liberar_pila(p);
      p = crear_pila(MAX_PILA);
      liberar_avl(avl);
      avl = crear_avl();
      destruir_cola_avls(cavl);
      cavl = crear_cola_avls();
      liberar_iterador(it);
      it = crear_iterador();
      liberar_conjunto(conj);
      conj = crear_conjunto();
      printf("Estructuras reiniciadas.\n");

      // Comandos para tests de tiempo

    } else if (!strcmp(nom_comando, "tiempo_suma_ultimos_pares")) {
      nat min, max, i, iter, timeout;
      scanf("%d %d %d %d %d", &min, &max, &i, &iter, &timeout);
      printf("\n Construyendo el árbol. \n");
      binario_t a = crear_binario();
      for (nat i = max; i > min; i--)
        a = insertar_en_binario(crear_info(i, int_a_texto(i)), a);
      printf(" Obteniendo suma ultimos pares. \n");

      clock_t tm = clock();
      for (nat i = 0; i < iter; i++)
        suma_ultimos_pares(i, a);
      tm = clock() - tm;
      float tiempo = ((float)tm) / CLOCKS_PER_SEC;
      if (tiempo > timeout)
        printf("ERROR, tiempo excedido; %.1f > %d \n", tiempo, timeout);

      printf(" Liberando binario. \n");
      liberar_binario(a);

    } else if (!strcmp(nom_comando, "tiempo_es_AVL")) {
      nat raiz, dos_h, iter, timeout;
      scanf("%d %d %d %d", &raiz, &dos_h, &iter, &timeout);
      printf("\n Construyendo el árbol. \n");
      binario_t a = crear_binario();
      ins_sub_arbol(raiz, dos_h, a);
      printf(" Evaluando si es AVL. \n");

      clock_t tm = clock();
      for (nat i = 0; i < iter; i++)
        es_AVL(a);
      tm = clock() - tm;
      float tiempo = ((float)tm) / CLOCKS_PER_SEC;
      if (tiempo > timeout)
        printf("ERROR, tiempo excedido: %.1f > %d \n", tiempo, timeout);

      printf(" Liberando binario. \n");
      liberar_binario(a);

    } else {
      printf("Comando no reconocido.\n");
    } // if
    fgets(resto_linea, MAX_LINEA + 1, stdin);
  } // while

  cad = liberar_cadena(cad);
  b = liberar_binario(b);
  liberar_pila(p);
  liberar_avl(avl);
  destruir_cola_avls(cavl);
  liberar_iterador(it);
  liberar_conjunto(conj);
  return 0;
}
