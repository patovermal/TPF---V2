/**
* @file nmea.h
* @author buyi97
* @date 22/11/2019
* @brief Define y structs para NMEA
*/

#ifndef NMEA__H
#define NMEA__H

#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "../geopos/geopos.h"
#include "../status/status.h"
#include "../fecha/fecha.h"
#include "../gpx/gpx.h"
#include "../files/files.h"
#include "../list/list.h"
#include "../split/split.h"
#include "../logs/logs.h"

#define NMEA_TOKEN_CHKSUM '*'

#define NMEA_CHAR_START '$'

#define NMEA_DELIM_CHAR ','
#define NMEA_DELIM_CANT_MAX 30
#define NMEA_DELIM_CANT_MIN 5

#define NMEA_ID_LEN 3

#define NMEA_MAX_LEN 150

#define NMEA_CANT_TIPOS	3

#define NMEA_GGA_STR "GGA"
#define NMEA_RMC_STR "RMC"
#define NMEA_ZDA_STR "ZDA"

#define NMEA_GGA_HORA_POS	1
#define NMEA_GGA_LAT_POS	2
#define NMEA_GGA_LON_POS	4
#define NMEA_GGA_CAL_POS	6
#define NMEA_GGA_SAT_POS	7
#define NMEA_GGA_HDOP_POS	8
#define NMEA_GGA_ELE_POS	9
#define NMEA_GGA_SEP_POS	11

#define MAX_CALIDAD			8
#define MAX_SATELITES 		12

#define NMEA_RMC_HORA_POS	1
#define NMEA_RMC_ST_POS	    2
#define NMEA_RMC_LAT_POS	3
#define NMEA_RMC_LON_POS	5
#define NMEA_RMC_VEL_POS	7
#define NMEA_RMC_ANG_POS	8
#define NMEA_RMC_FECHA_POS	9
#define NMEA_RMC_DESV_POS	10

#define EPOCH_YY_RMC 2000

#define STR_RMC_ACTIVE "A"
#define STR_RMC_VOID "V"

#define NMEA_ZDA_HORA_POS	1
#define NMEA_ZDA_DIA_POS	2
#define NMEA_ZDA_MES_POS	3
#define NMEA_ZDA_ANIO_POS	4
#define NMEA_ZDA_HHUTC_POS	5
#define NMEA_ZDA_MMUTC_POS	6

/**
 * @enum calidad_t
 * @brief Tipo enumerativo para la calidad del fix
 */
/*Tipo de dato para la CALIDAD DEL FIX*/
typedef enum calidad_t{ 
	CAL_INVALIDO, 
	CAL_FIX_GPS, 
	CAL_FIX_DGPS, 
	CAL_FIX_PPS, 
	CAL_RTK, 
	CAL_RTK_FLOAT, 
	CAL_DEAD_RECK, 
	CAL_MANUAL, 
	CAL_SIMULATION 
}calidad_t;

/**
 * @struct gga_t
 * @brief Estructura para la sentencia GGA
 */
/*Estructura para GGA, con los datos a guardar*/
typedef struct gga{
	hora_t hora;
	double latitud;
	double longitud;
	calidad_t calidad;
	unsigned int cant_satelites;
	float hdop;
	float elevacion;
	float sep_geoide;
}gga_t;

/**
 * @struct zda_t
 * @brief Estructura para la sentencia ZDA
 */
/*Estructura para ZDA, con los datos a guardar*/
typedef struct zda{
	fecha_t fecha;
	hora_t hora;
	int hh_utc;
	int mm_utc;
}zda_t;

/**
 * @struct rmc_t
 * @brief Estructura para la sentencia RMC
 */
/*Estructura para RMC, con los datos a guardar*/
typedef struct rmc{
	fecha_t fecha;
	hora_t hora;
	bool status;
	double latitud;
	double longitud;
	double velocidad;
	float ang_seg;
	float desv_mag;
}rmc_t;

/**
 * @enum nmea_id
 * @brief Tipo enumerativo para el ID (tipo de sentencia) de NMEA
 */
/*Tipo para el id de las sentencia NMEA*/
typedef enum nmea_id{
	RMC,
	ZDA,
	GGA,
}nmea_id;

/**
 * @struct nmea_t
 * @brief Estructura para las sentencias NMEA
 */
/*Estructura NMEA, con los datos a guardar (contiene una union de rmc_t, zda_t, y gga_t porque pueden venir cualquiera de los 3)*/
typedef struct nmea{
	nmea_id	id;
	union type {
   		rmc_t rmc;
   		zda_t zda;
   		gga_t gga;
	}type;  
}nmea_t;

/*Prototipos*/
status_t get_nmea_id ( const char *cadena , nmea_id* id );
status_t proc_zda( nmea_t* nmea, char* cadena );
status_t proc_rmc( nmea_t* nmea, char* cadena );
status_t proc_gga( nmea_t* nmea, char* cadena );
status_t proc_nmea( char* cadena , nmea_t* nmea , FILE* flog );
bool verify_checksum ( char* );
status_t rmc2gpx( nmea_t* nmea , gpx_t* gpx);
status_t zda2gpx( nmea_t* nmea , gpx_t* gpx);
status_t gga2gpx( nmea_t* nmea , gpx_t* gpx);
status_t nmea2gpx( Files_t* files , size_t maxlen );

#endif
