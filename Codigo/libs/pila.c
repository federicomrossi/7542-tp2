
#include <stdio.h>
#include "pila.h"
#include <stdlib.h>

#define TAM_INICIAL 5	//Setea el tamaño incial de la pila


/* ******************************************************************
 *                         FUNCIONES AUXILIARES
 * *****************************************************************/

//Función para redimensionar la pila.
//PRE: la pila fue creada.
//POST: cambia el tamaño de la pila a nuevo_tam y devuelve true, o deja 
//intacta la pila y devuelve false si no se pudo cambiar el tamaño
bool redimensionar_pila(pila_t *pila, size_t nuevo_tam)
{
	pila_dato_t* datos_nuevo = realloc(pila->datos, nuevo_tam * sizeof(pila_dato_t));
	
	if(! datos_nuevo) return false;
		
	pila->datos = datos_nuevo;
	pila->tamanio = nuevo_tam;
	return true;
}

//Función que devuelve el tamaño de la pila
//PRE: la pila fue creada
size_t obtener_tamanio(pila_t *pila)
{
	return pila->tamanio;
}


/* ******************************************************************
 *                         IMPLEMENTACIÓN
 * *****************************************************************/

// Crea una pila.
// POST: devuelve una nueva pila vacía.
pila_t* pila_crear()
{
	pila_t* pila = (pila_t*) malloc(sizeof(pila_t));
	if(! pila) return NULL;
	
	pila->datos = (pila_dato_t*) malloc(TAM_INICIAL * sizeof(pila_dato_t));
	
	if(! pila->datos)
	{
		free(pila);
		return NULL;
	}
	
	pila->tamanio = TAM_INICIAL;
	pila->cantidad = 0;
	
	return pila;
}

// Destruye la pila.
// PRE: la pila fue creada.
// POST: se eliminaron todos los elementos de la pila.
void pila_destruir(pila_t *pila)
{
	free(pila->datos);
	free(pila);
}

// Devuelve verdadero o falso, según si la pila tiene o no elementos apilados.
// PRE: la pila fue creada.
bool pila_esta_vacia(const pila_t *pila)
{
	//Si la pila no tiene elementos, cantidad=0
	if(! pila->cantidad) return true; 
	
	return false;
}

// Agrega un nuevo elemento a la pila. Devuelve falso en caso de error.
// PRE: la pila fue creada.
// POST: se agregó un nuevo elemento a la pila, valor es el nuevo tope.
bool pila_apilar(pila_t *pila, const pila_dato_t valor)
{
	//Si se alcanza la cantidad máxima de elementos se duplica el tamaño de la pila
	if(pila->cantidad == (pila->tamanio -1)) 
	{
		if(! redimensionar_pila(pila, pila->tamanio + TAM_INICIAL)) return false;
	}
	
	pila->datos[pila->cantidad] = valor;
	pila->cantidad++;
	
	return true;
}

// Obtiene el valor del tope de la pila. Si la pila tiene elementos, el valor
// de tope se copia en *valor y devuelve verdadero. Si está vacía devuelve
// falso.
// PRE: la pila fue creada, valor es un dirección de memoria válida donde se
// puede escribir.
// POST: valor contiene el valor del tope de la pila, cuando la pila no está
// vacía.
bool pila_ver_tope(const pila_t *pila, pila_dato_t *valor)
{
	if(! pila->cantidad) return false;
	
	*valor = pila->datos[pila->cantidad -1];
	return true;
}

// Saca el elemento tope de la pila. Si la pila tiene elementos, se quita el
// tope de la pila, se copia el valor en *valor y devuelve verdadero. Si la
// pila está vacía, devuelve falso.
// PRE: la pila fue creada, valor es un dirección de memoria válida donde se
// puede escribir.
// POST: valor contiene el valor del tope anterior, la pila contiene un
// elemento menos, si la pila no estaba vacía.
bool pila_desapilar(pila_t *pila, pila_dato_t *valor)
{
	//Si la pila tiene menos de la mitad de los elementos se redimensiona para
	//no malgastar memoria.
	if(pila->cantidad < (pila->tamanio - TAM_INICIAL)) 
	{
		if(! redimensionar_pila(pila, pila->tamanio - TAM_INICIAL)) return false;
	}
	
	if(! pila->cantidad) return false;
	
	*valor = pila->datos[pila->cantidad - 1];
	pila->cantidad--;
	
	return true;
}
