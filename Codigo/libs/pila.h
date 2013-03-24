#ifndef PILA_H
#define PILA_H

#include <stdbool.h>
#include <stddef.h>



/* ******************************************************************
 *                DEFINICION DE LOS TIPOS DE DATOS
 * *****************************************************************/

/* La pila est� planteada como una pila de enteros, pero puede manejar 
 * otros tipos de datos cambiando la siguiente l�nea. */
typedef int pila_dato_t;

typedef struct pila
{
    size_t tamanio;     // Tama�o actual del vector datos
	size_t cantidad;    // Cantidad actual de apilados 
    pila_dato_t *datos; // Vector de datos
} pila_t;



/* ******************************************************************
 *                    PRIMITIVAS DE LA PILA
 * *****************************************************************/

// Crea una pila.
// POST: devuelve una nueva pila vac�a.
pila_t* pila_crear();

// Destruye la pila.
// PRE: la pila fue creada.
// POST: se eliminaron todos los elementos de la pila.
void pila_destruir(pila_t *pila);

// Devuelve verdadero o falso, seg�n si la pila tiene o no elementos apilados.
// PRE: la pila fue creada.
bool pila_esta_vacia(const pila_t *pila);

// Agrega un nuevo elemento a la pila. Devuelve falso en caso de error.
// PRE: la pila fue creada.
// POST: se agreg� un nuevo elemento a la pila, valor es el nuevo tope.
bool pila_apilar(pila_t *pila, const pila_dato_t valor);

// Obtiene el valor del tope de la pila. Si la pila tiene elementos, el valor
// de tope se copia en *valor y devuelve verdadero. Si est� vac�a devuelve
// falso.
// PRE: la pila fue creada, valor es un direcci�n de memoria v�lida donde se
// puede escribir.
// POST: valor contiene el valor del tope de la pila, cuando la pila no est�
// vac�a.
bool pila_ver_tope(const pila_t *pila, pila_dato_t *valor);

// Saca el elemento tope de la pila. Si la pila tiene elementos, se quita el
// tope de la pila, se copia el valor en *valor y devuelve verdadero. Si la
// pila est� vac�a, devuelve falso.
// PRE: la pila fue creada, valor es un direcci�n de memoria v�lida donde se
// puede escribir.
// POST: valor contiene el valor del tope anterior, la pila contiene un
// elemento menos, si la pila no estaba vac�a.
bool pila_desapilar(pila_t *pila, pila_dato_t *valor);

#endif // PILA_H
