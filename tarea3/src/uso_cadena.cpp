/* 46450368			- 48579580 */
// Nicolás Saliba	- Gonzalo Nicolari.
// Instituto de Computación - Facultad de Ingeniería, Laboratorio de Programación 2.

#include "../include/info.h"
#include "../include/uso_cadena.h"

#include <string.h> // strlen, strcpy, strcmp, strcat

bool pertenece(int i, cadena_t cad) {

	localizador_t loc	= siguiente_clave(i, inicio_cadena(cad), cad);
	bool belongs		= false;
	while (es_localizador(loc) && !belongs) {
		belongs	= numero_info(info_cadena(loc, cad)) == i;
		loc		= siguiente_clave(i, inicio_cadena(cad), cad);
	}
	loc = NULL;
	return belongs;
}

nat longitud(cadena_t cad) {

	nat i = 0;
	localizador_t loc = inicio_cadena(cad);
	while (es_localizador(loc)) {
		i++;
		loc = siguiente(loc, cad);
	}
	return i;
}

bool esta_ordenada(cadena_t cad) {

	if (es_vacia_cadena(cad)) return true;
	else {
		localizador_t loc1	= inicio_cadena(cad);
		localizador_t loc2	= siguiente(loc1, cad);
		bool ordenada		= true;

		while (es_localizador(loc2) && ordenada) {
			ordenada	= numero_info(info_cadena(loc1, cad)) <= numero_info(info_cadena(loc2, cad));
			loc1		= loc2;
			loc2		= siguiente(loc2, cad);
		}
		return ordenada;
	}
}

/*
cadena_t mezcla(cadena_t c1, cadena_t c2) {
	cadena_t res	= concatenar(c1, c2);
	res				= ordenar(res);
	return res;
}
*/

cadena_t mezcla(cadena_t c1, cadena_t c2) {

	cadena_t res = crear_cadena();
	if (!es_vacia_cadena(c1) || !es_vacia_cadena(c2)) {

		localizador_t loc1	= inicio_cadena(c1);
		localizador_t loc2	= inicio_cadena(c2);

		while (es_localizador(loc1) || es_localizador(loc2)) {
			if (es_localizador(loc1) && es_localizador(loc2)) {
				if (numero_info(info_cadena(loc1, c1)) <= numero_info(info_cadena(loc2, c2))) {
					res		= insertar_al_final(copia_info(info_cadena(loc1, c1)), res);
					loc1	= siguiente(loc1, c1);
				} else {
					res		= insertar_al_final(copia_info(info_cadena(loc2, c2)), res);
					loc2	= siguiente(loc2, c2);
				}
			} else  if (es_localizador(loc1))
				while (es_localizador(loc1)) {
					res		= insertar_al_final(copia_info(info_cadena(loc1, c1)), res);
					loc1	= siguiente(loc1, c1);
				}
			else if (es_localizador(loc2))
				while (es_localizador(loc2)) {
					res		= insertar_al_final(copia_info(info_cadena(loc2, c2)), res);
					loc2	= siguiente(loc2, c2);
				}
		}
		loc1	= NULL;
		loc2	= NULL;
	}
	return res;
}

cadena_t concatenar(cadena_t c1, cadena_t c2) {

	cadena_t res		= crear_cadena();
	localizador_t loc	= inicio_cadena(c1);

	while (es_localizador(loc)) {
		insertar_al_final(copia_info(info_cadena(loc, c1)), res);
		loc = siguiente(loc, c1);
	}

	loc = inicio_cadena(c2);

	while (es_localizador(loc)) {
		insertar_al_final(copia_info(info_cadena(loc, c2)), res);
		loc = siguiente(loc, c2);
	}
	return res;
}

cadena_t ordenar(cadena_t cad) {

	if (!es_vacia_cadena(cad)) {
		localizador_t loc = inicio_cadena(cad);
		while (es_localizador(loc)) {
			cad	= intercambiar(menor_en_cadena(loc, cad), loc, cad);
			loc	= siguiente (loc, cad);
		}
	}
	return cad;
}

cadena_t cambiar_todos(int original, int nuevo, cadena_t cad) {

	if (pertenece(original, cad)) {
		// Obtengo la primera ocurrencia de original en cad.
		localizador_t loc = siguiente_clave(original, inicio_cadena(cad), cad);

		while (es_localizador(loc)) {
			info_t dato	= info_cadena(loc, cad);
			char *frase	= new char[sizeof(frase_info(dato))];
			strcpy(frase, frase_info(dato));
			info_t newData = crear_info(nuevo,frase);

			// Cambio los elementos.
			insertar_antes(newData, loc, cad);
			localizador_t locAux	= loc;
			loc						= anterior(loc, cad);
			remover_de_cadena(locAux, cad);

			loc = siguiente_clave(original, loc, cad);
		}
	}
	return cad;
}