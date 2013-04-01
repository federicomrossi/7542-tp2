/* ******************************************************************
 * ******************************************************************
 * DIJKSTRA - LIBRERÍA DE FUNCIONES 
 * ******************************************************************
 * ******************************************************************
 * 
 * Librería de funciones relacionadas con el algoritmo de caminos 
 * mínimos de Dijkstra. 
 */ 


#ifndef DIJKSTRA_H
#define DIJKSTRA_H



/* ******************************************************************
 * INCLUSIÓN DE LIBRERIAS Y TADS EXTERNOS
 * *****************************************************************/

#include "lista.h"
#include "grafo.h"


/* ******************************************************************
 * DECLARACIÓN DE LOS TIPOS DE DATOS
 * *****************************************************************/





/* ******************************************************************
 * FUNCIONES DE LA LIBRERIA
 * *****************************************************************/

// 
lista_t* dijkstra_caminos_minimos(grafo_t *grafo, 
	grafo_dato_t *origen, 
	int criterio_seleccion(lista_dato_t, lista_dato_t));

// 
lista_t* dijkstra_obtener_camino(lista_t* lista_resultados, 
	grafo_dato_t *destino);

//
void dijkstra_destruir_resultados(lista_t* lista_resultados);

#endif
