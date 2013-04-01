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


#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"



/* ******************************************************************
 * DECLARACIÓN DE LOS TIPOS DE DATOS
 * *****************************************************************/

typedef struct _arista_t arista_t;
typedef struct _vertice_t vertice_t;



/* ******************************************************************
 * INCLUSIÓN DE LIBRERIAS Y TADS EXTERNOS
 * *****************************************************************/

// TAD Lista
#define LISTA_DATO_T
typedef arista_t* lista_dato_t;
#include "lista.h"



/* ******************************************************************
 * DEFINICIÓN DE LOS TIPOS DE DATOS
 * *****************************************************************/

// Tipo que representa a un grafo.
struct _grafo_t
{
	vertice_t* primerVertice;	// Puntero al primer vértice del grafo
	vertice_t* ultimoVertice;	// Puntero al último vértice del grafo
	int cantidadVertices;		// Cantidad de vértices del grafo
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
	grafo_dato_t dato;				// Dato asociado al vértice
	lista_t* listaDeAdyacencia;		// Lista de adyacencia del vértice
	vertice_t* verticeSiguiente;	// Puntero al vértice siguiente
};



/* ******************************************************************
 * FUNCIONES AUXILIARES
 * *****************************************************************/

// Función que devuelve, de existir, el vértice asociado a un dato de
// un grafo.
// PRE: 'grafo' es un grafo existente; dato' es el dato que se 
// encuentra vinculado al vértice a consultar.
// POST: Se devuelve un puntero al vértice o NULL si no existe.
vertice_t* grafo_obtener_vertice(grafo_t *grafo, const grafo_dato_t dato)
{
	// Buscamos el vértice en la lista interna del grafo
	vertice_t *vertice = grafo->primerVertice;

	while(vertice)
	{
		if(vertice->dato == dato) return vertice;
		vertice = vertice->verticeSiguiente;
	}

	return NULL;
}

// Función que desvincula a un vértice del grafo al que pertenece.
// PRE: 'grafo' es un grafo existente; 'vertice' es un vértice 
// incluido en el grafo.
// POST: El vértice ya no se encuentra vinculado al grafo. Si se
// pasa un vértice que previamente no pertenecia al grafo, la función
// no lanza error.
void grafo_desvincular_vertice(grafo_t* grafo, vertice_t *vertice)
{
	// Iteramos sobre todos los vértices asociados al grafo
	vertice_t* vTmp = grafo->primerVertice;
	vertice_t* vAnteriorTmp = NULL;

	while(vTmp)
	{
		// Verificamos si encontramos el vértice a eliminar
		if(vTmp == vertice)
		{
			// Acción a realizar cuando el vértice es el primero
			if(grafo->primerVertice == vertice)
				grafo->primerVertice = vertice->verticeSiguiente;

			// Acción a realizar cuando el vértice es el último
			if(grafo->ultimoVertice == vertice)
				grafo->ultimoVertice = vAnteriorTmp;

			// Acción sobre el vértice anterior si existe
			if(vAnteriorTmp)
				vAnteriorTmp->verticeSiguiente = vTmp->verticeSiguiente;

			grafo->cantidadVertices--;

			return;
		}

		vAnteriorTmp = vTmp;
		vTmp = vTmp->verticeSiguiente;
	}
}

