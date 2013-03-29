#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "hash_abierto.h"

#define LISTA_DATO_T
typedef nodo_hash_t* lista_dato_t;

#define PILA_DATO_T
typedef nodo_hash_t* pila_dato_t;

#include "lista.h"
#include "pila.h"




/* ******************************************************************
 *                DEFINICION DE LOS TIPOS DE DATOS
 * *****************************************************************/

struct _hash_t
{
	size_t tamanio;										// Tamaño del hash.
	size_t cantidad;									// Cantidad de elementos almacenados.
	lista_t **baldes;									// Puntero a la lista enlazada de claves.
	hash_destruir_dato_t (*destruir_dato)(hash_dato_t);	// Función para destruir el valor asociado a la clave.
};

struct _nodo_hash_t
{
	char* clave;					// Almacena la clave.
	hash_dato_t valor;				// Almacena el valor de la clave.
};

struct _hash_iter_t
{
	hash_t* hash;					// Puntero a la tabla de hash.
	size_t pos;						// Posición actual en la tabla.
	lista_iter_t* lista_iter;		// Puntero al iterador activo.
};




/* ******************************************************************
 *                  	FUNCIONES AUXILIARES
 * *****************************************************************/

// Función de Hashing.
// Recibe una cadena, se suman las equivalenticas en ASCII de cada
// caracter y se toma el módulo de dividir por la cantidad de cubetas
// del hash.
// Solo es de uso recomendable para claves que sean cadenas.
// Pre: el hash fue creado.
// Post: se devuelve una posición de balde.
size_t hashing_f(hash_t* hash, const char *cadena)
{
	int suma = 0;
	size_t cadena_tam = strlen(cadena);	
	
	for (int i = 0; i < cadena_tam; i++)
		suma = suma + cadena[i];
	
	return suma % hash->tamanio;
}

// Evalua el factor de carga de la tabla de hash y devuelve 1 si es 
// necesario aumentar la cantidad de memoria utilizada por la tabla, -1
// si es posible disminuir la cantidad de memoria utilizada o 0 en caso
// de no requerir redimensionamiento alguno.
// Pre: la tabla de hash fue creada.
int need_redimensionar_hash(hash_t* hash)
{
	if (hash->cantidad >= (2 * hash->tamanio)) return 1;
	else if ((hash->cantidad < hash->tamanio) && (hash->tamanio > TAMANIO_HASH)) return -1;
	return false;
}

// Redimensiona una tabla de hash al doble de su tamaño actual y re
// inserta todas las claves y valores en nuevas posiciones. Si se redi-
// mensiono correctamente devuelve verdadero, y en caso de error, hash
// no se modificó y se devuelve false.
// Pre: la tabla de hash fue creada.
// Post: se redimensiono la tabla de hash.
bool redimensionar_hash(hash_t* hash)
{	
	pila_t* pila_temp = pila_crear();
	if (! pila_temp) return false;
	
	nodo_hash_t* nodo_temp;
	size_t nuevo_tamanio, pos;
	
	// Establecemos el nuevo tamaño de la tabla de hash.
	if(need_redimensionar_hash(hash) == 1) 
		nuevo_tamanio = (int)(hash->tamanio + TAMANIO_HASH);
	else if(need_redimensionar_hash(hash) == -1) 
		nuevo_tamanio = (int)(hash->tamanio - TAMANIO_HASH);
	
	// Almacenamos temporalmente todos los nodos del tipo nodo_hash_t
	// en una pila.	
	for(int i = 0; i < hash->tamanio; i++)
	{
		if(hash->baldes[i])
		{
			while(! lista_esta_vacia(hash->baldes[i]))
			{
				lista_borrar_primero(hash->baldes[i], &nodo_temp);
				pila_apilar(pila_temp, nodo_temp);
			}
			free(hash->baldes[i]);
		}
	}
	
	// Redimensionamos la tabla de hash.
	lista_t** hash_baldes_redim = (lista_t**) calloc(nuevo_tamanio, sizeof(lista_t**));	
	if (! hash_baldes_redim) return false;
	free(hash->baldes);
	hash->baldes = hash_baldes_redim;
	
	hash->tamanio = nuevo_tamanio;
	
	// Reinsertamos nodos del tipo nodo_hash_t en la tabla de hash	
	while(! pila_esta_vacia(pila_temp))
	{
		pila_desapilar(pila_temp, &nodo_temp);
		pos = hashing_f(hash, nodo_temp->clave);
		
		// Si no existe una lista en esa posición la creamos.
		if (! hash->baldes[pos])
			hash->baldes[pos] = lista_crear();
		
		if (! lista_insertar_ultimo(hash->baldes[pos], nodo_temp)) 
			return false;
	}
	
	pila_destruir(pila_temp, NULL);
	
	return true;
}

