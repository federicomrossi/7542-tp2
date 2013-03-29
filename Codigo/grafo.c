/* ******************************************************************
 * ******************************************************************
 * TAD GRAFO
 * ..................................................................
 * Implementación de un grafo múltiple a partir de una matriz de adya-
 * cencia, incluyendo como métodos a las operaciones básicas de los
 * grafos. Con múltiple nos referimos a que puede ser utilizado como
 * grafo ponderado o como grafo no ponderado.(REVISAR!!!!)
 *
 * ADVERTENCIA: El grafo puede ser utilizado para cualquier tipo de 
 * dato, exceptuando el tipo CHAR. En su lugar, se recomienda crear
 * una estructura que contenga al CHAR dentro de ella, para luego
 * utilizar como tipo de dato la nueva estructura creada.
 *
 * ******************************************************************
 * ******************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"



/* ******************************************************************
 *                 DECLARACIÓN DE LOS TIPOS DE DATOS
 * *****************************************************************/

typedef struct _arista_t arista_t;
typedef struct _vertice_t vertice_t;



/* ******************************************************************
 *              INCLUSIÓN DE LIBRERIAS Y TADS EXTERNOS
 * *****************************************************************/

#define LISTA_DATO_T
typedef arista_t* lista_dato_t;
#include "lista.h"



/* ******************************************************************
 *                DEFINICION DE LOS TIPOS DE DATOS
 * *****************************************************************/

// Tipo que representa a un grafo.
struct _grafo_t
{
	vertice_t* primerVertice;
	vertice_t* ultimoVertice;
	int cantidadVertices;
};

// Tipo que representa una arista.
struct _arista_t
{
	vertice_t* verticeAdyacente;	// Puntero al vértice adyacente
	int peso;						// Peso de la arista
};

// Tipo que representa a un vértice del grafo.
struct _vertice_t
{
	grafo_dato_t dato;
	lista_t* listaDeAdyacencia;
	vertice_t* siguienteVertice;
};





/* ******************************************************************
 *                  	FUNCIONES AUXILIARES
 * *****************************************************************/

//
vertice_t* grafo_obtener_vertice(grafo_t *grafo, const grafo_dato_t dato)
{
	vertice_t *vertice = grafo->primerVertice;

	while(vertice)
	{
		if(vertice->dato == dato) return vertice;
		vertice = vertice->siguienteVertice;
	}

	return NULL;
}


//
arista_t* grafo_obtener_arista(grafo_t *grafo, grafo_dato_t di, 
	grafo_dato_t df)
{
	// Obtenemos los vértices que contienen los datos
	vertice_t *vi = grafo_obtener_vertice(grafo, di);
	vertice_t *vf = grafo_obtener_vertice(grafo, df);
	if((!vi) || (!vf) || (vi == vf)) return NULL;

	lista_iter_t* iter = lista_iter_crear(vi->listaDeAdyacencia);
	arista_t* arista;

	while(!lista_iter_al_final(iter))
	{
		lista_iter_ver_actual(iter, &arista);
		if(arista->verticeAdyacente == vf)
		{
			lista_iter_destruir(iter);
			return arista;
		};
		lista_iter_avanzar(iter);
	}
	
	lista_iter_destruir(iter);
	return NULL;
}


// Función de destrucción de una arista. 
// Pre: la arista fue creada.
// Post: se eliminó la arista.
void grafo_destruir_arista(arista_t* arista)
{
	free(arista);
}


// 
bool grafo_existe_vertice(grafo_t *grafo, const grafo_dato_t dato)
{
	vertice_t *vertice = grafo->primerVertice;

	while(vertice)
	{
		if(vertice->dato == dato) return true;
		vertice = vertice->siguienteVertice;
	}

	return false;
}







/* ******************************************************************
 *                    PRIMITIVAS DE LA COLA
 * *****************************************************************/

// Crea un grafo.
// POST: devuelve un nuevo grafo vacío o NULL si no se ha podido
// llevar a cabo la creación del mismo.
grafo_t* grafo_crear()
{
	grafo_t* grafo = (grafo_t*) malloc(sizeof(grafo_t));

	if(!grafo) return NULL;

	grafo->primerVertice = NULL;
	grafo->ultimoVertice = NULL;
	grafo->cantidadVertices = 0;

	return grafo;
}


