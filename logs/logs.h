/**
* @file logs.h
* @author pulpo
* @date 24/11/2018
* @brief La funcion recibe el log y un puntero a file e imprime
* el mensaje correspondiente en el archivo indicado.
*/

#ifndef LOGS__H
#define LOGS__H

#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdio.h>
#include "../status/status.h"

/* prefijos */
#define MSJ_ERR_PREFIJO "[ERR]"
#define MSJ_WARN_PREFIJO "[WARN]"
#define MSJ_DEBUG_PREFIJO "[DEBUG]"

/* error */
#define MSJ_ERR_OPEN_FILE 		"No se pudo abrir el archivo (puede que no exista)"
#define MSJ_ERR_INV_CHKSUM 		"El checksum no concuerda"
#define MSJ_ERR_INV_LONG_UBX 	"El mensaje UBX tiene un largo invalido"
#define MSJ_ERR_INV_UBX			"Mensaje UBX mal formado"
#define MSJ_ERR_INV_NMEA 		"Mensaje NMEA mal formado"
#define MSJ_ERR_GET_DATE 		"Error al obtener la fecha del sistema"
#define MSJ_ERR_NO_MEM 			"No hay memoria disponible"
#define MSJ_ERR_LIST_MAKE 		"Error al crear la lista"
#define MSJ_ERR_LIST_APPEND 	"Error al agregar elementos a la lista"
#define MSJ_ERR_NO_PROTOCOL 	"No se indica protocolo"
#define MSJ_ERR_PROC_FILE 		"Error al procesar el archivo"
#define MSJ_ERR_PROC_ARGS 		"Error al procesar los argumentos en linea de comandos"

/* warning */
#define MSJ_WARN_ID_DESC 		"No se reconoce el ID"
#define MSJ_WARN_FIX_INV 		"Fix invalido"
#define MSJ_WARN_FULL_LIST 		"La lista esta llena"
#define MSJ_WARN_GPX_CONV 		"Problema al convertir a GPX (se descarta)"
#define MSJ_WARN_ARG_MISS 		"Faltan argumentos"

/* debug */
#define MSJ_DB_BYTES_SYNC_SEARCH 		"Buscando bytes de sincronismo"
#define MSJ_DB_ID_DETECT 		"ID identificado"
#define MSJ_DB_MSJ_DET 			"Se recolecta un mensaje"
#define MSJ_DB_MSJ_UP 			"Se carga un mensaje en la lista"
#define MSJ_DB_MSJ_PRINT 		"Se imprime un mensaje"
#define MSJ_DB_DATE_ACT 		"Fecha de los tracks actualizada"
#define MSJ_DB_VALID_CHKSUM 	"El checksum concuerda"
#define MSJ_DB_BYTES_SYNC_OK	"Bytes de sincronismo encontrados"
#define MSJ_DB_EOF				"EOF (final de archivo) alcanzado"

/* defino el tipo log_t */
/**
 * @enum log_t
 * @brief Tipo de dato para logs
 */
typedef enum log_t {
    ERR_OPEN_FILE,
	ERR_INV_CHKSUM,
	ERR_INV_LONG_UBX,
    ERR_INV_NMEA,
	ERR_INV_UBX,
	ERR_GET_DATE,
	ERR_NO_MEM,
	ERR_LIST_MAKE,
	ERR_LIST_APPEND,
	ERR_NO_PROTOCOL,
	ERR_PROC_FILE,
	ERR_PROC_ARGS,
	WARN_ID_DESC,
	WARN_FIX_INV,
	WARN_FULL_LIST,
	WARN_GPX_CONV,
	WARN_ARG_MISS,
    DB_BYTES_SYNC_SEARCH,
	DB_ID_DETECT,
	DB_MSJ_DET,
	DB_MSJ_UP,
	DB_MSJ_PRINT,
	DB_DATE_ACT,
	DB_VALID_CHKSUM,
	DB_BYTES_SYNC_OK,
	DB_EOF
} log_t;

/* prototipos  */
status_t init_logger(char * filename);
void close_logger(void);
status_t print_logs (log_t logs);

#endif
