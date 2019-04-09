/*
  Módulo principal de la tarea 3.

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

#include "include/binario.h"
#include "include/cadena.h"
#include "include/info.h"
#include "include/uso_cadena.h"

#include <stdio.h>
#include <string.h>
#include <time.h>

#define MAX_PALABRA 32
#define MAX_LINEA 256

/*
 Convierte `n' a string.
 */
char *int_a_texto(int n) {
  char *res = new char[11];
  sprintf(res, "%d", n);
  return res;
}

/*
  Lee una cadena_t de info_t desde la entrada estándar. Después de cada elemento
  hay un espacio en blanco. Termina con un punto.
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

// programa principal
int main() {
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

      // operaciones de binario

    } else if (!strcmp(nom_comando, "insertar_en_binario")) {
      info_t info = leer_info(MAX_PALABRA);
      if (!es_vacio_binario(buscar_subarbol(frase_info(info), b))) {
        printf("Ya estaba la frase en 'b'.\n");
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

  return 0;
}
