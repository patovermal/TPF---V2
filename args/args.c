/**
* @file args.c
* @author buyi97
* @date 22/11/2019
* @brief Funciones para el procesamiento de los argumentos por linea de comandos
*/

#include "args.h"

/**
* @brief Procesa los argumentos por linea de comandos
* @param argc : cantidad de argumentos que fueron ingresados (int)
* @param argv : arreglo de las cadenas que fueron ingresadas (char* [])
* @param config : puntero a config_t (config_t*)
* @return status_t : el estado en el que termino la función (ST_OK si salio bien)
*/

status_t  proc_args(int argc, char* argv[],config_t* config){
	
	char* ctemp;
	size_t ntemp;
	status_t st = ST_OK ;
	bool boolprot=false;
	size_t i;
	
	config->help = false;
	config->maxlen = 0;
	
	for(i=1;i<argc;i++){
		if ( argv[i][0] == CHAR_ARG_LCMD_START ){
			if( !strcmp(argv[i],STR_HELP_S) || !strcmp(argv[i],STR_HELP_L) ){
				config->help = true;
				return ST_OK;
			}
			else if( !strcmp(argv[i],STR_NAME_S) || !strcmp(argv[i],STR_NAME_L) ){
				if ( (i+1) < argc ){
					strncpy(config->nombre,argv[i+1],MAX_NOMBRE);
				}
				else {st = ST_ERR_NO_NAME; /*Printlog*/
				}
			}

			else if( !strcmp(argv[i],STR_PROTOCOL_S) || !strcmp(argv[i],STR_PROTOCOL_L) ){
				if ( (i+1) < argc){
					if ( !strcmp(argv[i+1], STR_NMEA ) ){
						config->protocol = P_NMEA;
						boolprot=true;
					}
					else if ( !strcmp(argv[i+1], STR_UBX ) ){
						config->protocol = P_UBX;
						boolprot=true;
					}						
				}
				else {	st = ST_ERR_NO_PROTOCOL; /*Printlog*/
				}
			}
			else if( !strcmp(argv[i],STR_INFILE_S) || !strcmp(argv[i],STR_INFILE_L) ){
				if ( (i+1)<argc ){
					strncpy( config->fin , argv[i+1] , MAX_NOMBRE );
				}
				else {	st = ST_ERR_NO_LOGFILE; /*Printlog*/
				}
			}
			else if( !strcmp(argv[i],STR_OUTFILE_S) || !strcmp(argv[i],STR_OUTFILE_L) ){
				if ( (i+1)<argc ){
					strncpy( config->fout, argv[i+1] , MAX_NOMBRE );
				}
				else {	st = ST_ERR_NO_LOGFILE; /*Printlog*/
				}
			}
			else if( !strcmp(argv[i],STR_LOGFILE_S) || !strcmp(argv[i],STR_LOGFILE_L) ){
				if ( (i+1)<argc ){
					strncpy( config->flog , argv[i+1] , MAX_NOMBRE );
				}
				else {	st = ST_ERR_NO_LOGFILE; /*Printlog*/
				}
			}
			else if( !strcmp(argv[i],STR_MAXLEN_S)  || !strcmp(argv[i],STR_MAXLEN_L) ){
				if ( (i+1)<argc ){
					ntemp = strtoul( argv[i+1] , &ctemp , 10 );
					if ( ctemp != '\0'){
						/* st = ST_ERR_NO_MAXLEN; */ /*Printlog*/
					}
					else { config->maxlen = ntemp;
					}
				}	
				else {	st = ST_ERR_NO_LOGFILE; /*Printlog*/
				}
			}
		}
	}
	
/* 	if ( boolprot == false )
		return ST_ERR_NO_PROTOCOL; */ /*Printlog*/
	
	return ST_OK;
}
