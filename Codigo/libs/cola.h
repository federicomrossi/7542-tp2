/* ******************************************************************
 * ******************************************************************
 * TAD COLA
 * ..................................................................
 * Implementaci�n del TDA Cola, la cual consta de un conjunto de 
 * primitivas b�sicas para su uso.
 * La cola est� planteada como una cola de punteros, pero puede manejar
 * otros tipos de datos definiendo el tipo de datos en el c�digo
 * principal
 *
 * ******************************************************************
 * ******************************************************************/


#ifndef COLA_H
#define COLA_H

#include <stdbool.h>
#include <stddef.h>


/* ******************************************************************
 *                DEFINICION DE LOS TIPOS DE DATOS
 * *****************************************************************/

#ifndef COLA_DATO_T
#define COLA_DATO_T
typedef void* cola_dato_t;
#endif

typedef struct _cola_t cola_t;



/* ******************************************************************
 *                    PRIMITIVAS DE LA COLA
 * *****************************************************************/

// Crea una cola.
// POST: devuelve una nueva cola vac�a o NULL si no se ha podido
// llevar a cabo la creaci�n de la misma.
cola_t* cola_crear();

// Destruye la cola.
// PRE: la cola fue creada.
// POST: se eliminaron todos los elementos de la cola.
void cola_destruir(cola_t *cola);

// Devuelve verdadero o falso seg�n si la cola tiene o no elementos
// encolados respectivamente.
// PRE: la cola fue creada.
// POST: devuelve True o False.
bool cola_esta_vacia(const cola_t *cola);

// Agrega un nuevo elemento a la cola. Devuelve falso en caso de error.
// PRE: la cola fue creada.
// POST: se agreg� un nuevo elemento a la cola, valor se encuentra al final
// de la cola.
bool cola_encolar(cola_t *cola, const cola_dato_t valor);

// Obtiene el valor del primer elemento de la cola. Si la cola tiene
// elementos, el valor del primero se copia en *valor y devuelve verdadero.
// Si est� vac�a devuelve falso.
// PRE: la cola fue creada, valor es un direcci�n de memoria v�lida donde se
// puede escribir.
// POST: valor contiene el valor del primer elemento de la cola, cuando la
// cola no est� vac�a.
bool cola_ver_primero(const cola_t *cola, cola_dato_t *valor);

// Saca el primer elemento de la cola. Si la cola tiene elementos, se quita el
// primero de la cola, se copia el valor en *valor y devuelve verdadero. Si la
// cola est� vac�a, devuelve falso.
// PRE: la cola fue creada, valor es un direcci�n de memoria v�lida donde se
// puede escribir.
// POST: valor contiene el valor del primer elemento anterior, la cola
// contiene un elemento menos, si la cola no estaba vac�a.
bool cola_desencolar(cola_t *cola, cola_dato_t *valor);

#endif
