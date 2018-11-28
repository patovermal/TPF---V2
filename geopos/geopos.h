#ifndef GEOPOS__H
#define GEOPOS__H

#include "status.h"

/* Defines para latitud */
#define STR_SUR 	"S"
#define STR_NORTE 	"N"
#define MAX_LONGITUD 180

/* Defines para longitud */
#define STR_OESTE	"W"
#define STR_ESTE	"E"
#define MAX_LATITUD 90


status_t str2lat(char* cadena, char* indicador, double* latitud );
status_t str2lon(char* cadena, char* indicador, double* longitud);

#endif