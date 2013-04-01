/* ******************************************************************
 * ******************************************************************
 * DIJKSTRA - LIBRERÍA DE FUNCIONES 
 * ******************************************************************
 * ******************************************************************
 * 
 * Librería de funciones relacionadas con el algoritmo de caminos 
 * mínimos de Dijkstra. 
 */ 


#include <stdio.h>
#include <stdlib.h>
#include "dijkstra.h"



/* ******************************************************************
 * CONSTANTES
 * *****************************************************************/

const int INFINITO = 1e9;



/* ******************************************************************
 * DECLARACIÓN DE LOS TIPOS DE DATOS
 * *****************************************************************/


typedef struct _dijkstra_nodo_t dijkstra_nodo_t;



/* ******************************************************************
 * INCLUSIÓN DE LIBRERIAS Y TADS EXTERNOS
 * *****************************************************************/

// TAD Cola
#define COLA_DATO_T
typedef dijkstra_nodo_t* cola_dato_t;
#include "cola.h"



/* ******************************************************************
 * DEFINICIÓN DE LOS TIPOS DE DATOS
 * *****************************************************************/

struct _dijkstra_nodo_t {
	lista_dato_t dato;				// Puntero al dato del vértice
	dijkstra_nodo_t *nodo_previo;	// Puntero al dato del vértice 
									// previo para llegar al vértice  
									// actual por camino mínimo
	int peso_camino;				// Peso mínimo del camino hasta 
									// llegar
};



/* ******************************************************************
 * FUNCIONES AUXILIARES
 * *****************************************************************/

// Función que mueve los datos almacenados en una cola a una lista de
// elementos de tipo no definido
lista_t* cola_a_lista(cola_t* cola)
{
	lista_t* lista = lista_crear();
	if(!lista) return NULL;
	cola_dato_t aux;

	while(!cola_esta_vacia(cola))
	{
		cola_desencolar(cola, &aux);
		lista_insertar_primero(lista, (lista_dato_t*) aux);
	}

	return lista;
}



/* ******************************************************************
 * FUNCIONES DE LA LIBRERIA
 * *****************************************************************/

// 
lista_t* dijkstra_caminos_minimos(grafo_t *grafo, grafo_dato_t *origen, 
	int criterio_seleccion(lista_dato_t, lista_dato_t))
{
	// Variables auxiliares de procesamiento
	dijkstra_nodo_t *a = NULL, *Vi;
	int menor_peso = INFINITO;

	// Cola de nodos marcados
	cola_t* M = cola_crear();
	// Cola de nodos no marcados
	cola_t* NM = cola_crear();
	// Cola auxiliar
	cola_t* CA = cola_crear();


	// (Paso 1) Obtenemos los vértices del grafo
	int i, cantidad_vertices = grafo_cantidad_vertices(grafo);
	grafo_dato_t arregloDeVertices[cantidad_vertices];
	grafo_obtener_vertices(grafo, arregloDeVertices);

	// Iteramos sobre el arreglo de vértices
	for(i = 0; i < cantidad_vertices; i++)
	{
		// Creamos un nodo para cada vértice
		dijkstra_nodo_t* nodo = (dijkstra_nodo_t*) malloc(sizeof(dijkstra_nodo_t));
		if(!nodo) return NULL;

		// Seteamos datos iniciales del nodo
		nodo->dato = arregloDeVertices[i];
		nodo->nodo_previo = NULL;
		nodo->peso_camino = INFINITO;

		// Enviamos a la cola de no marcados (NM) a los nodos
		// de los vértices que no son el origen
		if(arregloDeVertices[i] != origen)
			cola_encolar(NM, nodo);
		else
		{
			nodo->peso_camino = 0;
			//cola_encolar(M, nodo);
			//V = nodo;
			a = nodo;
		}
	}

	// (Paso 9)
	while(!cola_esta_vacia(NM))
	{
		// (Paso 5)
		while(!cola_esta_vacia(NM))
		{
			// (Paso 2)
			cola_desencolar(NM, &Vi);

			// (Paso 3)
			if(grafo_son_adyacentes(grafo, a->dato, Vi->dato))
			{
				int peso_camino = a->peso_camino + 
					grafo_obtener_peso_arista(grafo, a->dato, Vi->dato);

				// printf("%d - %d\n", Vi->peso_camino, peso_camino);

				if(Vi->peso_camino > peso_camino)
				{
					Vi->peso_camino = peso_camino;
					Vi->nodo_previo = a;
				}
			}

			// (Paso 4)
			cola_encolar(CA, Vi);
		}
		
		// (Paso 6)
		cola_encolar(M, a);
		a = Vi = NULL;
		menor_peso = INFINITO;

		while(!cola_esta_vacia(CA))
		{
			cola_desencolar(CA, &Vi);

			if(menor_peso > Vi->peso_camino)
			{
				if(a) cola_encolar(NM, a);
				a = Vi;
				menor_peso = Vi->peso_camino;
				continue;
			}
			else if(menor_peso == Vi->peso_camino)
			{
				if(criterio_seleccion(Vi->dato, a->dato) < 0)
				{
					cola_encolar(NM, a);
					a = Vi;
					menor_peso = Vi->peso_camino;
				}
				else
					cola_encolar(NM, Vi);

				continue;
			}
			
			cola_encolar(NM, Vi);
		}
	}

	// (Paso 10)
	cola_encolar(M, a);

	

	// Preparamos resultados para devolver
	lista_t* lista_resultados = cola_a_lista(M);

	// // DEBUG! Libera memoria
	// //while(!cola_esta_vacia(M))
	// //{
	// 	cola_desencolar(M, &V);
		
	// 	printf("peso: %d\n", V->peso_camino);
	// 	return V->dato;
	// 	return V->dato;
	// //	free(V);
	// //}

	cola_destruir(M);
	cola_destruir(NM);
	cola_destruir(CA);

	return lista_resultados;
}

//
void dijkstra_destruir_resultados(lista_t* lista_resultados)
{
	// Destruimos la lista y los nodos que contiene dentro
	lista_destruir(lista_resultados, free);
}

// 
lista_t* dijkstra_obtener_camino(lista_t* lista_resultados, lista_dato_t *destino)
{
	// Creamos lista de camino
	lista_t* camino = lista_crear();
	if(!camino) return NULL;

	// Establecemos el nodo destino como el nodo inicial de proceso
	lista_dato_t prox = destino;
	lista_insertar_primero(camino, prox);

	// Rastreamos camino desde el destino hacia el nodo origen.
	while(prox)
	{
		lista_iter_t* iter = lista_iter_crear(lista_resultados);
		lista_dato_t aux;

		while(!lista_iter_al_final(iter))
		{
			lista_iter_ver_actual(iter, &aux);
			
			if(((dijkstra_nodo_t*)aux)->dato == prox)
			{
				// Terminamos si se llego al origen
				if(!(((dijkstra_nodo_t*)aux)->nodo_previo)) 
				{
					prox = NULL;
					break;
				}

				prox = (((dijkstra_nodo_t*)aux)->nodo_previo)->dato;
				lista_insertar_primero(camino, prox);
				break;
			};

			lista_iter_avanzar(iter);
		}
		
		lista_iter_destruir(iter);
	}

	return camino;
}