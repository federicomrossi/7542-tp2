/* ******************************************************************
 * PROGRAMA CALCULADOR DE ROUTEO ENTRE PC's
 * ******************************************************************
 * 
 * Facultad de Ingeniería - UBA
 * 75.42 Taller de Programación I
 * Trabajo Práctico N°2
 * 
 * ALUMNO: Federico Martín Rossi
 * PADRÓN: 92086
 * EMAIL: federicomrossi@gmail.com
 *
 * ******************************************************************
 *
 * [ REVISARRRRRRR!!!!! ] Programa que se encarga de procesar un 
 * archivo con el listado de interrupciones de servicio eléctrico y 
 * calcula la multa que debe ser aplicada a cada cliente, enviandose 
 * estas a la salida estandar del sistema con el formato 
 * [número_cliente]:[multa].
 *
 * FORMA DE USO
 * ============
 * 
 * El programa se ejecuta del siguiente modo:
 *
 *		# ./tp [archivo]
 *
 * donde,
 *
 *		archivo: nombre de archivo (incluyendo su extensión) donde 
 *				 se registran las interrupciones y el cliente al 
 *				 que pertenece cada una de estas;
 * 
 * NOTA: El archivo de interrupciones debe seguir de manera estricta 
 * el siguiente formato:
 *
 *		[número_de_cliente]:[consumo_típico]:[duración_interrupción]
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
#include "router.h"



/* ******************************************************************
 * PROGRAMA PRINCIPAL
 * *****************************************************************/

int main(int argc, char **argv) {
	
	// Toma de parámetros
	char *archivo = NULL;
	if(argv[1]) archivo = argv[1];
	
	// Enviamos a procesamiento
	procesar_red_caminos_minimos(archivo);

	return 0;
}
