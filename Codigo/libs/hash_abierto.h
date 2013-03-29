#ifndef HASH_ABIERTO_H
#define HASH_ABIERTO_H


/* ******************************************************************
 *                	 CONSTANTES REPRESENTATIVAS
 * *****************************************************************/

#define TAMANIO_HASH 1	 		// Tamaño de la Tabla de Hash


/* ******************************************************************
 *                DEFINICION DE LOS TIPOS DE DATOS
 * *****************************************************************/

#ifndef HASH_DATO_T
#define HASH_DATO_T
typedef void* hash_dato_t;
#endif

#ifndef HASH_DESTRUIR_DATO_T
#define HASH_DESTRUIR_DATO_T
typedef void hash_destruir_dato_t;
#endif

typedef struct _hash_t hash_t;
typedef struct _nodo_hash_t nodo_hash_t;
typedef struct _hash_iter_t hash_iter_t;




/* ******************************************************************
 *                  PRIMITIVAS DEL HASH ABIERTO
 * *****************************************************************/

// Crea una tabla de hash. 'destruir_dato' es la función de destrucción
// del valor asignado a una clave. De no ser necesario su uso, debe
// pasarsele NULL.
// Post: devuelve un puntero a una tabla de hash vacía.
hash_t* hash_crear(hash_destruir_dato_t (*destruir_dato)(hash_dato_t));

// Guarda el dato asignado a la clave en la tabla de hash. Devuelve
// verdadero si se guardó correctamente y falso en caso contrario.
// Si la clave ya existía, se reemplaza el valor por el nuevo dato,
// destruyendose el anterior.
// Pre: la tabla de hash fue creada. 'clave' es una cadena y 'dato' es
// el valor de la clave.
// Post: se guardo la clave con su dato dentro de la tabla.
bool hash_guardar(hash_t *hash, const char* clave, const hash_dato_t dato);

// Borra una clave de la tabla de hash, depositando en dato el valor de 
// la clave eliminada. Si la clave no existe en la tabla se devuelve 
// falso. Si se borró correctamente la función devuelve verdadero.
// Pre: la tabla de hash fue creada, 'clave' es la clave que se desea
// eliminar y dato es un dirección de memoria válida donde se puede 
// escribir.
bool hash_borrar(hash_t *hash, const char* clave, hash_dato_t *dato);

// Busca si la clave esta en la tabla de hash. Si existe, deposita en
// 'dato' el valor correspondiente a la clave y devuelve verdadero. Si
// no existe la clave se devuelve false.
// Pre: la tabla de hash fue creada, 'clave' es la clave que se desea
// buscar y 'dato' es un dirección de memoria válida donde se puede 
// escribir.
// Post: de existir la clave se almacenó en 'dato' el valor que contiene
// dicha clave.
bool hash_obtener(hash_t *hash, const char* clave, hash_dato_t *dato);

// Devuelve la cantidad de claves que contiene la tabla de hash.
// Pre: la tabla de hash fue creada.
size_t hash_cantidad(const hash_t *hash);

// Destruye una tabla de hash.
// Pre: la tabla de hash fue creada.
void hash_destruir(hash_t* hash);




/* ******************************************************************
 *             PRIMITIVAS DEL ITERADOR DEL HASH ABIERTO
 * *****************************************************************/


// Crea un iterador para una tabla de hash.
// Pre: la tabla de hash fue creada.
// Post: devuelve un iterador nuevo.
hash_iter_t* hash_iter_crear(const hash_t *hash);

// Avanza sobre la tabla de hash. Devuelve verdadero si avanzó.
// Pre: El iterador fue creado.
// Post: Se avanzó sobre el hash, devuelve verdadero. En caso contrario
// devuelve falso.
bool hash_iter_avanzar(hash_iter_t *iter);

// Obtiene la clave y el valor asignado a la clave de la posición donde  
// se encuentra el  iterador. Si el hash tiene elementos, el valor 
// correspondiente a esa posición se copia en *dato y se devuelve la 
// clave. En caso contrario se devuelve NULL. El parámetro 'clave' debe 
// ser la misma variable que recibira la cadena.
// Pre: el iterador fue creado, dato y clave son direcciónes de memoria
// válida donde se puede escribir.
// Post: dato contiene el valor y se devuelve la clave de la posición en
// donde se encuentra el iterador.
char* hash_iter_ver_actual(hash_iter_t *iter, char* clave, hash_dato_t *dato);

// Devuelve verdadero o falso, según si el iterador llego al final de 
// la tabla de hash o no.
// Pre: el iterador fue creado.
bool hash_iter_al_final(hash_iter_t *iter);

// Destruye el iterador.
// Pre: el iterador fue creado.
void hash_iter_destruir(hash_iter_t* iter);


#endif
