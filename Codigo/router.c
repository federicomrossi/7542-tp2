/* ******************************************************************
 * ******************************************************************
 * LIBRERÍA DE FUNCIONES PARA ROUTERS
 * ******************************************************************
 * ******************************************************************
 * 
 * Librería de funciones aplicables a las redes y a los componentes
 * que en ellas se encuentran, tales como routers, hosts, etc.
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>




/* ******************************************************************
 * CONSTANTES
 * *****************************************************************/

// Etiquetas de secciones
const char S_HOST[] = "[host]";
const char S_DEVICE[] = "[device]";
const char S_ROUTE[] = "[route]";
enum seccion {NONE, HOST, DEVICE, ROUTE};

// Máximo de caracteres permitidos por cadena
#define MAX_CHARS 20
// Máximo de caracteres del buffer
#define MAX_BUFFER 100



 /* ******************************************************************
 * DECLARACIÓN DE LOS TIPOS DE DATOS
 * *****************************************************************/

typedef struct _host_t host_t;
typedef struct _device_t device_t;
typedef struct _route_t route_t;




/* ******************************************************************
 * INCLUSIÓN DE LIBRERIAS Y TADS EXTERNOS
 * *****************************************************************/

// TAD Lista
#define LISTA_DATO_T
typedef void* lista_dato_t;

// TAD Grafo
#define GRAFO_DATO_T
typedef device_t* grafo_dato_t;

#include "lista.h"
#include "grafo.h"
#include "dijkstra.h"



/* ******************************************************************
 * DEFINICIÓN DE LOS TIPOS DE DATOS
 * *****************************************************************/

// Tipo que representa a un host de una red.
struct _host_t
{
	char nombre[MAX_CHARS];				// Nombre del host
	char ip[MAX_CHARS];					// IP del host
	char dispositivo_nombre[MAX_CHARS];	// Nombre del dispositivo al 
										// cual está conectado el host
};

// Tipo que representa a un dispositivo de una red.
struct _device_t
{
	char nombre[MAX_CHARS];				// Nombre del dispositivo
	char ip[MAX_CHARS];					// IP del dispositivo
};

// Tipo que representa una ruta o conexión entre dispositivos
struct _route_t
{
	char ini[MAX_CHARS];				// Nombre del device de partida
	char fin[MAX_CHARS];				// Nombre del device destino
	int peso;							// Peso asociado a la conexión
};



/* ******************************************************************
 * FUNCIONES AUXILIARES
 * *****************************************************************/

// Crea un host.
// POST: devuelve un host o NULL si no ha sido posible llevar a cabo
// la creación del mismo.
host_t* host_crear()
{
	host_t *host = (host_t*) malloc(sizeof(host_t));
	if(!host) exit(0);
	return host;
}

// Destruye un host.
// PRE: 'host' es un host existente.
// POST: se eliminó el host.
void host_destruir(host_t *host)
{
	free(host);
}

// Crea un dispositivo.
// POST: devuelve un dispositivo o NULL si no ha sido posible llevar a cabo
// la creación del mismo.
device_t* device_crear()
{
	device_t *device = (device_t*) malloc(sizeof(device_t));
	if(!device) exit(0);
	return device;
}

// Destruye un dispositivo.
// PRE: 'dispositivo' es un dispositivo existente.
// POST: se eliminó el dispositivo.
void device_destruir(device_t *device)
{
	free(device);
}

// Crea una ruta o conexión.
// POST: devuelve una ruta o NULL si no ha sido posible llevar a cabo
// la creación del mismo.
route_t* route_crear()
{
	route_t *route = (route_t*) malloc(sizeof(route_t));
	if(!route) exit(0);
	return route;
}

// Destruye una ruta o conexión.
// PRE: 'device' es una ruta existente.
// POST: se eliminó la ruta.
void route_destruir(route_t *route)
{
	free(route);
}