// Busca un elemento de una lista que contenga almacenado en el miembro
// clave la cadena 'clave'. Si la encuentra, guarda en nodo_hash la
// dirección de memoria de ese nodo y la funcion devuelve verdadero.
// En caso contrario se devuelve false.
// Pre: lista es una lista enlazada existente, clave es una cadena y
// y nodo_hash es un dirección de memoria válida donde se puede 
// escribir.
// Post: de existir la clave, se almacenó la dirección de memoria del
// nodo en nodo_hash.
bool buscar_clave_lista(lista_t* lista, const char* clave, nodo_hash_t** nodo_hash)
{
	lista_iter_t* iter = lista_iter_crear(lista);
	if(! iter) return NULL;
	
	nodo_hash_t* dato;
	
	while (! lista_iter_al_final(iter))
	{
		lista_iter_ver_actual(iter, &dato);
		
		if (! strcmp(dato->clave, clave))
		{
			*nodo_hash = dato;
			lista_iter_destruir(iter);
			
			return true;
		}
		
		lista_iter_avanzar(iter);
	}
	
	lista_iter_destruir(iter);
	
	return false;
}

// Crea un nodo del tipo nodo_hash_t. Devuelve NULL en caso de error.
// Post: el nodo fue creado, se devuelve la posición de memoria de dicho
// nodo.
nodo_hash_t* crear_nodo_hash()
{
	nodo_hash_t* nodo_hash = (nodo_hash_t *) malloc(sizeof(nodo_hash_t));
	if(! nodo_hash) return NULL;
	
	return nodo_hash;
}

// Destruye un nodo del tipo nodo_hash_t. Si destruir_valor es verdadero
// se destruye el valor del nodo, y en caso de ser falso, no se destruye
// dicho valor.
// Pre: el hash y el nodo fueron creados.
// Post: se liberó la memoria utilizada por el nodo.
void destruir_nodo_hash(hash_t* hash, nodo_hash_t* nodo, bool destruir_valor)
{
	free(nodo->clave);
				
	if (destruir_valor && hash->destruir_dato)
		hash->destruir_dato(nodo->valor);
					
	free(nodo);
}

// Almacena una clave en un nodo de tipo nodo_hash_t. De guardarse
// correctamente se devuelve verdadero, y de lo contrario se devuelve
// falso.
// Pre: el nodo fue creado, clave es una cadena.
// Post: se almacenó la clave en el nodo.
bool clave_almacenar(nodo_hash_t *nodo_hash, const char* clave)
{
	nodo_hash->clave = (char*) malloc((strlen(clave) + 1) * sizeof(char));
		
	if(!nodo_hash->clave)
		return false;
			
	strcpy(nodo_hash->clave, clave);
	
	return true;
}



/* ******************************************************************
 *                  PRIMITIVAS DEL HASH ABIERTO
 * *****************************************************************/

// Crea una tabla de hash.
// Pre: recibe la funcion destruir_dato, la cual es utilizada para
// destruir los valores asignados a las claves. De no necesitarse
// debe ser NULL.
// Post: devuelve un puntero a una tabla de hash vacía.
hash_t* hash_crear(hash_destruir_dato_t (*destruir_dato)(hash_dato_t))
{
	hash_t* hash = (hash_t*) malloc(sizeof(hash_t));
    
    if (! hash) return NULL;

    hash->baldes = (lista_t**) calloc(TAMANIO_HASH, sizeof(lista_t**));
       
    if (! hash->baldes)
    {
        free(hash);
        return NULL;
    }
    
    hash->tamanio = TAMANIO_HASH;
    hash->cantidad = 0;
    hash->destruir_dato = destruir_dato;
    
    return hash;
}

