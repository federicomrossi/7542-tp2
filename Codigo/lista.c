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


#include <stdio.h>
#include <stdlib.h>
#include "lista.h"



/* ******************************************************************
 * DEFINICIÓN DE LOS TIPOS DE DATOS
 * *****************************************************************/

// Tipo que representa a un nodo de la lista
typedef struct _nodo_lista_t
{
	lista_dato_t dato;			// Dato que almacena el nodo.
	struct _nodo_lista_t* sig;	// Puntero al nodo siguiente.

} nodo_lista_t;

// Tipo que representa a una lista
struct _lista_t
{
	nodo_lista_t* primero; // Puntero al primer elemento de la lista
	nodo_lista_t* ultimo;  // Puntero al último elemento de la lista
	size_t largo;          // Cantidad de elementos que tiene la lista
};

// Tipo que representa a un iterador de la lista 
struct _lista_iter_t
{
	nodo_lista_t* act;		// Puntero a la posición actual del iterador
	nodo_lista_t* ant;		// Puntero al elemento anterior del iterador
};



/* ******************************************************************
 * FUNCIONES AUXILIARES
 * *****************************************************************/

// Función que crea un nodo.
// POST: se devuelve un puntero al nodo o NULL si no se ha podido 
// llevar a cabo la creación del mismo.
nodo_lista_t* lista_crear_nodo()
{
	nodo_lista_t* nodo = (nodo_lista_t*) malloc(sizeof(nodo_lista_t));
	if(!nodo) return NULL;
	return nodo;
}



/* ******************************************************************
 * PRIMITIVAS BÁSICAS
 * *****************************************************************/

// Crea una lista enlazada.
// POST: Devuelve un puntero a una lista vacía o NULL si no se ha 
// podido llevar a cabo la creación del mismo.
lista_t* lista_crear()
{
	// Solicitamos espacio en memoria para la lista
	lista_t* lista = (lista_t*) malloc(sizeof(lista_t));
	if(! lista) return NULL;

	// Seteamos parámetros iniciales de la lista
	lista->primero = NULL;
	lista->ultimo = NULL;
	lista->largo = 0;

	return lista;
}

// Verifica si una lista se encuentra vacía.
// PRE: 'lista' es una lista existente.
// POST: Devuelve verdadero si la lista se encuentra vacía o falso en 
// si tiene elementos.
bool lista_esta_vacia(const lista_t *lista)
{
	return (lista->largo == 0);
}

// Devuelve el largo de la lista.
// PRE: 'lista' es una lista existente.
size_t lista_largo(const lista_t *lista)
{
	return lista->largo;
}

// Inserta un elemento al principio de la lista.
// PRE: 'lista' es una lista existente; 'dato' es el elemento a 
// insertar.
// POST: devuelve true si se realizó la acción con éxito o falso en
// caso contrario.
bool lista_insertar_primero(lista_t *lista, const lista_dato_t dato)
{
	// Creamos un nuevo nodo
	nodo_lista_t* nodo = lista_crear_nodo();
	if(! nodo) return false;
	
	// Seteamos los campos del nodo
	nodo->dato = dato;
	nodo->sig = lista->primero;
	lista->primero = nodo;
	
	// Si no hay ningún elemento, el primero también es el último
	if(! lista->largo) lista->ultimo = nodo;
	lista->largo++;
	
	return true;
}

// Inserta un elemento al final de la lista.
// PRE: 'lista' es una lista existente; 'dato' es el elemento a 
// insertar.
// POST: devuelve true si se realizó la acción con éxito o falso en
// caso contrario.
bool lista_insertar_ultimo(lista_t *lista, const lista_dato_t dato)
{
	// Creamos un nuevo nodo
	nodo_lista_t* nodo = lista_crear_nodo();
	if(! nodo) return false;
	
	// Seteamos los campos del nodo
	nodo->dato = dato;
	nodo->sig = NULL;
	
	// Si no hay elementos, el último también es el primero
	if(! lista->ultimo)
		lista->primero = nodo;
	// Sino, insertamos el nuevo nodo a continuación del que 
	// se encontraba último
	else
		lista->ultimo->sig = nodo;

	lista->ultimo = nodo;
	lista->largo++;
	
	return true;
}

// Obtiene el primer elemento de la lista.
// PRE: 'lista' es una lista existente; 'dato' es un puntero a
// la variable que recibirá el dato.
// POST: si la lista posee elementos, se asocia el primero de esta
// con 'dato' y se devuelve verdadero. Si se encuentra vacía se
// devuelve falso.
bool lista_ver_primero(const lista_t *lista, lista_dato_t *dato)
{
	if (lista->largo == 0) return false;
	
	*dato = lista->primero->dato;
	
	return true;
}

// Obtiene el último elemento de la lista.
// PRE: 'lista' es una lista existente; 'dato' es un puntero a
// la variable que recibirá el dato.
// POST: si la lista posee elementos, se asocia el último de esta
// con 'dato' y se devuelve verdadero. Si se encuentra vacía se
// devuelve falso.
bool lista_ver_ultimo(const lista_t *lista, lista_dato_t *dato)
{
	if (lista->largo == 0) return false;
	
	*dato = lista->ultimo->dato;
	
	return true;
}

