/**
* @file logs.c
* @author pulpo
* @date 24/11/2018
* @brief La funcion recibe el log y un puntero a file e imprime
* el mensaje correspondiente en el archivo indicado.
*/

#include "logs.h"

/**
* @brief Imprimir logs
* @param logs : log_t tipo de log a loguear
* @param flogs : puntero a archivo de logs
* @return status_t : el estado en el que termina la función (si fue todo bien ST_OK)
*/

status_t print_logs (log_t logs, FILE *flogs) {
    
    time_t now;     
    time(&now);     
    char * date =ctime(&now);
    
    if (!flogs)
        return ST_ERR_PUNT_NULL;
    
	date[strlen(date) - 1] = '\0'; /* le saco el \n que tiene para que imprima todo en una linea*/
	fprintf(flogs, "%s - " , date);
	
    switch(logs) {

        /* Errores (ERR) */
        case ERR_OPEN_FILE:
            fprintf(flogs, "%s: %s\n", MSJ_ERR_PREFIJO, MSJ_ERR_OPEN_FILE);
			break;
			
        case ERR_INV_CHKSUM:
            fprintf(flogs, "%s: %s\n", MSJ_ERR_PREFIJO, MSJ_ERR_INV_CHKSUM);
            break;

        case ERR_INV_LONG_UBX:
            fprintf(flogs, "%s: %s\n", MSJ_ERR_PREFIJO, MSJ_ERR_INV_LONG_UBX);
            break;

        case ERR_INV_NMEA:
            fprintf(flogs, "%s: %s\n", MSJ_ERR_PREFIJO, MSJ_ERR_INV_NMEA);
            break;
		
		case ERR_GET_DATE:
			fprintf(flogs, "%s: %s\n", MSJ_ERR_PREFIJO, MSJ_ERR_GET_FECHA);
            break;
			
		case ERR_NO_MEM:
			fprintf(flogs, "%s: %s\n", MSJ_ERR_PREFIJO, MSJ_ERR_NO_MEM);
            break;
		
		case ERR_LIST_MAKE:
			fprintf(flogs, "%s: %s\n", MSJ_ERR_PREFIJO, MSJ_ERR_LIST_MAKE);
            break;
		
        /* Warnings (WARN) */
        case WARN_ID_DESC:
            fprintf(flogs, "%s: %s\n", MSJ_WARN_PREFIJO, MSJ_WARN_ID_DESC);
            break;

        case WARN_FIX_INV:
            fprintf(flogs, "%s: %s\n", MSJ_WARN_PREFIJO, MSJ_WARN_FIX_INV);
            break;

        case WARN_FULL_LIST:
            fprintf(flogs, "%s: %s\n", MSJ_WARN_PREFIJO, MSJ_WARN_FULL_LIST);
            break;
			
		case WARN_GPX_CONV:
            fprintf(flogs, "%s: %s\n", MSJ_WARN_PREFIJO, MSJ_WARN_GPX_CONV);
            break;

        /* Debug (DB) */
        case DB_BYTES_SYNC:
            fprintf(flogs, "%s: %s\n", MSJ_DEBUG_PREFIJO, MSJ_DB_BYTES_SYNC);
            break;

        case DB_ID_DETECT:
            fprintf(flogs, "%s: %s\n", MSJ_DEBUG_PREFIJO, MSJ_DB_ID_DETECT);
            break;

        case DB_MSJ_DET:
            fprintf(flogs, "%s: %s\n", MSJ_DEBUG_PREFIJO, MSJ_DB_MSJ_DET);
            break;

        case DB_MSJ_UP:
            fprintf(flogs, "%s: %s\n", MSJ_DEBUG_PREFIJO, MSJ_DB_MSJ_UP);
            break;
    }
    return ST_OK;
}
