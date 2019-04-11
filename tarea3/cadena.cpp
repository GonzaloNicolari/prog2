/* 46450368			- 48579580 */
// Nicolás Saliba	- Gonzalo Nicolari.
// Instituto de Computación - Facultad de Ingeniería, Laboratorio de Programación 2.

#include "../include/cadena.h"
#include "../include/info.h"

#include <stdio.h>
#include <string.h>
#include <assert.h>

struct nodo {
	nodo	*anterior;
	info_t	dato;
	nodo	*siguiente;
};

struct rep_cadena {
	nodo	*inicio;
	nodo	*final;
};

cadena_t crear_cadena() {

	rep_cadena *nueva	= new rep_cadena;
	nueva->inicio		= NULL;
	nueva->final		= NULL;
	return nueva;
}

cadena_t insertar_al_final(info_t i, cadena_t cad) {

	nodo *nuevo			= new nodo;
	nuevo->dato			= i;
	nuevo->siguiente	= NULL;
	nuevo->anterior		= cad->final;

	if (cad->final == NULL) {
		assert(cad->inicio == NULL);
		cad->inicio = nuevo;
	} else {
		assert(cad->inicio != NULL);
		cad->final->siguiente = nuevo;
	}
	cad->final = nuevo;
	return cad;
}

cadena_t insertar_antes(info_t i, localizador_t loc, cadena_t cad) {

	nodo *nuevo			= new nodo;
	nuevo->dato			= i;
	nuevo->siguiente	= NULL;
	nuevo->anterior		= NULL;

	if (cad->inicio == NULL) cad->inicio = nuevo;
	else if (es_inicio_cadena(loc, cad)) {
		cad->inicio			= nuevo;
		nuevo->siguiente	= loc;
		loc->anterior		= nuevo;
	} else {
		nuevo->anterior				= anterior(loc, cad);
		nuevo->siguiente			= loc;
		loc->anterior->siguiente	= nuevo;
		loc->anterior				= nuevo;
	}
	return cad;
}

cadena_t insertar_segmento_despues(cadena_t &sgm, localizador_t loc, cadena_t cad) {

	assert(es_vacia_cadena(cad) || localizador_en_cadena(loc, cad));
	if (es_vacia_cadena(cad)) {
		cad->inicio	= sgm->inicio;
		cad->final	= sgm->final;
	} else {
		if (!es_vacia_cadena(sgm)) {
			sgm->inicio->anterior	= loc;
			sgm->final->siguiente	= loc->siguiente;

			if (es_final_cadena(loc, cad)) cad->final = sgm->final;
			else loc->siguiente->anterior = sgm->final;

			loc->siguiente = sgm->inicio;
		}
	}
	sgm->inicio = sgm->final = NULL;
	return cad;
}

cadena_t copiar_segmento(localizador_t desde, localizador_t hasta, cadena_t cad) {

	cadena_t res = crear_cadena();
	if (!es_vacia_cadena(cad)) {
		localizador_t locCad = desde;
		while (locCad != hasta) {
			res = insertar_al_final(copia_info(locCad->dato), res);
			locCad = siguiente(locCad, cad);
		}
		res = insertar_al_final(copia_info(hasta->dato), res);
	}
	return res;
}

cadena_t cortar_segmento(localizador_t desde, localizador_t hasta, cadena_t cad) {

	// Si es vacìa.
	if (es_vacia_cadena(cad)) return cad;

	// Si solo se corta un elemento.
	else if (desde == hasta) return remover_de_cadena(desde, cad);

	// Si el segmento a cortar es toda la cadena.
	else if (es_inicio_cadena(desde, cad) && es_final_cadena(hasta, cad)) return liberar_cadena(cad);

	// Si el segmento a cortar está al inicio.
	else if (es_inicio_cadena(desde, cad)) {
		cad->inicio				= siguiente(hasta, cad);
		cad->inicio->anterior	= NULL;
		localizador_t loc		= desde;
		while (loc != cad->inicio) {
			nodo *a_borrar	= loc;
			loc				= siguiente(loc, cad);
			liberar_info(a_borrar->dato);
			delete(a_borrar);
		}
		loc = NULL;
		return cad;

	} else if (es_final_cadena(hasta, cad)) {
		// Si el segmento a cortar està al final.
		cad->final				= anterior(desde, cad);
		cad->final->siguiente	= NULL;
		localizador_t loc		= desde;
		while (es_localizador(loc)) {
			nodo *a_borrar	= loc;
			loc				= siguiente(loc, cad);
			liberar_info(a_borrar->dato);
			delete(a_borrar);
		}
		return cad;
	}

	// Si el segmento està al medio.
	localizador_t loc1	= anterior(desde, cad);
	localizador_t loc2	= siguiente(hasta, cad);
	loc1->siguiente		= loc2;
	loc2->anterior		= loc1;
	localizador_t loc	= desde;
	while (es_localizador(loc)) {
		nodo *a_borrar	= loc;
		cad->inicio		= NULL;
		cad->final		= NULL;
		loc				= siguiente(loc, cad);
		liberar_info(a_borrar->dato);
		delete(a_borrar);
	}
	return cad;
}

