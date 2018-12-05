/**
* @file status.h
* @author buyi97
* @date 18/11/2019
* @brief Definido el tipo status_t
*/

#ifndef STATUS__H
#define STATUS__H

/**
 * @enum status_t
 * @brief Tipo de dato para los estados de las distintas funciones
 */
typedef enum status_t{ 
			ST_OK, 
			ST_ERR_DATO_INCOMP, 
			ST_ERR_PUNT_NULL, 
			ST_ERR_FECHA_INVALIDA,
			ST_ERR_HORA_INVALIDA,
			ST_ERR_FIX_INVALIDO, 
			ST_ERR_MISSING_ARG, 
			ST_ERR_NO_NAME,
			ST_ERR_NO_PROTOCOL,
			ST_ERR_NO_INFILE,
			ST_ERR_NO_OUTFILE,
			ST_ERR_NO_LOGFILE,
			ST_ERR_NOMEM,
			ST_ERR_LIST_FULL,
			ST_ERR_MAKE_NODE,
			ST_ERR_SENTENCIA_INVALIDA,
			ST_ERR_ID_INVALIDO,
			ST_ERR_LOG_INVALIDO,
}status_t;

#endif
