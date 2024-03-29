/* ****************************************************************************
 * ****************************************************************************
 * TAD COLA
 * ..................................................................
 * Implementación del TDA Cola, la cual consta de un conjunto de 
 * primitivas básicas para su uso.
 *
 * ****************************************************************************
 * ****************************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include "cola.h"



/* ****************************************************************************
 * DEFINICIÓN DE LOS TIPOS DE DATOS
 * ***************************************************************************/

typedef struct _nodo_cola_t {
	cola_dato_t dato;				// Datos
	struct _nodo_cola_t* sig;		// Puntero al siguiente nodo de la lista
} nodo_cola_t;


struct _cola_t {
	nodo_cola_t* primero;		// Puntero al primer elemento de la cola
	nodo_cola_t* ultimo;		// Puntero al último elemento de la cola
};



/* ****************************************************************************
 * PRIMITIVAS DE LA COLA
 * ***************************************************************************/

// Crea una cola.
// POST: devuelve una nueva cola vacía o NULL si no se ha podido
// llevar a cabo la creación de la misma.
cola_t* cola_crear() {
	// Solicitamos espacio en memoria
	cola_t* cola = (cola_t*) malloc(sizeof(cola_t));
	if(!cola) return NULL;

	// Seteamos valores iniciales de la cola
	cola->primero = NULL;
	cola->ultimo = NULL;

	return cola;
}

// Destruye la cola.
// PRE: 'cola' es una cola existente.
// POST: se eliminaron todos los elementos de la cola.
void cola_destruir(cola_t *cola) {
	nodo_cola_t *nodo_actual, *nodo;

	// Si hay elementos, comenzamos la eliminación
	if(cola->primero) {
		nodo_actual = cola->primero;

		// Eliminación de los nodos uno a uno.
		while(nodo_actual->sig) {
			nodo = nodo_actual->sig;
			free(nodo_actual);
			nodo_actual = nodo;
		}

		free(nodo_actual);
	}

	free(cola);
}

// Verifica si una cola tiene o no elementos.
// PRE: 'cola' es una cola existente.
// POST: devuelve true si la cola esta vacía o false en su defecto.
bool cola_esta_vacia(const cola_t *cola) {
	return (!cola->primero);
}

// Agrega un nuevo elemento a la cola.
// PRE: la cola fue creada.
// POST: se agregó un nuevo elemento a la cola, valor se encuentra al final
// de la cola. Devuelve true si la acción se llevo a cabo con éxito o false
// en caso de error.
bool cola_encolar(cola_t *cola, const cola_dato_t valor) {
	// Solicitamos espacio en memoria para el nuevo nodo.
	nodo_cola_t* nodo = (nodo_cola_t*) malloc(sizeof(nodo_cola_t));
	if(!nodo) return false;

	// Guardamos valor en el nodo.
	nodo->dato = valor;
	nodo->sig = NULL;

	// Enlazamos el nodo al final de la cola.
	if (cola->primero)
		cola->ultimo->sig = nodo;
	else
		cola->primero = nodo;

	cola->ultimo = nodo;

	return true;
}

// Obtiene el valor del primer elemento de la cola. 
// PRE: 'cola' es una cola existente; 'valor' es un dirección de memoria
// válida donde se puede escribir.
// POST: Si la cola tiene elementos, el valor del primero se copia en *valor 
// y devuelve true. Si está vacía devuelve false.
bool cola_ver_primero(const cola_t *cola, cola_dato_t *valor) {
	if (!cola->primero) return false;

	*valor = cola->primero->dato;

	return true;
}

// Saca el primer elemento de la cola.
// PRE: 'cola' es una cola existente; 'valor' es un dirección de memoria
// válida donde se puede escribir.
// POST: 'valor' contiene el valor del primer elemento anterior, la cola
// contiene un elemento menos (si la cola no estaba vacía). Devuelve true 
// si la acción se llevo a cabo con éxito o false en caso de error.
bool cola_desencolar(cola_t *cola, cola_dato_t *valor) {
	if(!cola->primero) return false;
	
	// Tomamos dato del nodo y lo guardamos en valor.
	nodo_cola_t *nodo = cola->primero;
	*valor = nodo->dato;
	
	// Desenlazamos nodo y liberamos memoria.
	if(nodo->sig)
		cola->primero = nodo->sig;
	else
		cola->primero = cola->ultimo = NULL;

	free(nodo);

	return true;
}