// Guarda el dato asignado a la clave en la tabla de hash. Devuelve
// verdadero si se guardó correctamente y falso en caso contrario.
// Si la clave ya existía, se reemplaza el valor por el nuevo dato,
// destruyendose el anterior.
// Pre: la tabla de hash fue creada. 'clave' es una cadena y 'dato' es
// el valor de la clave.
// Post: se guardo la clave con su dato dentro de la tabla.
bool hash_guardar(hash_t *hash, const char* clave, const hash_dato_t dato)
{
	if (need_redimensionar_hash(hash) == 1)
		redimensionar_hash(hash);
	
	nodo_hash_t* nodo_hash;
	size_t pos = hashing_f(hash, clave);
	
	// Si no existe una lista en esa posición la creamos.
	if (! hash->baldes[pos])
		hash->baldes[pos] = lista_crear();
		
	// Si la clave ya existe, reemplazamos el valor.
	if (buscar_clave_lista(hash->baldes[pos], clave, &nodo_hash))
	{
		if (hash->destruir_dato)
			hash->destruir_dato(nodo_hash->valor);
		
		nodo_hash->valor = dato;
	}
	// Si la clave no existe, creamos un nuevo nodo de hash y lo
	// guardamos como un nuevo elemento en la lista.
	else
	{
		nodo_hash = crear_nodo_hash();
		if (! nodo_hash) return false;
		
		if (! clave_almacenar(nodo_hash, clave)) 
		{
			free(nodo_hash);
			return false;
		}
		
		nodo_hash->valor = dato;
		
		if (! lista_insertar_ultimo(hash->baldes[pos], nodo_hash)) 
			return false;
		
		hash->cantidad++;
	}
	
	return true;
}

// Borra una clave de la tabla de hash, depositando en dato el valor de 
// la clave eliminada. Si la clave no existe en la tabla se devuelve 
// falso. Si se borró correctamente la función devuelve verdadero.
// Pre: la tabla de hash fue creada, 'clave' es la clave que se desea
// eliminar y dato es un dirección de memoria válida donde se puede 
// escribir.
bool hash_borrar(hash_t *hash, const char* clave, hash_dato_t *dato)
{
	nodo_hash_t* nodo_hash_temp;
	size_t pos = hashing_f(hash, clave);
	
	if (! hash->baldes[pos]) return false;
		
	// Creamos iterador de la lista.
	lista_iter_t* iter = lista_iter_crear(hash->baldes[pos]);
	if(! iter) return false;
	
	// Iteramos sobre la lista.	
	while (! lista_iter_al_final(iter))
	{
		lista_iter_ver_actual(iter, &nodo_hash_temp);
			
		// La clave coincide con la clave de la posición en la que
		// se encuentra el iterador.
		if (! strcmp(nodo_hash_temp->clave, clave))
		{						
			// Borramos nodo de la lista.
			if(! lista_borrar(hash->baldes[pos], iter, &nodo_hash_temp))
			{
				lista_iter_destruir(iter);
				return false;
			}
						
			// Almacenamos en dato el valor del nodo eliminado.
			*dato = nodo_hash_temp->valor;
			
			// Destruimos el nodo.
			destruir_nodo_hash(hash, nodo_hash_temp, false);
					
			lista_iter_destruir(iter);
			
			// Si no hay mas elementos en la lista, la destruimos.
			if (lista_esta_vacia(hash->baldes[pos]))
			{
				lista_destruir(hash->baldes[pos], NULL);
				hash->baldes[pos] = NULL;
			}
			
			hash->cantidad--;
			
			// Redimensionamos la tabla de hash de ser necesario.
			if (need_redimensionar_hash(hash) == -1)
				redimensionar_hash(hash);
			
			return true;
		}
		
		lista_iter_avanzar(iter);
	}
	
	lista_iter_destruir(iter);
	
	return false;
}

// Busca si la clave esta en la tabla de hash. Si existe, deposita en
// 'dato' el valor correspondiente a la clave y devuelve verdadero. Si
// no existe la clave se devuelve false.
// Pre: la tabla de hash fue creada, 'clave' es la clave que se desea
// buscar y 'dato' es un dirección de memoria válida donde se puede 
// escribir.
// Post: de existir la clave se almacenó en 'dato' el valor que contiene
// dicha clave.
bool hash_obtener(hash_t *hash, const char* clave, hash_dato_t *dato)
{
	nodo_hash_t* nodo_hash_temp;
	size_t pos = hashing_f(hash, clave);
	
	if (! hash->baldes[pos]) return false;
	
	// Creamos iterador de la lista.
	lista_iter_t* iter = lista_iter_crear(hash->baldes[pos]);
	if(! iter) return false;
	
	// Iteramos sobre la lista.		
	while (! lista_iter_al_final(iter))
	{
		lista_iter_ver_actual(iter, &nodo_hash_temp);
		
		// La clave coincide con la clave de la posición en la que
		// se encuentra el iterador.
		if (! strcmp(nodo_hash_temp->clave, clave))
		{			
			// Guardamos en dato el valor asignado a esa clave.
			*dato = nodo_hash_temp->valor;
			lista_iter_destruir(iter);
			
			return true;
		}
		
		lista_iter_avanzar(iter);
	}
	
	lista_iter_destruir(iter);
	
	return false;
}