// Función que realiza la apertura de un archivo.
// PRE: 'archivo' es el nombre (y extensión) del archivo a abrir.
// POST: se devuelve el puntero al archivo.
FILE* archivo_abrir(char *archivo) {
	FILE *fp;

	// Apertura del archivo para lectura
	fp = fopen(archivo, "r");

	// Verificación de errores producidos
	if (fp == NULL) {
		printf("ERROR: No ha sido posible abrir el archivo %s.\n", archivo);
		// Se retorna 0 en todos los casos, a pesar de existir error.
		exit(0);
	}

	return fp;
}

// Cierra el stream de un archivo.
// PRE: 'fp' es un puntero al archivo
void archivo_cerrar(FILE* fp) {
	fclose(fp);
}

// Función que verifica si una cadena es prefijo de otra
// PRE: 'd' y 'q' son cadenas.
// POST: devuelve true si 'q' es prefijo de 'd' o false en caso contrario.
bool esPrefijo(const char *d, const char *q)
{
	int i;
	for(i = 0; q[i] && d[i]; i++)
		if(q[i] != d[i]) return false;

	return true;
}

// Función que realiza la comparación alfanumérica de dos cadenas.
// PRE: 'd' y 'q' son cadenas.
// POST: devuelve < 0 si d<q, 0 si d==q, ó > 0 si d>q.
// int comparacion_alfanumerica_cadenas(const char *d, const char *q)
// {
// 	int i, comp;
// 	for(i = 0; d[i] && q[i]; i++)
// 	{
// 		comp = strcmp(d[i], q[i]);
// 		if(comp < 0) return -1;
// 		else if (comp > 0) return 1;
// 	}

// 	return 0;
// }

// Función que dada una línea de la sección [host] del archivo de 
// especificación de ruteo, se encarga de parsear la información que en ella 
// está contenida.
// PRE: 'buffer' es un string con el formato '[nombre],[IP],[nombre_router]'.
// POST: devuelve un puntero a un host que contiene la información parseada.
host_t* parser_host(char *buffer) {
	
	// Creamos un host nuevo
	host_t *host = host_crear();

	// Parseamos el nombre del host
	char* segmento_1 = strstr(buffer, ",");
	int n = strlen(buffer) - strlen(segmento_1);
	strncpy(host->nombre, buffer, n);
	host->nombre[n] = '\0';

	// Parseamos la IP del host
	char* segmento_2 = strstr(++segmento_1, ",");
	n = strlen(segmento_1) - strlen(segmento_2);
	strncpy(host->ip, segmento_1, n);
	host->ip[n] = '\0';

	// Parseamos el nombre del dispositivo al cual esta conectado
	++segmento_2;
	strncpy(host->dispositivo_nombre, segmento_2, strlen(segmento_2) - 1);
	host->dispositivo_nombre[strlen(segmento_2) - 1] = '\0';

	return host;
}

// Función que dada una línea de la sección [device] del archivo de 
// especificación de ruteo, se encarga de parsear la información que en ella 
// está contenida.
// PRE: 'buffer' es un string con el formato '[nombre_router],[IP]'.
// POST: devuelve un puntero a un device que contiene la información parseada.
device_t* parser_device(char *buffer)
{
	// Creamos un device nuevo
	device_t *device = device_crear();

	// Parseamos el nombre del dispositivo
	char* segmento_1 = strstr(buffer, ",");
	int n = strlen(buffer) - strlen(segmento_1);
	strncpy(device->nombre, buffer, n);
	device->nombre[n] = '\0';

	// Parseamos la IP del dispositivo
	++segmento_1;
	n = strlen(segmento_1) - 1;
	strncpy(device->ip, segmento_1, n);
	device->ip[n] = '\0';

	return device;
}