// Destruye el grafo.
// PRE: 'grafo' es un grafo existente.
// POST: se eliminaron todos los vertices y aristas del grafo.
void grafo_destruir(grafo_t *grafo)
{
	vertice_t *vertice = grafo->primerVertice;
	vertice_t *vertice_tmp;

	while(vertice)
	{
		vertice_tmp = vertice->siguienteVertice;
		
		// Destruimos aristas asociadas al vértice
		lista_destruir(vertice->listaDeAdyacencia, grafo_destruir_arista);
		free(vertice);

		vertice = vertice_tmp;
	}

	// Liberamos el espacio del grafo
	free(grafo);
}


// Crea un nuevo vértice en el grafo.
// PRE: 'grafo' es un grafo existente; 'dato' es el dato a vincular
// con el vértice.
// POST: devuelve true si se llevó a cabo la acción exitosamente, y
// false en caso contrario.
bool grafo_nuevo_vertice(grafo_t *grafo, const grafo_dato_t dato)
{
	// Verificamos si ya existe un vértice con el mismo dato
	if(grafo_existe_vertice(grafo, dato))
		return false;

	// Creamos un vértice
	vertice_t* vertice = (vertice_t*) malloc(sizeof(vertice_t));
	if(!vertice) return false;

	// Seteamos la información inicial del vértice
	vertice->dato = dato;
	vertice->listaDeAdyacencia = lista_crear();
	vertice->siguienteVertice = NULL;

	// Actualizamos la lista de vértices del grafo
	if(!grafo->primerVertice)
		grafo->primerVertice = vertice;
	else
		grafo->ultimoVertice->siguienteVertice = vertice;

	grafo->ultimoVertice = vertice;
	grafo->cantidadVertices++;

	return true;
}


// Elimina un vértice del grafo.
// PRE: 'grafo' es un grafo existente; 'vertice' es el vértice que
// se desea eliminar.
// POST: devuelve true si se llevó a cabo la acción exitosamente, y
// false en caso contrario.
bool grafo_eliminar_vertice(grafo_t *grafo, const grafo_dato_t dato)
{
	// Verificamos que exista el vértice
	vertice_t* vertice = grafo_obtener_vertice(grafo, dato);
	if(!vertice) return false;

	// Destruimos aristas asociadas al vértice
	lista_destruir(vertice->listaDeAdyacencia, grafo_destruir_arista);

	// Hacemos que el grafo deje de apuntar al vértice
	// MALLLLLLL!!! puede que no se esté en el primer vértice!!!!!
	grafo->primerVertice = vertice->siguienteVertice;
	if(!grafo->primerVertice) grafo->ultimoVertice = NULL;
	grafo->cantidadVertices--;

	// Destruimos aristas asociadas a otros vértices que
	// incluyan al vértice
	vertice_t *vertice_tmp = grafo->primerVertice;

	while(vertice_tmp)
	{
		// Verificamos si existen aristas salientes del vértice
		if(!lista_esta_vacia(vertice_tmp->listaDeAdyacencia))
		{
			// Iteramos sobre aristas del vértice
			lista_iter_t* iter = lista_iter_crear(vertice_tmp->listaDeAdyacencia);
			arista_t* arista;

			while(!lista_iter_al_final(iter))
			{
				lista_iter_ver_actual(iter, &arista);
				if(arista->verticeAdyacente == vertice)
				{
					// Como la arista es única, la destruimos y salimos
					grafo_destruir_arista(arista);
					break;
				}
				lista_iter_avanzar(iter);
			}
			
			lista_iter_destruir(iter);
		}

		vertice_tmp = vertice_tmp->siguienteVertice;
	}

	// Destruimos el vértice
	free(vertice);

	return true;
}


// Verifica si un vértice existe en un grafo.
// PRE: 'grafo' es un grafo existente; 'vertice' es un vértice.
// POST: se devuelve true si el vértice existe en el grafo y false en
// en caso contrario.
bool grafo_es_vertice(grafo_t *grafo, const grafo_dato_t dato)
{
	// Verificamos si ya existe un vértice con el mismo dato
	if(grafo_existe_vertice(grafo, dato))
		return true;

	return false;
}


