
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "lista.h"



/* ******************************************************************
 *                DEFINICION DE LOS TIPOS DE DATOS
 * *****************************************************************/

typedef struct _nodo_lista_t
{
	lista_dato_t dato;			// Dato que almacena el nodo.
	struct _nodo_lista_t* sig;	// Puntero hacia el nodo siguiente.

} nodo_lista_t;


struct _lista_t
{
	nodo_lista_t* primero; // Puntero al primer elemento de la lista
	nodo_lista_t* ultimo;  // Puntero al último elemento de la lista
	size_t largo;          // Cantidad de elementos que tiene la lista
};


struct _lista_iter_t
{
	nodo_lista_t* ant;		// Puntero al elemento anterior del iterador
	nodo_lista_t* act;		// Puntero a la posición actual del iterador
};




/* ******************************************************************
 *                  	 PRIMITIVAS BÁSICAS
 * *****************************************************************/

// Crea una lista enlazada.
// Post: Devuelve un puntero a una lista vacía.
lista_t* lista_crear()
{
	lista_t* lista = (lista_t*) malloc(sizeof(lista_t));
	
	if(! lista) return NULL;

	lista->primero = NULL;
	lista->ultimo = NULL;
	lista->largo = 0;

	return lista;
}

// Devuelve verdadero si la lista esta vacía o falso si tiene elementos.
// Pre: la lista fue creada.
bool lista_esta_vacia(const lista_t *lista)
{
	return lista->largo == 0;
}

// Devuelve el largo de la lista.
// Pre: La lista fue creada.
size_t lista_largo(const lista_t *lista)
{
	return lista->largo;
}

// Inserta el elemento al principio de la lista. Devuelve falso en
// caso de error.
// Pre: La lista fue creada.
// Post: Se agregó un nuevo elemento, en la pimera posición de la lista.
bool lista_insertar_primero(lista_t *lista, const lista_dato_t dato)
{
	nodo_lista_t* nodo = (nodo_lista_t*) malloc(sizeof(nodo_lista_t));
	if(! nodo) return false;
	
	nodo->dato = dato;
	nodo->sig = lista->primero;
	lista->primero = nodo;
	
	// Si no hay ningún elemento, el primero también es el último
	if(! lista->largo) lista->ultimo = nodo;
	lista->largo++;
	
	return true;
}

// Inserta el elemento al final de la lista. Devuelve falso en caso de 
// error.
// Pre: La lista fue creada.
// Post: Se agregó un nuevo elemento, en la última posición de la lista.
bool lista_insertar_ultimo(lista_t *lista, const lista_dato_t dato)
{
	nodo_lista_t* nodo = (nodo_lista_t*) malloc(sizeof(nodo_lista_t));
	if(! nodo) return false;
	
	nodo->dato = dato;
	nodo->sig = NULL;
	
	//Si no hay elementos, el último también es el primero
	if(! lista->ultimo)
		lista->primero = nodo;
	//Si hay, pongo el nuevo nodo a continuación del que estaba último
	else
		lista->ultimo->sig = nodo;
	lista->ultimo = nodo;
	lista->largo++;
	
	return true;
}

// Obtiene el primer elemento de la lista. Si la lista tiene
// elementos, el primero se copia en *dato y devuelve verdadero.
// Si está vacía devuelve falso.
// Pre: la lista fue creada, dato es un dirección de memoria válida 
// donde se puede escribir.
// Post: dato contiene el primer elemento de la lista, cuando
// ésta no está vacía.
bool lista_ver_primero(const lista_t *lista, lista_dato_t *dato)
{
	if (lista->largo == 0) return false;
	
	*dato = lista->primero->dato;
	
	return true;
}

// Obtiene el último elemento de la lista. Si la lista tiene
// elementos, el último se copia en *dato y devuelve verdadero.
// Si está vacía devuelve falso.
// Pre: la lista fue creada, dato es un dirección de memoria válida 
// donde se puede escribir.
// Post: dato contiene el último elemento de la lista, cuando
// ésta no está vacía.
bool lista_ver_ultimo(const lista_t *lista, lista_dato_t *dato)
{
	if (lista->largo == 0) return false;
	
	*dato = lista->ultimo->dato;
	
	return true;
}

