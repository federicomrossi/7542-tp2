
#define LISTA_DATO_T
typedef int lista_dato_t;

#define GRAFO_DATO_T
typedef int* grafo_dato_t;


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "lista.h"
#include "grafo.h"



/* ******************************************************************
 *                      FUNCIONES AUXILIARES
 * *****************************************************************/

/* Función auxiliar para imprimir si estuvo OK o no. */
void print_test(char* name, bool result)
{
    printf("%s: %s\n", name, result? "OK" : "ERROR");
}

/* Función auxiliar para imprimir un espacio entre lineas */
void print_spaceline()
{
	printf("\n");
}



/* ******************************************************************
 *                        PRUEBAS UNITARIAS
 * *****************************************************************/


/* Prueba que las primitivas de la lista funcionen correctamente. */
void prueba_grafo()
{
	grafo_t *grafo = grafo_crear();

	int v1 = 1;
	int v2 = 2;


	print_test("Prueba", grafo != NULL);
	print_test("Prueba", grafo_cantidad_vertices(grafo) == 0);
	print_test("Prueba", !grafo_es_vertice(grafo, &v1));
	print_test("Prueba", grafo_nuevo_vertice(grafo, &v1));
	print_test("Prueba", grafo_cantidad_vertices(grafo) == 1);
	print_test("Prueba", grafo_es_vertice(grafo, &v1));
	print_test("Prueba", grafo_eliminar_vertice(grafo, &v1));
	print_test("Prueba", grafo_cantidad_vertices(grafo) == 0);
	print_test("Prueba", !grafo_es_vertice(grafo, &v1));
	print_test("Prueba", !grafo_crear_arista(grafo, &v1, &v2, 7));
	print_test("Prueba", grafo_nuevo_vertice(grafo, &v1));
	print_test("Prueba", !grafo_crear_arista(grafo, &v1, &v2, 7));
	print_test("Prueba", grafo_nuevo_vertice(grafo, &v2));
	print_test("Prueba", grafo_obtener_peso_arista(grafo, &v1, &v2) == 0);
	print_test("Prueba", grafo_crear_arista(grafo, &v1, &v2, 7));
	print_test("Prueba", grafo_obtener_peso_arista(grafo, &v1, &v2) == 7);
	
	
	grafo_destruir(grafo);
}



/* ******************************************************************
 *                        PROGRAMA PRINCIPAL
 * *****************************************************************/

/* Programa principal. */
int main(void)
{
    /* Ejecuta todas las pruebas unitarias. */
    prueba_grafo();

    return 0;
}