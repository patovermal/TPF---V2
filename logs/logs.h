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
#define MSJ_ERR_PREFIJO "ERR"
#define MSJ_WARN_PREFIJO "WARN"
#define MSJ_DEBUG_PREFIJO "DEBUG"

/* error */
#define MSJ_ERR_OPEN_FILE "No se pudo abrir el archivo"
#define MSJ_ERR_INV_CHKSUM "El checksum no concuerda"
#define MSJ_ERR_INV_LONG_UBX "El mensaje UBX tiene un largo inválido"
#define MSJ_ERR_INV_NMEA "El mensaje NMEA está mal formado"
#define MSJ_ERR_PTR_NULL "Se recibió un puntero nulo"

/* warning */
#define MSJ_WARN_ID_DESC "No se reconoce el ID"
#define MSJ_WARN_FIX_INV "Fix inválido"
#define MSJ_WARN_FULL_LIST "La lista está llena."

/* debug */
#define MSJ_DB_BYTES_SYNC "Buscando bytes de sincronismo"
#define MSJ_DB_ID_DETECT "ID identificado: " //para poner despues que ID
#define MSJ_DB_MSJ_DET "Se recolectó un mensaje"
#define MSJ_DB_MSJ_UP "Se cargó un mensaje en la lista"
#define MSJ_DB_MSJ_PRINT "Se imprimió un mensaje de la lista"

/* defino el tipo log_t */
typedef enum log_t {
    ERR_OPEN_FILE, ERR_INV_CHKSUM, ERR_INV_LONG_UBX,
    ERR_INV_NMEA, ERR_PTR_NULL, WARN_ID_DESC, WARN_FIX_INV, WARN_FULL_LIST,
    DB_BYTES_SYNC, DB_ID_DETECT, DB_MSJ_DET, DB_MSJ_UP, DB_MSJ_PRINT
} log_t;

/* prototipos  */
status_t print_logs (log_t logs, FILE *flogs);

#endif
