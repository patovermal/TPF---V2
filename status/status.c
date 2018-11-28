/**
* @file status.c
* @Author buyi97
* @date 22/11/2019
* @brief Funciones para el tipo status_t
*/

#include <stdio.h>
#include "status.h"
#include "fecha.h"

/**
* @brief Imprime el encabezado del gpx
* @param void : nada
* @return void : nada
*/

void print_log ( FILE* flog, status_t st ){
	
	static const char *dic_status[] = {     /*diccionario de estados, contiene el mensaje de error de cada estado*/
	TXT_ST_OK, TXT_ST_ERR_DATO_INCOMP, TXT_ST_ERR_PUNT_NULL, TXT_ST_ERR_FECHA_INVALIDA, TXT_ST_ERR_FIX_INVALIDO}; /*diccionario para status_t*/
	
	fprintf( flog , "%s\n" , "Imprimiendo log" );
	
}
