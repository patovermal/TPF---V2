/**
* @file args.h
* @author buyi97
* @date 22/11/2019
* @brief Defines para el procesamiento de los argumentos por linea de comandos
*/

#ifndef ARGS__H
#define ARGS__H

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../status/status.h"

#define MAX_NOMBRE 50
#define MAX_LEN_DEFAULT 10

#define PROTOCOL_CANT	2

#define CHAR_ARG_LCMD_START	'-'

#define STR_HELP_S "-h"
#define STR_HELP_L "--help"
#define STR_NAME_S "-n"
#define STR_NAME_L "--name"
#define STR_PROTOCOL_S "-p"
#define STR_PROTOCOL_L "--protocol"
#define STR_INFILE_S "-i"
#define STR_INFILE_L "--infile"
#define STR_OUTFILE_S "-o"
#define STR_OUTFILE_L "--outfile"
#define STR_LOGFILE_S "-l"
#define STR_LOGFILE_L "--logfile"
#define STR_MAXLEN_S "-m"
#define STR_MAXLEN_L "--maxlen"

#define STR_NMEA	"nmea"
#define STR_UBX		"ubx"

#define STR_STDIN	"-"
#define STR_STDOUT	"-"
#define STR_STDERR	"-"

/**
 * @enum protocol_t
 * @brief Tipo para el protocolo de GNSS
 */
/*Tipo de dato para PROTOCOLO*/
typedef enum protocol{
	P_NMEA,
	P_UBX,
}protocol_t;

/**
 * @struct config_t
 * @brief Estructura para la configuracion del programa, argumento que se le va a pasar a proc_args
 */
/*Estructura que le vamos a pasar a proc_argv, con las configuraciones del programa*/
typedef struct config{
	bool help;
	char nombre[MAX_NOMBRE+1];
	protocol_t protocol;
	bool bool_prot;
	char fin[MAX_NOMBRE+1];
	bool bool_fin;
	char fout[MAX_NOMBRE+1];
	bool bool_fout;
	char flog[MAX_NOMBRE+1];
	bool bool_flog;
	size_t maxlen;
}config_t;

/* Prototipos */
status_t proc_args( int argc, char* argv[], config_t* config );

#endif