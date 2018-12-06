/**
* @file fecha.h
* @author buyi97
* @date 18/11/2019
* @brief Funciones para fecha_t y hora_t
*/

#ifndef FECHA__H
#define FECHA__H

#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "../status/status.h"

#define EPOCH_TM_Y 	1900
#define EPOCH_TM_M 	1
#define EPOCH_TM_D 	0

/**
 * @struct fecha_t
 * @brief Estructura para la fecha usando el calendario gregoriano
 */
typedef struct fecha_t{	int year;	/* estructura para la fecha */
			int month;
			int day;
}fecha_t;
/**
 * @struct hora_t
 * @brief Estructura para la hora
 */
typedef struct hora_t{	int hh;		/* estructura para la hora */
			int mm;
			double ss;
}hora_t;

/* Prototipos */
status_t str2hora(char* cadena, hora_t* hora);
status_t str2fecha(char* cadena, fecha_t* hora);
status_t str2fecha_inv(char* cadfecha, fecha_t * fecha);
status_t get_currentdate(fecha_t* fecha, hora_t* hora);

#endif