// Borra el primer elemento de la lista. 
// PRE: 'lista' es una lista existente; 'dato' es un puntero a
// la variable que recibirá el dato.
// POST: si la lista tiene elementos, se quita el primero, se copia 
// en 'dato' y se devuelve verdadero. Si la lista está vacía, devuelve 
// falso.
bool lista_borrar_primero(lista_t *lista, lista_dato_t *dato)
{
	if (lista->largo == 0) return false;
	
	// Tomamos el nodo a borrar y apuntamos 'dato' al dato del nodo.
	nodo_lista_t* nodo_borrar = lista->primero;
	*dato = lista->primero->dato;
	
	// El segundo elemento pasa a ser el primero
	lista->primero = lista->primero->sig;
	lista->largo--;
	
	// Liberamos la memoria usada por el nodo.
	free(nodo_borrar);
	
	// Verificamos si quedan mas elementos en la lista
	if (lista->largo == 0) lista->ultimo = NULL;	
	
	return true;
}

// Destruye la lista enlazada. El parámetro 
// PRE: 'lista' es una lista existente; 'destruir_dato' es una función
// que se encarga de destruir los datos (e.g.: free()). En caso de que 
// los datos no necesiten ser destruidos se debe pasar NULL.
// POST: se eliminó la lista y todos sus elementos.
void lista_destruir(lista_t *lista, void destruir_dato(lista_dato_t))
{
	nodo_lista_t* nodo;
	
	// Recorremos los nodos y los destruimos
	while(lista->primero)
	{
		nodo = lista->primero;
		lista->primero = nodo->sig;
		
		// Si se especificó una función para destruir los datos, 
		// la usamos
		if(destruir_dato) destruir_dato(nodo->dato);
		free(nodo);
	}
	
	free(lista);
}



/* ******************************************************************
 * PRIMITIVAS DE ITERACIÓN
 * *****************************************************************/

// Crea un iterador para una lista.
// PRE: 'lista' es una lista existente;
// POST: se devuelve un iterador nuevo o NULL si no se ha podido 
// llevar a cabo la creación del mismo.
lista_iter_t* lista_iter_crear(const lista_t* lista)
{
	// Solicitamos espacio en memoria para el iterador
	lista_iter_t* iter = (lista_iter_t*) malloc(sizeof(lista_iter_t));
	if(! iter) return NULL;

	// Seteamos parámetros iniciales del iterador
	iter->ant = NULL;
	iter->act = lista->primero;

	return iter;
}

// Avanza sobre la lista.
// PRE: 'iter' es un iterador existente
// POST: se devuelve true si se avanzó sobre la lista o false en caso
// contrario.
bool lista_iter_avanzar(lista_iter_t *iter)
{
	if (!iter->act) return false;
	
	iter->ant = iter->act;
	iter->act = iter->act->sig;
	
	return true;	
}

// Obtiene el dato de la posición actual del iterador.
// PRE: 'iter' es un iterador existente; 'dato' es un puntero a la
// variable que recibirá el dato.
// POST: si la lista posee elementos, se asocia el dato de la posición
// actual del iterador con 'dato' y se devuelve verdadero. En caso
// contrario se devuelve false.
bool lista_iter_ver_actual(const lista_iter_t *iter, lista_dato_t *dato)
{
	if (iter->act == NULL) return false;
	
	*dato = iter->act->dato;
	
	return true;
}

// Verifica si el iterador llegó al final de la lista.
// PRE: 'iter' es un iterador existente.
// POST: se devuelve true si el iterador llegó al final de la lista o
// false en caso contrario
bool lista_iter_al_final(const lista_iter_t *iter)
{
	return !iter->act;
}

// Destruye el iterador.
// PRE: 'iter' es un iterador existente.
void lista_iter_destruir(lista_iter_t *iter)
{
	free(iter);
}



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
	const lista_dato_t dato)
{
	// Creamos un nuevo nodo
	nodo_lista_t* nodo = lista_crear_nodo();
	if(! nodo) return false;
	
	// Seteamos los campos del nodo
	nodo->dato = dato;
	nodo->sig = iter->act;
	
	// Ubicamos el nodo
	if(!iter->ant)
		lista->primero = nodo;
	else		
		iter->ant->sig = nodo;
	if(lista_iter_al_final(iter)) lista->ultimo = nodo;
	iter->act = nodo;
	
	lista->largo++;
	
	return true;
}

// Elimina el elemento de la lista sobre el cual se encuentra posicionado 
// el iterador.
// PRE: 'lista' es una lista existente; 'iter' es un iterador existente
// y perteneciente a 'lista'; 'dato' es un puntero a la variable que 
// recibirá el dato.
// POST: 'dato' contiene el dato de la posición que se eliminó. El itera
// dor avanzó hacia el siguiente elemento de la lista. En caso de ser
// exitosa la acción se devuelve true o false en caso contrario.
bool lista_borrar(lista_t *lista, lista_iter_t *iter, lista_dato_t *dato)
{
	// Verificamos si el iterador se encuentra al final de la lista
	if(lista_iter_al_final(iter)) return false;
	
	// Enviamos el dato a la variable de salida 'dato'
	nodo_lista_t* nodo_act = iter->act;
	*dato = nodo_act->dato;
	
	// Movemos el iterador al siguiente elemento
	iter->act = nodo_act->sig;
	
	// Desvinculamos el nodo y lo liberamos
	if(nodo_act == lista->primero) lista->primero = nodo_act->sig;
	if(nodo_act == lista->ultimo) lista->ultimo = iter->ant;
	if(iter->ant) iter->ant->sig = iter->act;
	lista->largo--;
	
	free(nodo_act);
	return true;
}
