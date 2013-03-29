#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

typedef struct _nuevo_int {
	int entero;
} nuevo_int;

#define GRAFO_DATO_T
typedef nuevo_int* grafo_dato_t;
#include "grafo.h"




int main(void)
{
	grafo_t *grafo = grafo_crear();

	nuevo_int *numero1 = (nuevo_int*) malloc(sizeof(nuevo_int));
	numero1->entero = 4;

	nuevo_int *numero2 = (nuevo_int*) malloc(sizeof(nuevo_int));
	numero2->entero = 5;

	nuevo_int *numero3 = (nuevo_int*) malloc(sizeof(nuevo_int));
	numero3->entero = 5;

	nuevo_int *numero4 = (nuevo_int*) malloc(sizeof(nuevo_int));
	numero4->entero = 7;

	grafo_nuevo_vertice(grafo, numero1);
	printf("Vertices: %d\n", grafo_cantidad_vertices(grafo));
	grafo_nuevo_vertice(grafo, numero1);
	printf("Vertices: %d\n", grafo_cantidad_vertices(grafo));
	grafo_nuevo_vertice(grafo, numero2);
	printf("Vertices: %d\n", grafo_cantidad_vertices(grafo));
	grafo_nuevo_vertice(grafo, numero3);
	printf("Vertices: %d\n", grafo_cantidad_vertices(grafo));
	grafo_nuevo_vertice(grafo, numero2);
	printf("Vertices: %d\n", grafo_cantidad_vertices(grafo));
	grafo_nuevo_vertice(grafo, numero4);
	printf("Vertices: %d\n", grafo_cantidad_vertices(grafo));

	grafo_dato_t lv[grafo_cantidad_vertices(grafo)];

	grafo_obtener_vertices(grafo, lv);

	printf("Len LV: %d\n\n", sizeof(lv)/sizeof(grafo_dato_t));
	
	int i;
	
	for(i=0; i < grafo_cantidad_vertices(grafo); i++ )
	{
		printf("Dato %d: %d\n", i+1, lv[i]->entero);
		if(lv[i]==numero1) printf("coincidio con numero1\n");
	}


	// grafo_crear_arista(grafo, numero1, numero2, 5);
	// grafo_crear_arista(grafo, numero1, numero3, 8);
	// grafo_crear_arista(grafo, numero2, numero1, 7);
	// printf("\nArista: %d\n", grafo_obtener_peso_arista(grafo, numero1, numero2));
	
	// grafo_eliminar_arista(grafo, numero1, numero2);
	// grafo_eliminar_arista(grafo, numero1, numero3);
	// grafo_eliminar_arista(grafo, numero2, numero1);

	
	// grafo_eliminar_vertice(grafo, numero1);
	// printf("Vertices: %d\n", grafo_cantidad_vertices(grafo));
	// grafo_eliminar_vertice(grafo, numero2);
	// printf("Vertices: %d\n", grafo_cantidad_vertices(grafo));
	// grafo_eliminar_vertice(grafo, numero3);
	// printf("Vertices: %d\n", grafo_cantidad_vertices(grafo));
	// grafo_eliminar_vertice(grafo, numero4);
	// printf("Vertices: %d\n", grafo_cantidad_vertices(grafo));


	// printf("\nArista: %d\n", grafo_obtener_peso_arista(grafo, numero1, numero2));
	// printf("\nArista: %d\n", grafo_obtener_peso_arista(grafo, numero1, numero3));
	// printf("\nArista: %d\n", grafo_obtener_peso_arista(grafo, numero2, numero1));


	// if (grafo_son_adyacentes(grafo, numero2, numero1))
	// 	printf("Son adyacentes\n");
	// else
	// 	printf("No son adyacentes\n");

	grafo_destruir(grafo);

	free(numero1);
	free(numero2);
	free(numero3);
	free(numero4);


	return 0;
}