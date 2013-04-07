/* ****************************************************************************
 * ****************************************************************************
 * LIBRERÍA DE FUNCIONES PARA ROUTERS
 * ****************************************************************************
 * ****************************************************************************
 * 
 * Librería de funciones aplicables a las redes y a los dispositivos
 * y componentes que en ellas se encuentran, tales como routers, 
 * hosts, switches, etc.
 */


#ifndef ROUTER_H
#define ROUTER_H



/* ****************************************************************************
 * FUNCIONES DE LA LIBRERIA
 * ***************************************************************************/


// Función que procesa una red compuesta de hosts y dispositivos, tales
// como routers, con el fin del encontrar el camino minimo para el envío
// de datos desde un host origen hacia los demas hosts existentes en la
// red.
// PRE: 'archivo' es el nombre de archivo (inluyendo su extensión si es
// que posee) en el que se encuentra la especificación de ruteo. 
// El archivo debe estar dividido en secciones, con las siguientes 
// etiquetas: '[host]', '[device]' y '[route]'. En la sección [host] se 
// deben especificar los host que integran la red, con el formato 
// '[NOMBRE],[IP],[NOMBRE_ROUTER]'. El primer host ingresado se considera
// el host origen. En la sección [device] se deben especificar los
// dispositivos que integran la red, con el formato '[NOMBRE_ROUTER],[IP]'.
// El primer dispositivo ingresado se considera el dispositivo origen. 
// Por último, la sección [route] contiene el registro de las conexiones 
// entre los dispositivos, siendo su formato '[D1]->[D2],[PESO]', donde
// D1 es el dispositivo de partida y D2 el dispositivo de llegada para 
// ese tramo del recorrido.
// Si no se especifica ningún archivo de entrada, el sistema solicitará
// que se ingresen los datos a través de la entrada estandar, siendo
// estrictamente necesario ingresarlos correctamente sin errores, con el
// formato que se indicará por pantalla.
// POST: Los resultados se envían a la salida estandar.
void procesar_red_caminos_minimos(char *archivo);

#endif
