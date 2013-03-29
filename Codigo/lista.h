#ifndef LISTA_H
#define LISTA_H

#include <stdbool.h>

/* ******************************************************************
 *                DEFINICION DE LOS TIPOS DE DATOS
 * *****************************************************************/

/* La lista está planteada como una lista de punteros, pero puede 
 * manejar otros tipos de datos definiendo el tipo de datos en el código
 * principal. */
#ifndef LISTA_DATO_T
#define LISTA_DATO_T
typedef void* lista_dato_t;
#endif

typedef struct _lista_t lista_t;
typedef struct _lista_iter_t lista_iter_t;




/* ******************************************************************
 *                  	 PRIMITIVAS BÁSICAS
 * *****************************************************************/

// Crea una lista enlazada.
// POST: Devuelve un puntero a una lista vacía.
lista_t* lista_crear();

// Devuelve verdadero si la lista esta vacía o falso si tiene elementos.
// PRE: la lista fue creada.
bool lista_esta_vacia(const lista_t *lista);

// Devuelve el largo de la lista.
// PRE: La lista fue creada.
size_t lista_largo(const lista_t *lista);

// Inserta el elemento al principio de la lista. Devuelve falso en
// caso de error.
// PRE: La lista fue creada.
// POST: Se agregó un nuevo elemento, en la pimera posición de la lista.
bool lista_insertar_primero(lista_t *lista, const lista_dato_t dato);

// Inserta el elemento al final de la lista. Devuelve falso en caso de
// error.
// PRE: La lista fue creada.
// POST: Se agregó un nuevo elemento, en la última posición de la lista.
bool lista_insertar_ultimo(lista_t *lista, const lista_dato_t dato);

// Obtiene el primer elemento de la lista. Si la lista tiene
// elementos, el primero se copia en *dato y devuelve verdadero.
// Si está vacía devuelve falso.
// PRE: la lista fue creada, dato es un dirección de memoria válida
// donde se puede escribir.
// POST: dato contiene el primer elemento de la lista, cuando
// ésta no está vacía.
bool lista_ver_primero(const lista_t *lista, lista_dato_t *dato);

// Obtiene el último elemento de la lista. Si la lista tiene
// elementos, el último se copia en *dato y devuelve verdadero.
// Si está vacía devuelve falso.
// PRE: la lista fue creada, dato es un dirección de memoria válida 
// donde se puede escribir.
// POST: dato contiene el último elemento de la lista, cuando
// ésta no está vacía.
bool lista_ver_ultimo(const lista_t *lista, lista_dato_t *dato);

// Saca el primer elemento de la lista. Si ésta tiene elementos, se 
// quita el primero, se copia en *dato y devuelve verdadero. Si la lista 
// está vacía, devuelve falso.
// PRE: la lista fue creada, dato es un dirección de memoria válida 
// donde se puede escribir.
// POST: Si la lista no estaba vacía, dato contiene el primer elemento, 
// y éste se quita de la lista. El elemento que le sigue pasa a ser el
//primero
bool lista_borrar_primero(lista_t *lista, lista_dato_t *dato);

// Destruye la lista. El parámetro destruir_dato es una función que se
// encarga de destruir los datos. En caso de que los datos no necesiten
// ser destruidos se pasa NULL, caso contrario se pasa free o una
// función que se encargue de destruir los datos.
// PRE: la lista fue creada.
// POST: se eliminaron la lista y todos sus elementos.
void lista_destruir(lista_t *lista, void destruir_dato(lista_dato_t));




/* ******************************************************************
 *                     PRIMITIVAS DE ITERACIÓN
 * *****************************************************************/

// Crea un iterador para una lista.
// PRE: la lista fue creada.
// POST: devuelve un iterador nuevo.
lista_iter_t* lista_iter_crear(const lista_t* lista);

// Avanza sobre la lista. Devuelve verdadero si avanzó.
// PRE: El iterador fue creado.
// POST: Se avanzó sobre la lista, devuelve verdadero. En caso contrario
// devuelve falso.
bool lista_iter_avanzar(lista_iter_t *iter);

// Obtiene el valor del dato de la posición donde se encuentra el  
// iterador. Si la lista tiene elementos, el valor correspondiente a esa 
// posición se copia en *dato y devuelve verdadero. En caso contrario
// se devuelve falso.
// PRE: el iterador fue creado, dato es un dirección de memoria válida 
// donde se puede escribir.
// POST: dato contiene el valor de la posición en la que se encuentra el
// iterador.
bool lista_iter_ver_actual(const lista_iter_t *iter, lista_dato_t *dato);

// Devuelve verdadero o falso, según si el iterador llego al final de 
// la lista o no.
// PRE: el iterador fue creado.
bool lista_iter_al_final(const lista_iter_t *iter);

// Destruye el iterador.
// PRE: el iterador fue creado.
void lista_iter_destruir(lista_iter_t *iter);




/* ******************************************************************
 *             PRIMITIVAS DE LISTAS JUNTO CON ITERADOR
 * *****************************************************************/

// Inserta un dato en la lista a la izquierda de la posición en la que
// se encuentra el iterador. Devuelve verdadero si se agregó el dato y 
// falso en caso contrario.
// Pre: la lista y el iterador fueron creados.
// Post: el dato fue insertado a la izquierda de la posición en la que
// se encontraba el iterador. El iterador no modifica su 
// posicionamiento.
bool lista_insertar(lista_t *lista, lista_iter_t *iter, const lista_dato_t dato);

// Elimina el elemento de la lista sobre el cual se encuentra
// posicionado el iterador. Devuelve verdader si se borro correctamente
// y falso en caso contrario.
// Pre: la lista y el iterador fueron creados.
// Post: dato contiene el valor de la posicion que se elimino. El itera
// dor avanzó hacia el elemento siguiente de la lista.
bool lista_borrar(lista_t *lista, lista_iter_t *iter, lista_dato_t *dato);


#endif