// Saca el primer elemento de la lista. Si ésta tiene elementos, se 
// quita el primero, se copia en *dato y devuelve verdadero. Si la lista 
// está vacía, devuelve falso.
// Pre: la lista fue creada, dato es un dirección de memoria válida 
// donde se puede escribir.
// Post: Si la lista no estaba vacía, dato contiene el primer elemento, 
// y éste se quita de la lista. El elemento que le sigue pasa a ser el
//primero
bool lista_borrar_primero(lista_t *lista, lista_dato_t *dato)
{
	if (lista->largo == 0) return false;
	
	// Tomamos el nodo a borrar y guardamos en *dato el dato de este.
	nodo_lista_t* nodo_borrar = lista->primero;
	*dato = lista->primero->dato;
	
	// El segundo elemento pasa a ser el primero y se decrementa 
	// el largo de la lista.
	lista->primero = lista->primero->sig;
	lista->largo--;
	
	// Liberamos la memoria usada por el nodo.
	free(nodo_borrar);
	
	// Si no quedan mas elementos en la lista, ultimo ya no debe apuntar
	// a ninguna posición de memoria.
	if (lista->largo == 0) lista->ultimo = NULL;	
	
	return true;
}

// Destruye la lista. El parámetro destruir_dato es una función que se
// encarga de destruir los datos. En caso de que los datos no necesiten
// ser destruidos se pasa NULL, caso contrario se pasa free o una
// función que se encargue de destruir los datos.
// Pre: la lista fue creada.
// Post: se eliminaron la lista y todos sus elementos.
void lista_destruir(lista_t *lista, void destruir_dato(lista_dato_t))
{
	nodo_lista_t* nodo;
	
	while(lista->primero)
	{
		nodo = lista->primero;
		lista->primero = nodo->sig;
		
		// Si hay una función para destruir los datos la uso
		if(destruir_dato) destruir_dato(nodo->dato);
		free(nodo);
	}
	
	free(lista);
}



/* ******************************************************************
 *                     PRIMITIVAS DE ITERACIÓN
 * *****************************************************************/

// Crea un iterador para una lista.
// Pre: la lista fue creada.
// Post: devuelve un iterador nuevo.
lista_iter_t* lista_iter_crear(const lista_t* lista)
{
	lista_iter_t* iter = (lista_iter_t*) malloc(sizeof(lista_iter_t));
	if(! iter) return NULL;

	iter->ant = NULL;
	iter->act = lista->primero;

	return iter;
}

// Avanza sobre la lista. Devuelve verdadero si avanzó.
// Pre: El iterador fue creado.
// Post: Se avanzó sobre la lista, devuelve verdadero. En caso contrario
// devuelve falso.
bool lista_iter_avanzar(lista_iter_t *iter)
{
	if (!iter->act) return false;
	
	iter->ant = iter->act;
	iter->act = iter->act->sig;
	
	return true;	
}

// Obtiene el valor del dato de la posición donde se encuentra el  
// iterador. Si la lista tiene elementos, el valor correspondiente a esa 
// posición se copia en *dato y devuelve verdadero. En caso contrario
// se devuelve falso.
// Pre: el iterador fue creado, dato es un dirección de memoria válida 
// donde se puede escribir.
// Post: dato contiene el valor de la posición en la que se encuentra el
// iterador.
bool lista_iter_ver_actual(const lista_iter_t *iter, lista_dato_t *dato)
{
	if (iter->act == NULL) return false;
	
	*dato = iter->act->dato;
	
	return true;
}

// Devuelve verdadero o falso, según si el iterador llego al final de 
// la lista o no.
// Pre: el iterador fue creado.
bool lista_iter_al_final(const lista_iter_t *iter)
{
	return !iter->act;
}

// Destruye el iterador.
// Pre: el iterador fue creado.
void lista_iter_destruir(lista_iter_t *iter)
{
	free(iter);
}



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
bool lista_insertar(lista_t *lista, lista_iter_t *iter, const lista_dato_t dato)
{
	nodo_lista_t* nodo = (nodo_lista_t*) malloc(sizeof(nodo_lista_t));
	if(! nodo) return false;
	
	nodo->dato = dato;
	nodo->sig = iter->act;
	
	if(!iter->ant)
		lista->primero = nodo;
	else		
		iter->ant->sig = nodo;
	if(lista_iter_al_final(iter)) lista->ultimo = nodo;
	iter->act = nodo;
	
	lista->largo++;
	
	return true;
}

// Elimina el elemento de la lista sobre el cual se encuentra
// posicionado el iterador. Devuelve verdader si se borro correctamente
// y falso en caso contrario.
// Pre: la lista y el iterador fueron creados.
// Post: dato contiene el valor de la posicion que se elimino. El itera
// dor avanzó hacia el elemento siguiente de la lista.
bool lista_borrar(lista_t *lista, lista_iter_t *iter, lista_dato_t *dato)
{
	if(lista_iter_al_final(iter)) return false;
	
	nodo_lista_t* nodo_act = iter->act;
	*dato = nodo_act->dato;
	
	iter->act = nodo_act->sig;
	
	if(nodo_act == lista->primero) lista->primero = nodo_act->sig;
	if(nodo_act == lista->ultimo) lista->ultimo = iter->ant;
	if(iter->ant) iter->ant->sig = iter->act;
	lista->largo--;
		
	free(nodo_act);
	return true;
}

