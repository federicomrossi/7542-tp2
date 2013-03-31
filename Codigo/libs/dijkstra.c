

#include <stdio.h>
#include "dijkstra.h"


/* ******************************************************************
 * DECLARACIÓN DE LOS TIPOS DE DATOS
 * *****************************************************************/


typedef struct _dijkstra_nodo_t dijkstra_nodo_t;



/* ******************************************************************
 * INCLUSIÓN DE LIBRERIAS Y TADS EXTERNOS
 * *****************************************************************/

// TAD Lista
#define LISTA_DATO_T
typedef void* lista_dato_t;

// TAD Cola
#define COLA_DATO_T
typedef void* cola_dato_t;




/* ******************************************************************
 * DEFINICIÓN DE LOS TIPOS DE DATOS
 * *****************************************************************/

struct _dijkstra_nodo_t {
	grafo_dato_t *dato;			// Puntero al dato del vértice
	grafo_dato_t *nodo_previo	// Puntero al dato del vértice previo
								// para llegar al vértice actual por
								// camino mínimo
	int peso_camino;			// Peso mínimo del camino hasta llegar
};



/* ******************************************************************
 * FUNCIONES DE LA LIBRERIA
 * *****************************************************************/

// 
cola_t* dijkstra_caminos_minimos(grafo_t *grafo, 
	grafo_dato_t *origen, void criterio_seleccion())
{
	// Variables auxiliares de procesamiento
	dijkstra_nodo_t *V, *Vi, *A = NULL;
	// Cola de nodos marcados
	cola_t* M = cola_crear();
	// Cola de nodos no marcados
	cola_t* NM = cola_crear();
	// Cola auxiliar
	cola_t* CA = cola_crear();


	// Obtenemos los vértices del grafo
	list_t* listaDeVertices = lista_crear();
	grafo_obtener_vertices(grafo_t *grafo, grafo_dato_t *listaDeVertices);

	// Iteramos sobre la lista de vértices
	lista_iter_t* iter = lista_iter_crear(listaDeVertices);
	grafo_dato_t* vertice;

	while(!lista_iter_al_final(iter))
	{
		// Creamos un nodo para cada vértice
		lista_iter_ver_actual(iter, &vertice);
		dijkstra_nodo_t* nodo = (dijkstra_nodo_t*) malloc(sizeof(dijkstra_nodo_t));
		if(!nodo) return NULL;

		// Seteamos datos iniciales del nodo
		nodo->dato = vertice;
		nodo->nodo_previo = NULL;
		nodo->peso_camino = INFINITO;
		
		// Enviamos a la cola de no marcados (NM) a los nodos
		// de los vértices que no son el origen
		if(vertice != origen)
			cola_encolar(NM, nodo);
		else
		{
			cola_encolar(M, nodo);
			V = nodo;
		}

		lista_iter_avanzar(iter);
	}

	lista_iter_destruir(iter);
	lista_destruir(listaDeVertices, NULL);



	return NULL;
}

// 
lista_t* dijkstra_obtener_camino(cola_t nodos, 
	grafo_dato_t *destino)
{
	return NULL;
}