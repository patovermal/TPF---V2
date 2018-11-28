#ifndef STATUS__H
#define STATUS__H

#include <stdio.h>

/* mensajes de errores */
#define TXT_ST_OK					"Correcto."
#define TXT_ST_ERR_DATO_INCOMP		"Dato incompleto."
#define TXT_ST_ERR_PUNT_NULL		"Puntero nulo."
#define TXT_ST_ERR_FECHA_INVALIDA 	"Fecha ingresa inválida."
#define TXT_ST_ERR_FIX_INVALIDO		"Fix inválido. Se ignora."

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
}status_t;

void print_log ( FILE* flog, status_t st );

#endif