// Función que dada una línea de la sección [route] del archivo de 
// especificación de ruteo, se encarga de parsear la información que en ella 
// está contenida.
// PRE: 'buffer' es un string con el formato '[router_ini]->[router_fin],peso'.
// POST: devuelve un puntero a un route que contiene la información parseada.
route_t* parser_route(char *buffer)
{
	// Creamos una conexión nueva
	route_t *route = route_crear();

	// Parseamos el dispositivo de partida
	char* segmento_1 = strstr(buffer, "->");
	int n = strlen(buffer) - strlen(segmento_1);
	strncpy(route->ini, buffer, n);
	route->ini[n] = '\0';

	// Parseamos el dispositivo destino
	++segmento_1;
	char* segmento_2 = strstr(++segmento_1, ",");
	n = strlen(segmento_1) - strlen(segmento_2);
	strncpy(route->fin, segmento_1, n);
	route->fin[n] = '\0';

	// Parseamos el peso de la conexión
	char s_peso[MAX_CHARS] = "";
	++segmento_2;
	strncpy(s_peso, segmento_2, strlen(segmento_2) - 1);
	route->peso = atoi(s_peso);

	return route;
}

// Función que busca dispositivo en una lista de dispositivos.
// PRE: 'devices' es una lista que contiene dispositivos; 'nombre'
// es el nombre del dispositivo que se desea buscar.
// POST: si se lo encuentra, se devuelve un puntero al dispositivo.
// En caso contrario, se devuelve NULL;
device_t* buscar_device(lista_t *devices, char *nombre)
{
	// Iteramos sobre la lista de dispositivos hasta encontrar
	// el que buscamos
	lista_iter_t* iter = lista_iter_crear(devices);
	lista_dato_t device;

	while(!lista_iter_al_final(iter))
	{
		lista_iter_ver_actual(iter, &device);
		
		if(!strcmp(((device_t*) device)->nombre, nombre))
		{
			lista_iter_destruir(iter);
			return (device_t*) device;
		}

		lista_iter_avanzar(iter);
	}
	
	lista_iter_destruir(iter);

	return NULL;
}

// Función que procesa el archivo de especificación de ruteo.
// PRE: 'archivo' es el nombre de archivo (incluyendo su extensión) donde
// se encuentran especificadas las reglas de routeo, los dispositivos y
// hosts existentes en la red; 'devices' es una lista de dispositivos 
// (device_t); 'hosts' es una lista de hosts (host_t). 
// POST: se devuelve un grafo cuyos vértices son los dispositivos procesados
// (de tipo 'device_t') y cuyas aristas son las rutas o conexiones procesadas. 
// Se almacenan además los dispositivos y hosts procesados en las listas
// 'devices' y 'hosts' respectivamete.
// NOTA: Al ser extraídos de las listas deben ser casteados a sus respectivos
// tipos para poder ser utilizados debidamente.
grafo_t* armar_red_archivo_de_entrada(char* archivo, lista_t *devices, 
	lista_t *hosts)
{
	// Variables para el tratamiento del archivo
	FILE *fp;
	char buffer[MAX_BUFFER];
	int seccion = NONE;
	host_t* host;
	device_t* device;
	route_t* route;

	
	// Apertura del archivo para lectura
	fp = archivo_abrir(archivo);

	// Creamos el grafo de la red
	grafo_t* grafo_red = grafo_crear();

	// Procesamos linea por linea del archivo
	while(fgets(buffer, MAX_BUFFER, fp)) 
	{
		// Verificamos si ha cambiado la sección
		if(esPrefijo(buffer, S_HOST))
		{
			seccion = HOST;
			printf("HOST\n");
			continue;
		}
		else if(esPrefijo(buffer, S_DEVICE))
		{
			seccion = DEVICE;
			printf("\nDEVICE\n");
			continue;
		}
		else if(esPrefijo(buffer, S_ROUTE))
		{
			seccion = ROUTE;
			printf("\nROUTE\n");
			continue;
		}

		printf("linea: %s", buffer);

		// Si no ha cambiado la sección, procesamos de acuerdo
		// a la sección en la que nos encontremos
		switch(seccion)
		{
			// Procesamos host
			case HOST:		host = parser_host(buffer);
							// Agregamos el host a la lista de hosts
							lista_insertar_ultimo(hosts, (lista_dato_t) host);
							break;

			// Procesamos device
			case DEVICE:	device = parser_device(buffer);
							// Agregamos el device como vértice del grafo
							grafo_nuevo_vertice(grafo_red, device);
							// Agregamos el device a la lista de devices
							lista_insertar_ultimo(devices, 
								(lista_dato_t) device);
							break;

			// Procesamos route
			case ROUTE:		route = parser_route(buffer);
							// Creamos la arista de la conexión en el grafo
							grafo_crear_arista(grafo_red, 
								buscar_device(devices, route->ini), 
								buscar_device(devices, route->fin),
								route->peso);
							route_destruir(route);
							break;
		}
	}

	// Cerramos el archivo
	archivo_cerrar(fp);

	return grafo_red;
}