cadena_t remover_de_cadena(localizador_t &loc, cadena_t cad) {

	nodo *a_borrar = loc;

	if (es_inicio_cadena(loc, cad) && es_final_cadena(loc, cad)) {
		// Si es el único elemento.
		cad->inicio	= NULL;
		cad->final	= NULL;
	} else if (es_inicio_cadena(loc, cad)) {
		// Si está al inicio.
		cad->inicio				= siguiente(loc, cad);
		cad->inicio->anterior	= NULL;
	} else if (es_final_cadena(loc, cad)) {
		// Si está al final.
		cad->final				= anterior(loc, cad);
		cad->final->siguiente	= NULL;
	} else {
		// Si está en el medio.
		loc->anterior->siguiente	= siguiente(loc, cad);
		loc->siguiente->anterior	= anterior(loc, cad);
	}

	// Libero memoria.
	liberar_info(a_borrar->dato);
	delete(a_borrar);
	loc = NULL;
	return cad;
}


cadena_t liberar_cadena(cadena_t cad) {

	nodo *a_borrar;
	while (cad->inicio != NULL) {
		a_borrar	= cad->inicio;
		cad->inicio	= cad->inicio->siguiente;
		liberar_info(a_borrar->dato);
		delete(a_borrar);
	}
	delete cad;
	return cad;
}

bool es_localizador(localizador_t loc) {
	return loc != NULL;
}

bool es_vacia_cadena(cadena_t cad) {
	return (cad->inicio == NULL) && (cad->final == NULL);
}

bool es_final_cadena(localizador_t loc, cadena_t cad) {
	return (!es_vacia_cadena(cad) && localizador_en_cadena(loc, cad) && loc->siguiente == NULL);
}

bool es_inicio_cadena(localizador_t loc, cadena_t cad) {
	return (!es_vacia_cadena(cad) && localizador_en_cadena(loc, cad) && loc->anterior == NULL);
}

bool localizador_en_cadena(localizador_t loc, cadena_t cad) {

	localizador_t locMove = inicio_cadena(cad);
	while (es_localizador(locMove) && (locMove != loc))
		locMove = siguiente(locMove, cad);
	return es_localizador(locMove);
}

bool precede_en_cadena(localizador_t loc1, localizador_t loc2, cadena_t cad) {

	if (es_vacia_cadena(cad))	return false;
	else if (loc1 == loc2)		return true;
	else {
		localizador_t locAux = loc2;
		while (es_localizador(locAux) && (locAux != loc1))
			locAux = anterior(locAux, cad);
		return locAux == loc1;
	}
}

localizador_t inicio_cadena(cadena_t cad) {

	localizador_t loc;
	if (es_vacia_cadena(cad))
		loc = NULL;
	else
		loc = cad->inicio;
	return loc;
}

localizador_t final_cadena(cadena_t cad) {

	localizador_t loc;
	if (es_vacia_cadena(cad))
		loc = NULL;
	else
		loc = cad->final;
	return loc;
}	

localizador_t kesimo(nat k, cadena_t cad) {

	localizador_t loc	= NULL;
	if (!es_vacia_cadena(cad) && (k > 0)) {
		nat i	= 1;
		loc		= inicio_cadena(cad);

		while (i < k && es_localizador(loc)) {
			loc = siguiente(loc, cad);
			i++;
		}
	}
	return loc;
}

localizador_t siguiente(localizador_t loc, cadena_t cad) {

	if (!es_final_cadena(loc, cad)) return loc->siguiente;
	else return NULL;
}

localizador_t anterior(localizador_t loc, cadena_t cad) {

	if (!es_inicio_cadena(loc, cad)) return loc->anterior;
	else return NULL;
}

localizador_t menor_en_cadena(localizador_t loc, cadena_t cad) {

	localizador_t res		= loc;
	localizador_t locMove	= loc;
	while (es_localizador(locMove)) {
		if (numero_info(info_cadena(locMove, cad)) < numero_info(info_cadena(res, cad))) res = locMove;
		locMove = siguiente(locMove, cad);
	}
	return res;
}

localizador_t siguiente_clave(int clave, localizador_t loc, cadena_t cad) {

	localizador_t res = loc;
	if(es_vacia_cadena(cad))
		res = NULL;
	else
		while (es_localizador(res) && numero_info(info_cadena(res, cad)) != clave)
			res = siguiente(res, cad);
	return res;
}

info_t info_cadena(localizador_t loc, cadena_t cad) {

	info_t info = loc->dato;
	return info;
}

cadena_t cambiar_en_cadena(info_t i, localizador_t loc, cadena_t cad) {

	loc->dato = i;
	return cad;
}

cadena_t intercambiar(localizador_t loc1, localizador_t loc2, cadena_t cad) {

	if (loc1 != loc2) {
		info_t info = copia_info(loc2->dato);
		liberar_info(loc2->dato);
		loc2->dato	= loc1->dato;
		loc1->dato	= info;
	}
	return cad;
}


void imprimir_cadena(cadena_t cad) {

	if (!es_vacia_cadena(cad)) {
		localizador_t loc = inicio_cadena(cad);
		while (loc != NULL) {
			char *info = info_a_texto(info_cadena(loc, cad));
			printf("%s", info);
			loc = siguiente(loc, cad);
			delete[] info;
		}
	}
	printf("\n");
}
