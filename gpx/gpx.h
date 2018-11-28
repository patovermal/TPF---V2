#ifndef GPX__H
#define GPX__H

#include "fecha.h"
#include "status.h"

#define MAX_NOMBRE 50

/*Estructura para GPX, con los datos a guardar*/
typedef struct gpx{
	fecha_t fecha;
	hora_t hora;
	double latitud;
	double longitud;
	float elevacion;
}gpx_t;

typedef struct metadata_t{
	char nombre[MAX_NOMBRE+1];
	fecha_t fecha;
	hora_t hora;
}Gpx_mtdt;

/* definicion de los chars a usar */
#define CHAR_START 		"<"
#define CHAR_END 		">"
#define CHAR_QUESTION 	"?"
#define CHAR_COMILLAS 	"\""
#define CHAR_EQUAL 		"="
#define CHAR_BAR 		"/"
#define CHAR_FECHA_SEP	"-"
#define CHAR_HORA_SEP	":"
#define CHAR_FECHA_END	"T"
#define CHAR_HORA_END 	"Z"

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
void print_header(void);
void print_metadata(Gpx_mtdt*);
void print_trk_start(void);
void print_trkpt(gpx_t* );
void print_trk_end(void);
void print_end(void);
/* fin de prototipos */


#endif