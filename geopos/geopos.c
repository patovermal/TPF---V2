/**
* @file geopos.c
* @Author buyi97
* @date 18/11/2019
* @brief Funciones para latitud y longitud
*/

#include <string.h>
#include <stdlib.h>
#include "status.h"
#include "geopos.h"

/**
* @brief Pasar de una cadena ddmm.mm a latitud
* @param Cadena ddmm.mm, cadena indicadora (norte o sur) , puntero a double latitud;
* @return El estado en el que terminó la función (si fue todo bien ST_OK)
*/

status_t str2lat(char* cad_lat, char* indicador, double* latitud){
	
	char *ctemp;
	double ntemp;
	
	if ( !cad_lat || !indicador || !latitud )
		return ST_ERR_PUNT_NULL;
	
	if ( strcmp(indicador, STR_NORTE) != 0 && strcmp(indicador, STR_SUR) != 0 ){
		return ST_ERR_FIX_INVALIDO;
	}
	
	ntemp = strtod(cad_lat, &ctemp);

	if ( *ctemp != '\0' )
		return ST_ERR_FIX_INVALIDO;

	if ( ( (*latitud) = (int)ntemp/100) > MAX_LATITUD ) 	/* compruebo que los grados sean menor al maximo*/
		return ST_ERR_FIX_INVALIDO;

	ntemp -= (*latitud)*100;			/*le saco los grados*/
	*latitud += ntemp/60; 			/*le agrego los minutos pasados a grados*/
	
	if ( strcmp(indicador, STR_SUR) == 0 )
		*latitud *= -1;
	
	return ST_OK;
}

/**
* @brief Pasar de una cadena ddmm.mm a longitud
* @param Cadena ddmm.mm, cadena indicadora (este u oeste), puntero a double latitud;
* @return El estado en el que terminó la función (si fue todo bien ST_OK)
*/

status_t str2lon(char* cad_lon, char* indicador, double* longitud){
	
	char *ctemp;
	double ntemp;
	
	if ( !cad_lon || !indicador || !longitud )
		return ST_ERR_PUNT_NULL;
	
	if ( strcmp(indicador, STR_ESTE) != 0 && strcmp(indicador, STR_OESTE) != 0 )
		return ST_ERR_FIX_INVALIDO;
	
	ntemp = strtod(cad_lon, &ctemp);

	if ( *ctemp != '\0' && *ctemp != '\n' && *ctemp != '\r' )
		return ST_ERR_FIX_INVALIDO;

	if ( ( (*longitud) = (int)ntemp/100) > MAX_LONGITUD ) 	/* compruebo que los grados sean menor al maximo */
		return ST_ERR_FIX_INVALIDO;

	ntemp -= (*longitud)*100;			/*le saco los grados*/
	*longitud += ntemp/60; 			/*le agrego los minutos pasados a grados*/
	
	if ( strcmp(indicador, STR_OESTE) == 0 )
		*longitud *= -1;
	
	return ST_OK;
}
