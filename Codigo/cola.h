/* ******************************************************************
 * ******************************************************************
 * TAD COLA
 * ..................................................................
 * Implementación del TDA Cola, la cual consta de un conjunto de 
 * primitivas básicas para su uso.
 *
 * ******************************************************************
 * ******************************************************************/


#ifndef COLA_H
#define COLA_H

#include <stdbool.h>
#include <stddef.h>


/* ******************************************************************
 * DECLARACIÓN DE LOS TIPOS DE DATOS
 * *****************************************************************/

#ifndef COLA_DATO_T
// Para especificar el tipo de datos que manejará la cola, copie
// las siguientes dos líneas en su código, justo antes de incluir
// el presente header. Reemplace void* por el tipo que usted prefiera.
#define COLA_DATO_T
typedef void* cola_dato_t;
#endif

typedef struct _cola_t cola_t;



/* ******************************************************************
 * PRIMITIVAS DE LA COLA
 * *****************************************************************/

// Crea una cola.
// POST: devuelve una nueva cola vacía o NULL si no se ha podido
// llevar a cabo la creación de la misma.
cola_t* cola_crear();

// Destruye la cola.
// PRE: 'cola' es una cola existente.
// POST: se eliminaron todos los elementos de la cola.
void cola_destruir(cola_t *cola);

// Verifica si una cola tiene o no elementos.
// PRE: 'cola' es una cola existente.
// POST: devuelve true si la cola esta vacía o false en su defecto.
bool cola_esta_vacia(const cola_t *cola);

// Agrega un nuevo elemento a la cola.
// PRE: la cola fue creada.
// POST: se agregó un nuevo elemento a la cola, valor se encuentra al final
// de la cola. Devuelve true si la acción se llevo a cabo con éxito o false
// en caso de error.
bool cola_encolar(cola_t *cola, const cola_dato_t valor);

// Obtiene el valor del primer elemento de la cola. 
// PRE: 'cola' es una cola existente; 'valor' es un dirección de memoria
// válida donde se puede escribir.
// POST: Si la cola tiene elementos, el valor del primero se copia en *valor 
// y devuelve true. Si está vacía devuelve false.
bool cola_ver_primero(const cola_t *cola, cola_dato_t *valor);

// Saca el primer elemento de la cola.
// PRE: 'cola' es una cola existente; 'valor' es un dirección de memoria
// válida donde se puede escribir.
// POST: 'valor' contiene el valor del primer elemento anterior, la cola
// contiene un elemento menos (si la cola no estaba vacía). Devuelve true 
// si la acción se llevo a cabo con éxito o false en caso de error.
bool cola_desencolar(cola_t *cola, cola_dato_t *valor);

#endif
