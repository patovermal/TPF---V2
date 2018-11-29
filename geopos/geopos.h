/**
* @file geopos.h
* @author buyi97
* @date 18/11/2019
* @brief Funciones y defines para convertir de cadena a latitud y longitud
*/

#ifndef GEOPOS__H
#define GEOPOS__H

#include <string.h>
#include <stdlib.h>
#include "../status/status.h"

/* Defines para latitud */
#define STR_SUR 	"S"
#define STR_NORTE 	"N"
#define MAX_LONGITUD 180

/* Defines para longitud */
#define STR_OESTE	"W"
#define STR_ESTE	"E"
#define MAX_LATITUD 90

/* Prototipos */
status_t str2lat(char* cadena, char* indicador, double* latitud );
status_t str2lon(char* cadena, char* indicador, double* longitud);

#endif