// Añade un arco o arista (vi, vf) al grafo.
// PRE: 'grafo' es un grafo existente; 'vi' es el vértice de partida; 'vf' es
// el vértice destino; 'peso' es el peso de la arista, el cual, en caso de ser
// un grafo no ponderado, debe pasarse el valor entero 1.
// POST: devuelve true si se llevó a cabo la acción exitosamente, y
// false en caso contrario. De existir la arista previamente a su creación, 
// también se devolverá false.
bool grafo_crear_arista(grafo_t *grafo, grafo_dato_t di, 
	grafo_dato_t df, int peso)
{
	// Obtenemos los vértices que contienen los datos
	vertice_t *vi = grafo_obtener_vertice(grafo, di);
	vertice_t *vf = grafo_obtener_vertice(grafo, df);
	if((!vi) || (!vf) || (vi == vf)) return false;

	// Creamos arista 
	arista_t *arista = (arista_t*) malloc(sizeof(arista_t));
	if(!arista) return false;

	// Insertamos info en arista
	arista->verticeAdyacente = vf;
	arista->peso = peso;

	// Agregamos la arista a la lista de adyacencia del vértice inicial
	lista_insertar_ultimo(vi->listaDeAdyacencia, arista);

	return true;
}


// Elimina un arco o arista (vi, vf) del grafo.
// PRE: 'grafo' es un grafo existente; 'vi' es el vértice de partida; 'vf' es
// el vértice destino.
// POST: devuelve true si se llevó a cabo la acción exitosamente, y
// false en caso contrario. De existir la arista previamente a su creación, 
// también se devolverá false.
bool grafo_eliminar_arista(grafo_t *grafo, grafo_dato_t di, 
	grafo_dato_t df)
{
	// Obtenemos los vértices que contienen los datos
	vertice_t *vi = grafo_obtener_vertice(grafo, di);
	vertice_t *vf = grafo_obtener_vertice(grafo, df);
	if((!vi) || (!vf) || (vi == vf)) return false;

	// Iteramos sobre la lista de adyacentes del vértice inicial
	// hasta encontrar la arista, y la eliminamos.
	lista_iter_t* iter = lista_iter_crear(vi->listaDeAdyacencia);
	arista_t* arista;

	while(!lista_iter_al_final(iter))
	{
		lista_iter_ver_actual(iter, &arista);
		
		if(arista->verticeAdyacente == vf)
		{
			grafo_destruir_arista(arista);
			lista_borrar(vi->listaDeAdyacencia, iter, &arista);
			lista_iter_destruir(iter);
			return true;
		};

		lista_iter_avanzar(iter);
	}
	
	lista_iter_destruir(iter);
	return false;
}


// Consulta el peso de la arista que une a dos vértices.
// PRE: 'grafo' es un grafo existente; 'vi' es el vértice de partida; 'vf' es
// el vértice destino.
// POST: devuelve un entero que representa el peso de la arista o NULL si
// no existe la arista.
int grafo_obtener_peso_arista(grafo_t *grafo, grafo_dato_t di, 
	grafo_dato_t df)
{
	arista_t *arista = grafo_obtener_arista(grafo, di, df);
	if (!arista) return 0;
	
	return arista->peso;
}


// Devuelve la cantidad de vértices contenidos en un grafo.
// PRE: 'grafo' es un grafo existente.
// POST: devuelve un entero que representa la cantidad de vértices del grafo.
// Devuelve 0 si no hay vértices.
int grafo_cantidad_vertices(grafo_t *grafo)
{
	return grafo->cantidadVertices;
}


// Verifica si dos vértices de un grafo son adyacentes
// PRE: 'grafo' es un grafo existente. 'vi' es el vértice de partida; 'vf' es
// el vértice destino. 'vi' y 'vf' deben pertenecer al grafo.
// POST: devuelve true si si los vértices son adyacentes o false en caso
// contrario.
bool grafo_son_adyacentes(grafo_t *grafo, grafo_dato_t di, 
	grafo_dato_t df)
{
	return (grafo_obtener_arista(grafo, di, df) != NULL);
}


// Devuelve los vértices de un grafo.
// PRE: 'grafo' es un grafo existente.
// POST: devuelve una lista con los vértices del grafo.
//lista_t* grafo_obtener_vertices(grafo_t *grafo);