// Devuelve la cantidad de claves que contiene la tabla de hash.
// Pre: la tabla de hash fue creada.
size_t hash_cantidad(const hash_t *hash)
{	
	return hash->cantidad;
}

// Destruye una tabla de hash.
// Pre: la tabla de hash fue creada.
void hash_destruir(hash_t* hash)
{
	for (int i = 0; i < hash->tamanio; i++)
	{
		if (hash->baldes[i])
		{
			while(! lista_esta_vacia(hash->baldes[i]))
			{
				nodo_hash_t* nodo;
				lista_borrar_primero(hash->baldes[i], &nodo);
				destruir_nodo_hash(hash, nodo, true);
			}
			
			lista_destruir(hash->baldes[i], NULL);
		}
		
	}
	
	free(hash->baldes);
	free(hash);
}




/* ******************************************************************
 *             PRIMITIVAS DEL ITERADOR DEL HASH ABIERTO
 * *****************************************************************/


// Crea un iterador para una tabla de hash.
// Pre: la tabla de hash fue creada.
// Post: devuelve un iterador nuevo.
hash_iter_t* hash_iter_crear(const hash_t *hash)
{
	hash_iter_t* hash_iter = (hash_iter_t *) malloc(sizeof(hash_iter_t));
	if(! hash_iter) return NULL;
	
	lista_iter_t* iter = NULL;
		
	for(int i = 0; i < hash->tamanio; i++)
	{
		if(hash->baldes[i])
		{
			hash_iter->pos = i;
			// Creamos iterador de la lista.
			iter = lista_iter_crear(hash->baldes[i]);
			if(! iter) return false;
			
			break;
		}
	}
			
	hash_iter->hash = (hash_t*) hash;
	hash_iter->lista_iter = iter;
	
	return hash_iter;
}

// Avanza sobre la tabla de hash.
// Pre: El iterador fue creado.
// Post: Si avanzó sobre el hash, devuelve verdadero. En caso contrario
// devuelve falso.
bool hash_iter_avanzar(hash_iter_t *iter)
{
	if (hash_iter_al_final(iter)) return false;
	
	lista_iter_avanzar(iter->lista_iter);
	
	if(! lista_iter_al_final(iter->lista_iter))
		return true;

	lista_iter_destruir(iter->lista_iter);
	iter->lista_iter = NULL;

	for(int i = iter->pos+1; i < iter->hash->tamanio; i++)
	{
		if (iter->hash->baldes[i])
		{
			lista_iter_t* iter_nuevo = lista_iter_crear(iter->hash->baldes[i]);
			if(! iter_nuevo) return false;
			
			
			iter->lista_iter = iter_nuevo;
			iter->pos = i;
			
			return true;
		}
	}
	
	return  false;
}

// Obtiene la clave y el valor asignado a la clave de la posición donde  
// se encuentra el  iterador. Si el hash tiene elementos, el valor 
// correspondiente a esa posición se copia en *dato y se devuelve la 
// clave. En caso contrario se devuelve NULL. El parámetro 'clave' debe 
// ser la misma variable que recibira la cadena.
// Pre: el iterador fue creado, dato y clave son direcciónes de memoria
// válida donde se puede escribir.
// Post: dato contiene el valor y se devuelve la clave de la posición en
// donde se encuentra el iterador.
char* hash_iter_ver_actual(hash_iter_t *iter, char* clave, hash_dato_t *dato)
{	
	if (hash_iter_al_final(iter)) return NULL;
	
	nodo_hash_t* nodo;
	
	if(! lista_iter_ver_actual(iter->lista_iter, &nodo)) return NULL;
	
	clave = malloc((strlen(nodo->clave) + 1) * sizeof(char));
	if(! clave) return NULL;
	
	strcpy(clave, nodo->clave);
	*dato = nodo->valor;
	
	return clave;
}

// Devuelve verdadero o falso, según si el iterador llego al final de 
// la tabla de hash o no.
// Pre: el iterador fue creado.
bool hash_iter_al_final(hash_iter_t *iter)
{	
	return !(iter->lista_iter);
}

// Destruye el iterador.
// Pre: el iterador fue creado.
void hash_iter_destruir(hash_iter_t* iter)
{
	if (iter->lista_iter)
		lista_iter_destruir(iter->lista_iter);
	
	free(iter);
}
