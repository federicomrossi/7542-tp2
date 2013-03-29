/* ******************************************************************
 * ******************************************************************
 * TAD GRAFO
 * ..................................................................
 * Implementación de un grafo múltiple a partir de una matriz de adya-
 * cencia, incluyendo como métodos a las operaciones básicas de los
 * grafos. Con múltiple nos referimos a que puede ser utilizado como
 * grafo ponderado o como grafo no ponderado.(REVISAR!!!!)
 *
 * ******************************************************************
 * ******************************************************************/


#ifndef GRAFO_H
#define GRAFO_H

#include <stdbool.h>
#include <stddef.h>
//#include "lista.h"



/* ******************************************************************
 *                 DECLARACIÓN DE LOS TIPOS DE DATOS
 * *****************************************************************/

#ifndef GRAFO_DATO_T
#define GRAFO_DATO_T
typedef void* grafo_dato_t;
#endif

typedef struct _grafo_t grafo_t;



/* *******************************************************************
 * INCLUSIÓN DE TAD's Y DEFINICIÓN DE LOS TIPOS DE DATOS DE LOS MISMOS
 * ******************************************************************/

//#define LISTA_DATO_T
//typedef grafo_vertice_t* lista_dato_t;

//#define HASH_DATO_T
//typedef grafo_vertice_t* hash_dato_t;


//#include "librerias/lista.h"
//#include "librerias/hash_abierto.h"



/* ******************************************************************
 *                     PRIMITIVAS DEL GRAFO
 * *****************************************************************/

// Crea un grafo.
// POST: devuelve un nuevo grafo vacío o NULL si no se ha podido
// llevar a cabo la creación del mismo.
grafo_t* grafo_crear();

// Destruye el grafo.
// PRE: 'grafo' es un grafo existente.
// POST: se eliminaron todos los vertices y aristas del grafo.
void grafo_destruir(grafo_t *grafo);

// Crea un nuevo vértice en el grafo.
// PRE: 'grafo' es un grafo existente; 'dato' es el dato a vincular
// con el vértice.
// POST: devuelve true si se llevó a cabo la acción exitosamente, y
// false en caso contrario.
bool grafo_nuevo_vertice(grafo_t *grafo, const grafo_dato_t dato);

// Elimina un vértice del grafo.
// PRE: 'grafo' es un grafo existente; 'vertice' es el vértice que
// se desea eliminar.
// POST: devuelve true si se llevó a cabo la acción exitosamente, y
// false en caso contrario.
bool grafo_eliminar_vertice(grafo_t *grafo, const grafo_dato_t dato);

// Verifica si un vértice existe en un grafo.
// PRE: 'grafo' es un grafo existente; 'vertice' es un vértice.
// POST: se devuelve true si el vértice existe en el grafo y false en
// en caso contrario.
bool grafo_es_vertice(grafo_t *grafo, const grafo_dato_t dato);

// Añade un arco o arista (vi, vf) al grafo.
// PRE: 'grafo' es un grafo existente; 'vi' es el vértice de partida; 'vf' es
// el vértice destino; 'peso' es el peso de la arista, el cual, en caso de ser
// un grafo no ponderado, debe pasarse el valor entero 1.
// POST: devuelve true si se llevó a cabo la acción exitosamente, y
// false en caso contrario. De existir la arista previamente a su creación, 
// también se devolverá false.
bool grafo_crear_arista(grafo_t *grafo, grafo_dato_t di, 
	grafo_dato_t df, int peso);

// Elimina un arco o arista (vi, vf) del grafo.
// PRE: 'grafo' es un grafo existente; 'vi' es el vértice de partida; 'vf' es
// el vértice destino.
// POST: devuelve true si se llevó a cabo la acción exitosamente, y
// false en caso contrario. De existir la arista previamente a su creación, 
// también se devolverá false.
//bool grafo_eliminar_arista(grafo_t *grafo, grafo_vertice_t *vi,
//	grafo_vertice_t *vf);

// Consulta el peso de la arista que une a dos vértices.
// PRE: 'grafo' es un grafo existente; 'vi' es el vértice de partida; 'vf' es
// el vértice destino.
// POST: devuelve un entero que representa el peso de la arista o NULL si
// no existe la arista.
int grafo_obtener_peso_arista(grafo_t *grafo, grafo_dato_t di, 
	grafo_dato_t df);

// Devuelve la cantidad de vértices contenidos en un grafo.
// PRE: 'grafo' es un grafo existente.
// POST: devuelve un entero que representa la cantidad de vértices del grafo.
// Devuelve 0 si no hay vértices.
int grafo_cantidad_vertices(grafo_t *grafo);

// Verifica si dos vértices de un grafo son adyacentes
// PRE: 'grafo' es un grafo existente. 'vi' es el vértice de partida; 'vf' es
// el vértice destino. 'vi' y 'vf' deben pertenecer al grafo.
// POST: devuelve true si si los vértices son adyacentes o false en caso
// contrario.
bool grafo_son_adyacentes(grafo_t *grafo, grafo_dato_t di, 
	grafo_dato_t df);
//
// Devuelve los vértices de un grafo.
// PRE: 'grafo' es un grafo existente.
// POST: devuelve una lista con los vértices del grafo.
//lista_t* grafo_obtener_vertices(grafo_t *grafo);


#endif
