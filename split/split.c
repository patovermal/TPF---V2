/**
* @file split.c
* @author buyi97
* @date 22/11/2019
* @brief Funciones para cortar cadenas
*/

#include "split.h"

/**
* @brief Corta una cadena en un arreglo de cadenas segun el delimitador que le pases
* @param cadena: cadena a cortar
* @param ptr2ptrarray: puntero al arreglo de cadenas
* @param delim: char delimitador
* @return size_t : cantidad de cadenas en el arreglo de cadenas
*/

size_t split_delim (char * cadena, char ** ptr2ptrarray, char delim) {
	
	size_t i=0;	/* variable de iteracion */

	if ( !cadena || !ptr2ptrarray )	/* valido los punteros */
		return 0;
	
	ptr2ptrarray[0] = cadena;
	
	if ( !( ptr2ptrarray[1] = strchr(cadena,delim) ) )	/* busco el primer delim */
		return 0;
	
	*(ptr2ptrarray[1])='\0';	/* le asigno un \0 */
	ptr2ptrarray[1]++;			/* le hago apuntar a un lugar despues del \0 */
	
	for (i = 2; ( ptr2ptrarray[i] = strchr(ptr2ptrarray[i-1],delim) ) ; i++) {
		
		ptr2ptrarray[i][0] = '\0';
		ptr2ptrarray[i]++;
		
	}

	return i;
	
}