// 
grafo_t* armar_red_entrada_estandar(lista_t *devices, lista_t *hosts)
{
	return NULL;
}

// 
void enviar_caminos_minimos_salida_estandar()
{
	return;
}



// Función que establece el criterio de selección de caminos para
// el caso de poseer dos caminos de igual longitud.
// PRE: 'c1' y 'c2' son parámetros que deben haber sido creados como
// tipo 'device_t' (se los pasa como void por ser tratado por listas)
int criterio_de_seleccion_de_camino(lista_dato_t c1, lista_dato_t c2)
{
	printf("c1: %s - ", ((device_t*) c1)->nombre);
	printf("c2: %s\n", ((device_t*) c2)->nombre);	
	return strcmp(((device_t*) c1)->nombre, ((device_t*) c2)->nombre);
}



/* ******************************************************************
 * FUNCIONES DE LA LIBRERIA
 * *****************************************************************/

// 
void procesar_red_caminos_minimos(char *archivo)
{
	grafo_t *grafo_devices = NULL;
	lista_t *devices = lista_crear();
	lista_t *hosts = lista_crear();
	lista_dato_t device_origen;

	// Armamos el grafo de routers
	if(archivo)
		// Procesamos hosts y devices desde archivo de entrada.
		grafo_devices = armar_red_archivo_de_entrada(archivo, devices, hosts);
	else
		// Procesamos hosts y devices desde entrada estandar
		//grafo_routers = armar_red_entrada_estandar(devices, hosts);
		printf("Procesamos hosts y devices desde entrada estandar");

	// Buscamos caminos mínimos por Dijkstra
	lista_ver_primero(devices, &device_origen);
	lista_t* resultados = dijkstra_caminos_minimos(grafo_devices,
		device_origen, criterio_de_seleccion_de_camino);

	lista_t *camino = dijkstra_obtener_camino(resultados, 
		(lista_dato_t) buscar_device(devices, "5"));



	//printf("largo: %d\n", lista_largo(camino));

	// lista_dato_t aux;
	// lista_ver_primero(camino, &aux);
	// printf("nombre: %s\n", ((device_t*)aux)->nombre);

	lista_iter_t* iter = lista_iter_crear(camino);
	lista_dato_t aux;

	while(!lista_iter_al_final(iter))
	{
		lista_iter_ver_actual(iter, &aux);
		printf("nombre: %s\n", ((device_t*)aux)->nombre);
		lista_iter_avanzar(iter);
	}
	
	lista_iter_destruir(iter);

	dijkstra_destruir_resultados(resultados);

	

	/////printf("dispositivo: %s\n", ((device_t*)a)->nombre);

	// Enviamos resultado a salida estandar

	// Liberamos memoria utilizada
	lista_destruir(devices, free);
	lista_destruir(hosts, free);
	grafo_destruir(grafo_devices);
}