/**
* @file files.h
* @author buyi97
* @date 25/11/2019
* @brief Estructura para los archivos de entrada, salida y logs
*/

#ifndef FILES__H
#define FILES__H

#include <stdio.h>

/* Estructuras */

/**
 * @struct Files_t
 * @brief Estructura que contiene los 3 punteros a archivos
 */
typedef struct Files{
	FILE * fin, * fout, * flog;
}Files_t;

#endif