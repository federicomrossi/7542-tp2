/* ******************************************************************
 * ******************************************************************
 * TAD LISTA ENLAZADA
 * ..................................................................
 *
 * Implementación de una lista simplemente enlazada, incluyendo como 
 * primitivas a las operaciones básicas de estas.
 *
 * ******************************************************************
 * ******************************************************************/


#ifndef LISTA_H
#define LISTA_H

#include <stdbool.h>



/* ******************************************************************
 * DECLARACIÓN DE LOS TIPOS DE DATOS
 * *****************************************************************/

#ifndef LISTA_DATO_T
// Para especificar el tipo de datos que manejará la lista, copie
// las siguientes dos líneas en su código, justo antes de incluir
// el presente header. Reemplace void* por el tipo que usted prefiera.
#define LISTA_DATO_T
typedef void* lista_dato_t;
#endif


typedef struct _lista_t lista_t;
typedef struct _lista_iter_t lista_iter_t;



/* ******************************************************************
 * PRIMITIVAS BÁSICAS
 * *****************************************************************/

// Crea una lista enlazada.
// POST: Devuelve un puntero a una lista vacía o NULL si no se ha 
// podido llevar a cabo la creación del mismo.
lista_t* lista_crear();

// Verifica si una lista se encuentra vacía.
// PRE: 'lista' es una lista existente.
// POST: Devuelve verdadero si la lista se encuentra vacía o falso en 
// si tiene elementos.
bool lista_esta_vacia(const lista_t *lista);

// Devuelve el largo de la lista.
// PRE: 'lista' es una lista existente.
size_t lista_largo(const lista_t *lista);

// Inserta un elemento al principio de la lista.
// PRE: 'lista' es una lista existente; 'dato' es el elemento a 
// insertar.
// POST: devuelve true si se realizó la acción con éxito o falso en
// caso contrario.
bool lista_insertar_primero(lista_t *lista, const lista_dato_t dato);

// Inserta un elemento al final de la lista.
// PRE: 'lista' es una lista existente; 'dato' es el elemento a 
// insertar.
// POST: devuelve true si se realizó la acción con éxito o falso en
// caso contrario.
bool lista_insertar_ultimo(lista_t *lista, const lista_dato_t dato);

// Obtiene el primer elemento de la lista.
// PRE: 'lista' es una lista existente; 'dato' es un puntero a
// la variable que recibirá el dato.
// POST: si la lista posee elementos, se asocia el primero de esta
// con 'dato' y se devuelve verdadero. Si se encuentra vacía se
// devuelve falso.
bool lista_ver_primero(const lista_t *lista, lista_dato_t *dato);

// Obtiene el último elemento de la lista.
// PRE: 'lista' es una lista existente; 'dato' es un puntero a
// la variable que recibirá el dato.
// POST: si la lista posee elementos, se asocia el último de esta
// con 'dato' y se devuelve verdadero. Si se encuentra vacía se
// devuelve falso.
bool lista_ver_ultimo(const lista_t *lista, lista_dato_t *dato);

// Borra el primer elemento de la lista. 
// PRE: 'lista' es una lista existente; 'dato' es un puntero a
// la variable que recibirá el dato.
// POST: si la lista tiene elementos, se quita el primero, se copia 
// en 'dato' y se devuelve verdadero. Si la lista está vacía, devuelve 
// falso.
bool lista_borrar_primero(lista_t *lista, lista_dato_t *dato);

// Destruye la lista enlazada.
// PRE: 'lista' es una lista existente; 'destruir_dato' es una función
// que se encarga de destruir los datos (e.g.: free()). En caso de que 
// los datos no necesiten ser destruidos se debe pasar NULL.
// POST: se eliminó la lista y todos sus elementos.
void lista_destruir(lista_t *lista, void destruir_dato(lista_dato_t));




/* ******************************************************************
 * PRIMITIVAS DE ITERACIÓN
 * *****************************************************************/

// Crea un iterador para una lista.
// PRE: 'lista' es una lista existente;
// POST: se devuelve un iterador nuevo o NULL si no se ha podido 
// llevar a cabo la creación del mismo.
lista_iter_t* lista_iter_crear(const lista_t* lista);

// Avanza sobre la lista.
// PRE: 'iter' es un iterador existente
// POST: se devuelve true si se avanzó sobre la lista o false en caso
// contrario.
bool lista_iter_avanzar(lista_iter_t *iter);

// Obtiene el dato de la posición actual del iterador.
// PRE: 'iter' es un iterador existente; 'dato' es un puntero a la
// variable que recibirá el dato.
// POST: si la lista posee elementos, se asocia el dato de la posición
// actual del iterador con 'dato' y se devuelve verdadero. En caso
// contrario se devuelve false.
bool lista_iter_ver_actual(const lista_iter_t *iter, lista_dato_t *dato);

// Verifica si el iterador llegó al final de la lista.
// PRE: 'iter' es un iterador existente.
// POST: se devuelve true si el iterador llegó al final de la lista o
// false en caso contrario
bool lista_iter_al_final(const lista_iter_t *iter);

// Destruye el iterador.
// PRE: 'iter' es un iterador existente.
void lista_iter_destruir(lista_iter_t *iter);




/* ******************************************************************
 * PRIMITIVAS DE LA LISTA PARA EL ITERADOR
 * *****************************************************************/

// Inserta un dato en la lista a la izquierda de la posición en la que
// se encuentra el iterador.
// PRE: 'lista' es una lista existente; 'iter' es un iterador existente
// y perteneciente a 'lista'; 'dato' es el elemento a insertar.
// POST: devuelve true si se realizó la acción con éxito o falso en
// caso contrario. El iterador no modifica su posicionamiento.
bool lista_insertar(lista_t *lista, lista_iter_t *iter, 
	const lista_dato_t dato);

// Elimina el elemento de la lista sobre el cual se encuentra posicionado 
// el iterador.
// PRE: 'lista' es una lista existente; 'iter' es un iterador existente
// y perteneciente a 'lista'; 'dato' es un puntero a la variable que 
// recibirá el dato.
// POST: 'dato' contiene el dato de la posición que se eliminó. El itera
// dor avanzó hacia el siguiente elemento de la lista. En caso de ser
// exitosa la acción se devuelve true o false en caso contrario.
bool lista_borrar(lista_t *lista, lista_iter_t *iter, lista_dato_t *dato);

#endif
