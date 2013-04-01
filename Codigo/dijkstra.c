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

// Entero considerado infinito utilizado para el algoritmo de Dijkstra
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

// Tipo que representa un nodo en el algoritmo de Dijkstra.
struct _dijkstra_nodo_t {
	lista_dato_t dato;				// Puntero al dato del vértice
	dijkstra_nodo_t *nodo_previo;	// Puntero al dato del vértice 
									// previo para llegar al vértice  
									// actual por camino mínimo
	int peso_camino;				// Peso mínimo del camino hasta 
									// llegar
};



/* ******************************************************************
 * FUNCIONES DE LA LIBRERÍA
 * *****************************************************************/


// Función que calcula los caminos mínimos de un grafo, partiendo de un
// origen hacia los demás vérticies, utilizando el algoritmo de Dijkstra.
// PRE: 'grafo' es un grafo cargado con nodos no aislados; 'origen' es
// el nodo desde el cual se desean calcular los caminos mínimos (debe ser
// del tipo de datos cargado en el grafo, pero al pasarse a esta función
// debe ser casteado al tipo lista_dato_t para evitar conflictos de tipo
// en las listas); 'criterio_seleccion()' es una función que se encarga 
// de definir el criterio de selección ante dos caminos que poseen la 
// misma distancia desde el nodo origen. Por parámetro recibe los dos
// nodos del grafo. La función debe devolver un valor entero < 0 si se
// debe elegir el nodo del primer parámetro ó un entero > 0 si se debe
// elegir el nodo del segundo parámetro.
// POST: se devuelve una lista donde se almacenan los resultados de 
// procesamiento. Estos no son directamente procesables por el usuario.
// Esta lista es utilizada por otras funciones de la librería para poder
// brindar resultados personalizados de acuerdo a lo que se necesite.
lista_t* dijkstra_caminos_minimos(grafo_t *grafo, lista_dato_t origen, 
	int criterio_seleccion(lista_dato_t, lista_dato_t))
{
	// Variables auxiliares de procesamiento
	dijkstra_nodo_t *a = NULL, *Vi;
	int menor_peso = INFINITO;

	// Lista de nodos marcados
	lista_t* M = lista_crear();
	// Cola de nodos no marcados
	cola_t* NM = cola_crear();
	// Cola auxiliar
	cola_t* CA = cola_crear();


	// Obtenemos los vértices del grafo
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
			a = nodo;
		}
	}

	// Iteramos hasta marcar todos los nodos
	while(!cola_esta_vacia(NM))
	{
		// Iteramos hasta completar una vuelta de procesamiento de
		// nodos no marcados
		while(!cola_esta_vacia(NM))
		{
			cola_desencolar(NM, &Vi);

			// Si son adyacentes, comparamos distancias
			if(grafo_son_adyacentes(grafo, a->dato, Vi->dato))
			{
				// Calculamos el peso del camino llegando desde nodo actual 'a'
				int peso_camino = a->peso_camino + 
					grafo_obtener_peso_arista(grafo, a->dato, Vi->dato);

				// Si el camino llegando desde 'a' es mas corto que el que
				// se tenía registrado, cambiamos el punto de llegada de Vi
				// para que provenga desde 'a'
				if(Vi->peso_camino > peso_camino)
				{
					Vi->peso_camino = peso_camino;
					Vi->nodo_previo = a;
				}
			}

			// Encolamos el nodo procesado en la cola auxiliar
			cola_encolar(CA, Vi);
		}
		
		// Marcamos el nodo actual 'a' enviándolo a la lista de marcados.
		// Lo insertamos primero para que quede en orden decreciente, es decir,
		// que comienze por el destino y termine en el origen.
		lista_insertar_primero(M, a);
		// Reseteamos variables de procesamiento
		a = Vi = NULL;
		menor_peso = INFINITO;

		// Iteramos hasta pasar todos los nodos de CA a NM excepto
		// aquel que posee la menor distancia, el cual pasa a ser
		// el nuevo nodo actual 'a'
		while(!cola_esta_vacia(CA))
		{
			cola_desencolar(CA, &Vi);

			// Caso para cuando aparece un nodo con menor
			// distancia
			if(menor_peso > Vi->peso_camino)
			{
				if(a) cola_encolar(NM, a);
				a = Vi;
				menor_peso = Vi->peso_camino;
				continue;
			}
			// Caso para cuando las distancias de los nodos son iguales
			else if(menor_peso == Vi->peso_camino)
			{
				// Elegimos uno de acuerdo al criterio de selección definido
				// por el usuario
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
			
			// Si la distancia del nodo es mayor, directamente encolamos
			// en la cola de no marcados nuevamente
			cola_encolar(NM, Vi);
		}
	}

	// Si no quedan mas nodos sin marcar, enviamos el último nodo actual 'a' 
	// a la lista de marcados. Lo insertamos primero para que quede en orden
	// decreciente, es decir, que comienze por el destino y termine en el
	// origen
	lista_insertar_primero(M, a);

	cola_destruir(NM);
	cola_destruir(CA);

	return M;
}


// Función que destruye la lista de resultados del algoritmo de Dijkstra.
// PRE: 'lista_resultados' es una lista que contiene los resultados derivados
// de la función dijkstra_caminos_minimos().
// POST: Los resultados son destruidos.
void dijkstra_destruir_resultados(lista_t* lista_resultados)
{
	// Destruimos la lista y los nodos que contiene dentro
	lista_destruir(lista_resultados, free);
}


// Función que construye una lista con el camino desde el vértice origen
// hasta un vértice destino.
// PRE: 'lista_resultados' es una lista que contiene los resultados derivados
// de la función dijkstra_caminos_minimos(); 'destino' es el destino al que
// se desea llegar (debe ser del mismo tipo que el dato almacenado en el grafo
// que se procesó en la función que genera los resultados, pero debe ser 
// pasado a esta función con un casteo previo a lista_dato_t).
// POST: devuelve una lista donde el primer elemento es el origen, elúltimo 
// es el destino y los elementos intermedios determinan el camino a seguir. 
// Al sacar los elementos de la lista deben ser casteados al tipo del dato
// insertado en el grafo, el cual se procesó en la función generadora de 
// resultados.
lista_t* dijkstra_obtener_camino(lista_t* lista_resultados, lista_dato_t *destino)
{
	// Creamos lista del camino
	lista_t* camino = lista_crear();
	if(!camino) return NULL;

	// Establecemos el nodo destino como el nodo inicial de proceso, el cual
	// se encuentra como primer elemento en la lista de resultados
	lista_dato_t previo = destino;
	lista_insertar_primero(camino, previo);

	// Rastreamos camino desde el destino hacia el nodo origen
	while(previo)
	{
		lista_iter_t* iter = lista_iter_crear(lista_resultados);
		lista_dato_t aux;

		while(!lista_iter_al_final(iter))
		{
			lista_iter_ver_actual(iter, &aux);
			
			// Buscamos en la lista el nodo previo
			if(((dijkstra_nodo_t*)aux)->dato == previo)
			{
				// Terminamos si se llegó al origen
				if(!(((dijkstra_nodo_t*)aux)->nodo_previo)) 
				{
					previo = NULL;
					break;
				}

				previo = (((dijkstra_nodo_t*)aux)->nodo_previo)->dato;
				lista_insertar_primero(camino, previo);
				break;
			};

			lista_iter_avanzar(iter);
		}
		
		lista_iter_destruir(iter);
	}

	// Devolvemos la lista del camino
	return camino;
}
