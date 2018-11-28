/**
* @file fecha.c
* @Author buyi97
* @date 18/11/2019
* @brief Funciones para fecha_t y hora_t
*/

#include <string.h>
#include <time.h>
#include "status.h"
#include "fecha.h"

/**
* @brief Pasar de una cadena hhmmss.ss a hora_t
* @param Cadena hhmmss.ss, puntero a estructura hora_t;
* @return El estado en el que terminó la función (si fue todo bien ST_OK)
*/

status_t str2hora(char* cadena, struct hora_t* hora){
	
	char* ctemp;				
	double ntemp;
	
	if ( !cadena | !hora)
		return ST_ERR_PUNT_NULL;
	
	ntemp = strtod(cadena, &ctemp);

	if ( *ctemp != '\0' )
		return ST_ERR_HORA_INVALIDA;

	if ( (hora->hh = (int)ntemp/10000) < 0 ||  hora->hh > 23 ) 	  /*me fijo que sea hora valida entre 0 y 23*/
		return ST_ERR_HORA_INVALIDA;

	ntemp -= hora->hh*10000; 									/*le saco las horas*/

	if ( (hora->mm = (int)ntemp/100) < 0 || hora->mm > 59)        /*me fijo que sea minutos validos entre 0 y 59*/
		return ST_ERR_HORA_INVALIDA;

	ntemp -= hora->mm*100;  // le saco los minutos

	if ( (hora->ss = ntemp) < 0 || hora->ss > 59  ) 		/*me fijo que sean segundos validos entre 0 y 59*/
		return ST_ERR_HORA_INVALIDA;
		
	return ST_OK;
}

/**
* @brief Pasar de una cadena yyyymmdd a fecha_t
* @param Cadena yyyymmdd, puntero a estructura fecha_t;
* @return El estado en el que terminó la función (si fue todo bien ST_OK)
*/

status_t str2fecha(char* cadfecha, struct fecha_t * fecha){

	char* temp;
	long int ntemp; 	/*numero temporario donde almaceno la fecha como 20180925 (ejemplo)*/
	
	if ( !cadfecha || !fecha )
		return ST_ERR_PUNT_NULL;
	
	ntemp = strtoul(cadfecha,&temp,10); 	/*ntemp = yyyymmdd*/

	if (*temp != '\0')
		return ST_ERR_FECHA_INVALIDA;

	fecha->year = ntemp/10000;

	ntemp -= fecha->year*10000; 	/*saco el año, queda ntemp = mmdd*/

	if ( (fecha->month = ntemp/100) > 12 || fecha->month < 1) 	/*me fijo que sea un dia valido entre 1 y 12*/
		return ST_ERR_FECHA_INVALIDA;

	ntemp -= fecha->month*100; 		/*me saco de encima el mes, queda ntemp = dd*/

	if ( (fecha->day = ntemp) > 31 || fecha->day < 1 ) /*me fijo que sea un dia valido entre 1 y 31*/
		return ST_ERR_FECHA_INVALIDA;

	return ST_OK; /*retorno un OK (todo salio bien)*/

}

/**
* @brief Pone la fecha y hora actual en un fecha_t y hora_t
* @param Puntero a fecha_t, puntero a hora_t;
* @return El estado en el que terminó la función (si fue todo bien ST_OK)
*/

status_t get_currentdate(struct fecha_t* fecha, struct hora_t* hora){
	
	if ( !fecha || !hora )
		return ST_ERR_PUNT_NULL;
	
	struct tm *tiempo;
	time_t tiempo_seg;
	tiempo_seg = time(NULL);
	if ( ! ( tiempo = localtime(&tiempo_seg) )
	    return ST_ERR_FECHA_INVALIDA;

	fecha->year 	= tiempo->tm_year + EPOCH_TM_Y;
	fecha->month 	= tiempo->tm_mon  + EPOCH_TM_M;
	fecha->day 	= tiempo->tm_mday + EPOCH_TM_D;
	hora->hh	= tiempo->tm_hour;
	hora->mm	= tiempo->tm_min;
	hora->ss	= tiempo->tm_sec;
	    
	return ST_OK;

}