// Función que devuelve un puntero a la arista asociada a dos datos
// que previamente tienen que haber sido ingresados como vértices.
// PRE: 'grafo' es un grafo existente; 'di' es el dato vinculado al 
// vértice de partida de la arista; 'df' es el dato vinculado al 
// vértice destino de la arista.
// POST: se devuelve un puntero a la arista en caso de existir, o
// NULL en caso contrario. Si alguno de los datos no se encuentra
// en uno de los vértices, también se devuelve NULL.  
arista_t* grafo_obtener_arista(grafo_t *grafo, grafo_dato_t di, 
	grafo_dato_t df)
{
	// Obtenemos los vértices asociados a los datos
	vertice_t *vi = grafo_obtener_vertice(grafo, di);
	vertice_t *vf = grafo_obtener_vertice(grafo, df);
	if((!vi) || (!vf) || (vi == vf)) return NULL;

	// Iteramos sobre la lista de adyacencia del vértice de partida
	// para buscar la arista que lo vincula con el vértice destino
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
// Pre: 'arista' es una arista existente.
// Post: Se liberó el espacio de memoria ocupado por la arista.
void arista_funcion_de_destruccion(arista_t* arista)
{
	free(arista);
}

// Función que dados dos vértices, destruye la arista que los
// asocia.
// PRE: 'vi' es el vértice de partida de la arista; 'vf' es el
// vértice destino de la arista.
// POST: devuelve true si se realizó la acción exitosamente o
// false en su defecto, como así también, si no existe tal arista.
bool grafo_destruir_arista(vertice_t *vi, vertice_t *vf)
{
	// Iteramos sobre la lista de adyacentes del vértice inicial
	// hasta encontrar la arista, y la eliminamos.
	lista_iter_t* iter = lista_iter_crear(vi->listaDeAdyacencia);
	arista_t* arista;

	while(!lista_iter_al_final(iter))
	{
		lista_iter_ver_actual(iter, &arista);
		
		if(arista->verticeAdyacente == vf)
		{
			arista_funcion_de_destruccion(arista);
			lista_borrar(vi->listaDeAdyacencia, iter, &arista);
			lista_iter_destruir(iter);
			return true;
		};

		lista_iter_avanzar(iter);
	}
	
	lista_iter_destruir(iter);

	// No se encontró la arista
	return false;
}


// Función que verifica si existe un vértice en un grafo.
// PRE: 'grafo' es un grafo existente; 'dato' es el dato que se 
// encuentra vinculado al vértice que se desea verificar.
// POST: devuelve true si el vértice existe en el grafo o false en
// en caso contrario.
bool grafo_existe_vertice(grafo_t *grafo, const grafo_dato_t dato)
{
	// Iteramos sobre todos los vértices asociados al grafo
	vertice_t *vertice = grafo->primerVertice;

	while(vertice)
	{
		// Comprobamos si el vértice actual se encuentra
		// asociado al dato
		if(vertice->dato == dato) return true;
		vertice = vertice->verticeSiguiente;
	}

	// No se encontró un vértice asociado
	return false;
}



/* ******************************************************************
 * PRIMITIVAS DEL GRAFO
 * *****************************************************************/

// Crea un grafo.
// POST: devuelve un nuevo grafo vacío o NULL si no se ha podido
// llevar a cabo la creación del mismo.
grafo_t* grafo_crear()
{
	// Solicitamos espacio en memoria
	grafo_t* grafo = (grafo_t*) malloc(sizeof(grafo_t));
	if(!grafo) return NULL;

	// Seteamos parámetros iniciales del grafo
	grafo->primerVertice = NULL;
	grafo->ultimoVertice = NULL;
	grafo->cantidadVertices = 0;

	return grafo;
}

// Destruye un grafo.
// PRE: 'grafo' es un grafo existente.
// POST: se eliminaron todos los vértices y aristas del grafo mas no
// así los datos vinculados a los vértices, los cuales permanecen 
// intactos.
void grafo_destruir(grafo_t *grafo)
{
	vertice_t *vertice = grafo->primerVertice;
	vertice_t *vertice_tmp;

	// Destruimos los vértices asociados al grafo
	while(vertice)
	{
		vertice_tmp = vertice->verticeSiguiente;
		
		// Destruimos aristas asociadas al vértice
		lista_destruir(vertice->listaDeAdyacencia, 
			arista_funcion_de_destruccion);
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
	vertice->verticeSiguiente = NULL;

	// Vinculamos el vértice al grafo
	if(!grafo->primerVertice)
		grafo->primerVertice = vertice;
	else
		grafo->ultimoVertice->verticeSiguiente = vertice;

	grafo->ultimoVertice = vertice;
	grafo->cantidadVertices++;

	return true;
}

// Elimina un vértice del grafo.
// PRE: 'grafo' es un grafo existente; 'dato' es el dato que se 
// encuentra vinculado al vértice que se desee eliminar.
// POST: devuelve true si se llevó a cabo la acción exitosamente, y
// false en caso contrario. Si no existia previamente el vértice
// se devuelve false.
bool grafo_eliminar_vertice(grafo_t *grafo, const grafo_dato_t dato)
{
	// Verificamos que exista el vértice
	vertice_t* vertice = grafo_obtener_vertice(grafo, dato);
	if(!vertice) return false;

	// Destruimos aristas asociadas al vértice
	lista_destruir(vertice->listaDeAdyacencia, arista_funcion_de_destruccion);

	// Desvinculamos al vértice del grafo
	grafo_desvincular_vertice(grafo, vertice);

	// Destruimos aristas asociadas a otros vértices que
	// incluyan al vértice
	vertice_t *vertice_tmp = grafo->primerVertice;

	while(vertice_tmp)
	{
		// Verificamos si existen aristas salientes del vértice
		if(!lista_esta_vacia(vertice_tmp->listaDeAdyacencia))
			grafo_destruir_arista(vertice_tmp, vertice);

		vertice_tmp = vertice_tmp->verticeSiguiente;
	}

	// Destruimos el vértice
	free(vertice);

	return true;
}

// Verifica si un vértice existe en un grafo.
// PRE: 'grafo' es un grafo existente; dato' es el dato que se 
// encuentra vinculado al vértice a consultar.
// POST: se devuelve true si el vértice existe en el grafo o false en
// en caso contrario.
bool grafo_es_vertice(grafo_t *grafo, const grafo_dato_t dato)
{
	// Verificamos si ya existe un vértice con el mismo dato
	if(grafo_existe_vertice(grafo, dato))
		return true;

	return false;
}

// Añade un arco o arista (di, df) al grafo.
// PRE: 'grafo' es un grafo existente; 'di' es el dato vinculado al 
// vértice de partida; 'df' es el dato vinculado al vértice destino;
// 'peso' es el peso de la arista, el cual, en caso de ser un grafo 
// no ponderado, debe pasársele el valor entero 1.
// POST: devuelve true si se llevó a cabo la acción exitosamente o
// false en caso contrario. Si ya existia la arista, se actualiza
// su peso.
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

	// Eliminamos, si existe, la arista vieja
	grafo_destruir_arista(vi, vf);

	// Agregamos arista a la lista de adyacencia del vértice inicial
	lista_insertar_ultimo(vi->listaDeAdyacencia, arista);

	return true;
}

// Elimina un arco o arista (di, df) del grafo.
// PRE: 'grafo' es un grafo existente; 'di' es el dato vinculado al 
// vértice de partida; 'df' es el dato vinculado al vértice destino.
// POST: devuelve true si se llevó a cabo la acción exitosamente o
// false en caso contrario. En caso de no existir previamente la 
// arista también se devolverá false.
bool grafo_eliminar_arista(grafo_t *grafo, grafo_dato_t di, 
	grafo_dato_t df)
{
	// Obtenemos los vértices que contienen los datos
	vertice_t *vi = grafo_obtener_vertice(grafo, di);
	vertice_t *vf = grafo_obtener_vertice(grafo, df);
	if((!vi) || (!vf) || (vi == vf)) return false;

	return grafo_destruir_arista(vi, vf);
}

// Devuelve el peso de la arista que une a dos vértices.
// PRE: 'grafo' es un grafo existente; 'di' es el dato vinculado al 
// vértice de partida; 'df' es el dato vinculado al vértice destino.
// POST: devuelve un entero que representa el peso de la arista. Se
// devuelve el valor 0 si no existe la arista.
int grafo_obtener_peso_arista(grafo_t *grafo, grafo_dato_t di, 
	grafo_dato_t df)
{
	arista_t *arista = grafo_obtener_arista(grafo, di, df);
	if (!arista) return 0;
	
	return arista->peso;
}

// Devuelve la cantidad de vértices contenidos en un grafo.
// PRE: 'grafo' es un grafo existente.
// POST: devuelve un entero que representa la cantidad de vértices 
// del grafo. Devuelve 0 si no hay vértices.
int grafo_cantidad_vertices(grafo_t *grafo)
{
	return grafo->cantidadVertices;
}

// Verifica si dos vértices de un grafo son adyacentes.
// PRE: 'grafo' es un grafo existente; 'di' es el dato vinculado al 
// vértice de partida; 'df' es el dato vinculado al vértice destino.
// POST: devuelve true si los vértices son adyacentes o false en caso
// contrario.
bool grafo_son_adyacentes(grafo_t *grafo, grafo_dato_t di, 
	grafo_dato_t df)
{
	return (grafo_obtener_arista(grafo, di, df) != NULL);
}

// Carga una lista con los vértices de un grafo.
// PRE: 'grafo' es un grafo existente; 'listaDeVertices' es un arreglo 
// del tamaño de la cantidad de vértices existente en el grafo al 
// momento de llamar a esta función (el usuario es el responsable de
// asegurarse de cumplir con este requisito). 
// POST: se almacenó en 'listaDeVertices' los datos de los vértices 
// existentes. Si no hay vértices, la lista será igual a NULL.
void grafo_obtener_vertices(grafo_t *grafo, grafo_dato_t *listaDeVertices)
{
	// Verificamos si hay vértices en el grafo
	if(!grafo->cantidadVertices) 
	{
		listaDeVertices = NULL;
		return;
	}	

	// Almacenamos los datos de los vértices en la lista de vértices
	vertice_t *v;
	int i = 0;

	for(v = grafo->primerVertice; v; v = v->verticeSiguiente)
		listaDeVertices[i++] = v->dato;
}
