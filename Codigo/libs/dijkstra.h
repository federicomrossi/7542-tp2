 
#ifndef DIJKSTRA_H
#define DIJKSTRA_H


/* ******************************************************************
 * INCLUSIÓN DE LIBRERIAS Y TADS EXTERNOS
 * *****************************************************************/

#include "lista.h"
#include "cola.h"
#include "grafo.h"


/* ******************************************************************
 * DECLARACIÓN DE LOS TIPOS DE DATOS
 * *****************************************************************/


typedef struct _dijkstra_nodo_t dijkstra_nodo_t;



/* ******************************************************************
 * FUNCIONES DE LA LIBRERIA
 * *****************************************************************/

// 
cola_t* dijkstra_caminos_minimos(grafo_t *grafo, 
	grafo_dato_t *origen, void criterio_seleccion());

// 
lista_t* dijkstra_obtener_camino(cola_t nodos, 
	grafo_dato_t *destino);

#endif
