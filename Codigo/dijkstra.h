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
 * FUNCIONES DE LA LIBRERIA
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
	int criterio_seleccion(lista_dato_t, lista_dato_t));


// Función que destruye la lista de resultados del algoritmo de Dijkstra.
// PRE: 'lista_resultados' es una lista que contiene los resultados derivados
// de la función dijkstra_caminos_minimos().
// POST: Los resultados son destruidos.
void dijkstra_destruir_resultados(lista_t* lista_resultados);


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
lista_t* dijkstra_obtener_camino(lista_t* lista_resultados, 
	lista_dato_t *destino);


#endif
