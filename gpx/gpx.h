/**
* @file gpx.h
* @author buyi97
* @date 22/11/2019
* @brief Funciones, tipos y defines para el formato gpx
*/

#ifndef GPX__H
#define GPX__H

#include <stdio.h>
#include "../fecha/fecha.h"
#include "../status/status.h"

#define MAX_NOMBRE 50

#define DEFAULT_NOMBRE "archivo"

/* Estructuras */
/**
 * @struct gpx_t
 * @brief Estructura para GPX, con los datos a guardar
 */
typedef struct gpx{
	fecha_t fecha;
	hora_t hora;
	double latitud;
	double longitud;
	float elevacion;
}gpx_t;

/**
 * @struct Gpx_mtdt
 * @brief Estructura para la metadata GPX, con los datos a guardar
 */
typedef struct metadata_t{
	char nombre[MAX_NOMBRE+1];
	fecha_t fecha;
	hora_t hora;
}Gpx_mtdt;

/* definicion de los chars a usar */
#define CHAR_START 		'<'
#define CHAR_END 		'>'
#define CHAR_COMILLAS 	'\"'
#define CHAR_EQUAL 		'='
#define CHAR_BAR 		'/'
#define CHAR_FECHA_SEP	'-'
#define CHAR_HORA_SEP	':'
#define CHAR_FECHA_END	'T'
#define CHAR_HORA_END 	'Z'
#define CHAR_QUESTION 	'?'

/* definicion de las cadenas a usar */
#define MSJ_XML 			"xml"
#define MSJ_VERSION 		"version"
#define MSJ_ENCODING		"encoding"
#define MSJ_GPX 			"gpx"
#define MSJ_VERSION 		"version"
#define MSJ_CREATOR 		"creator"
#define MSJ_XMLNS 			"xmlns"
#define MSJ_METADATA 		"metadata"
#define MSJ_NAME 			"name"
#define MSJ_TIME			"time"
#define MSJ_TRK 			"trk"
#define MSJ_TRKSEG 			"trkseg"
#define MSJ_TRKPT 			"trkpt"
#define MSJ_LAT 			"lat"
#define MSJ_LON 			"lon"
#define MSJ_ELE 			"ele"

/* definicion de las constantes */
#define VERSION_XML	"1.0"
#define VERSION_GPX	"1.1"
#define ENCODING 	"UTF -8"
#define CREATOR 	"95.11 TPF - Grupo 7"
#define XMLNS		"http://www.topografix.com/GPX/1/1"

/* prototipos de todas las funciones contenidas */
void print_headerGPX(FILE * fout);
void print_metadataGPX(Gpx_mtdt * fix, FILE * fout);
void print_trk_startGPX(FILE * fout);
void print_trkptGPX(gpx_t* fix, FILE * fout);
void print_trk_endGPX(FILE * fout);
void print_endGPX(FILE * fout);
/* fin de prototipos */


#endif