/* ******************************************************************
 * ******************************************************************
 * TAD GRAFO
 * ..................................................................
 *
 * Implementación de un grafo múltiple, incluyendo como primitivas a
 * las operaciones básicas de estos. Con múltiple nos referimos a que 
 * puede ser utilizado como grafo ponderado o como grafo no ponderado.
 *
 * ******************************************************************
 * ******************************************************************/


#ifndef GRAFO_H
#define GRAFO_H

#include <stdbool.h>
#include <stddef.h>



/* ******************************************************************
 * DECLARACIÓN DE LOS TIPOS DE DATOS
 * *****************************************************************/

#ifndef GRAFO_DATO_T
#define GRAFO_DATO_T
typedef void* grafo_dato_t;
#endif

typedef struct _grafo_t grafo_t;



/* ******************************************************************
 * PRIMITIVAS DEL GRAFO
 * *****************************************************************/

// Crea un grafo.
// POST: devuelve un nuevo grafo vacío o NULL si no se ha podido
// llevar a cabo la creación del mismo.
grafo_t* grafo_crear();

// Destruye un grafo.
// PRE: 'grafo' es un grafo existente.
// POST: se eliminaron todos los vértices y aristas del grafo mas no
// así los datos vinculados a los vértices, los cuales permanecen 
// intactos.
void grafo_destruir(grafo_t *grafo);

// Crea un nuevo vértice en el grafo.
// PRE: 'grafo' es un grafo existente; 'dato' es el dato a vincular
// con el vértice.
// POST: devuelve true si se llevó a cabo la acción exitosamente, y
// false en caso contrario.
bool grafo_nuevo_vertice(grafo_t *grafo, const grafo_dato_t dato);

// Elimina un vértice del grafo.
// PRE: 'grafo' es un grafo existente; 'dato' es el dato que se 
// encuentra vinculado al vértice que se desee eliminar.
// POST: devuelve true si se llevó a cabo la acción exitosamente, y
// false en caso contrario. Si no existia previamente el vértice
// se devuelve false.
bool grafo_eliminar_vertice(grafo_t *grafo, const grafo_dato_t dato);

// Verifica si un vértice existe en un grafo.
// PRE: 'grafo' es un grafo existente; dato' es el dato que se 
// encuentra vinculado al vértice a consultar.
// POST: se devuelve true si el vértice existe en el grafo o false en
// en caso contrario.
bool grafo_es_vertice(grafo_t *grafo, const grafo_dato_t dato);

// Añade un arco o arista (di, df) al grafo.
// PRE: 'grafo' es un grafo existente; 'di' es el dato vinculado al 
// vértice de partida; 'df' es el dato vinculado al vértice destino;
// 'peso' es el peso de la arista, el cual, en caso de ser un grafo 
// no ponderado, debe pasársele el valor entero 1.
// POST: devuelve true si se llevó a cabo la acción exitosamente o
// false en caso contrario. Si ya existia la arista, se actualiza
// su peso.
bool grafo_crear_arista(grafo_t *grafo, grafo_dato_t di, 
	grafo_dato_t df, int peso);

// Elimina un arco o arista (di, df) del grafo.
// PRE: 'grafo' es un grafo existente; 'di' es el dato vinculado al 
// vértice de partida; 'df' es el dato vinculado al vértice destino.
// POST: devuelve true si se llevó a cabo la acción exitosamente o
// false en caso contrario. En caso de no existir previamente la 
// arista también se devolverá false.
bool grafo_eliminar_arista(grafo_t *grafo, grafo_dato_t di, 
	grafo_dato_t df);

// Devuelve el peso de la arista que une a dos vértices.
// PRE: 'grafo' es un grafo existente; 'di' es el dato vinculado al 
// vértice de partida; 'df' es el dato vinculado al vértice destino.
// POST: devuelve un entero que representa el peso de la arista. Se
// devuelve el valor 0 si no existe la arista.
int grafo_obtener_peso_arista(grafo_t *grafo, grafo_dato_t di, 
	grafo_dato_t df);

// Devuelve la cantidad de vértices contenidos en un grafo.
// PRE: 'grafo' es un grafo existente.
// POST: devuelve un entero que representa la cantidad de vértices 
// del grafo. Devuelve 0 si no hay vértices.
int grafo_cantidad_vertices(grafo_t *grafo);

// Verifica si dos vértices de un grafo son adyacentes.
// PRE: 'grafo' es un grafo existente; 'di' es el dato vinculado al 
// vértice de partida; 'df' es el dato vinculado al vértice destino.
// POST: devuelve true si los vértices son adyacentes o false en caso
// contrario.
bool grafo_son_adyacentes(grafo_t *grafo, grafo_dato_t di, 
	grafo_dato_t df);

// Devuelve los vértices de un grafo.
// PRE: 'grafo' es un grafo existente; 'listaDeVertices' es un arreglo 
// del tamaño de la cantidad de vértices existente en el grafo al 
// momento de llamar a esta función (el usuario es el responsable de
// asegurarse de cumplir con este requisito). 
// POST: se almacenó en 'listaDeVertices' los datos de los vértices 
// existentes. Si no hay vértices, la lista será igual a NULL.
void grafo_obtener_vertices(grafo_t *grafo, grafo_dato_t *listaDeVertices);

#endif
