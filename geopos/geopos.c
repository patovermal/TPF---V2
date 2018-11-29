/**
* @file geopos.c
* @author buyi97
* @date 18/11/2019
* @brief Funciones para latitud y longitud
*/

#include "geopos.h"

/**
* @brief Pasar de una cadena ddmm.mm a latitud en grados
* @param cad_lat: cadena ddmm.mm
* @param indicador: cadena indicadora (norte "N" o sur "S")
* @param latitud: puntero a double latitud, donde se guardará el valor convertido de latitud
* @return status_t: el estado en el que termina la función (si fue todo bien ST_OK)
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
* @brief Pasar de una cadena dddmm.mm a longitud en grados
* @param cad_lon: cadena ddmm.mm
* @param indicador: cadena indicadora (oeste "W" o este "E")
* @param longitud: puntero a double longitud, donde se guardará el valor convertido de longitud
* @return status_t: el estado en el que termina la función (si fue todo bien ST_OK)
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