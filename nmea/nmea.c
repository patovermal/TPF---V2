/**
* @file nmea.c
* @Author buyi97
* @date 22/11/2019
* @brief Funciones para NMEA
*/

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "geopos.h"
#include "status.h"
#include "fecha.h"
#include "gpx.h"
#include "nmea.h"

/**
* @brief Corta una cadena en un arreglo de cadenas segun el delimitador que le pases
* @param cadena: cadena ZDA
* @param ptr2ptrarray: puntero al arreglo de cadenas
* @param delim: char delimitador
* @return size_t : cantidad de cadenas es el arreglo de cadenas
*/

size_t split_delim (char * cadena, char ** ptr2ptrarray, char delim) {
	
	size_t i=0;	/* variable de iteracion */

	if ( !cadena || !ptr2ptrarray )	/* valido los punteros */
		return 0;
	
	ptr2ptrarray[0] = cadena;
	
	if ( !( ptr2ptrarray[1] = strchr(cadena,delim) ) )	/* busco el primer delim */
		return 0;
	
	*(ptr2ptrarray[1])='\0';	/* le asigno un \0 */
	ptr2ptrarray[1]++;			/* le hago apuntar a un lugar despues del \0 */
	
	for (i = 2; ( ptr2ptrarray[i] = strchr(ptr2ptrarray[i-1],delim) ) ; i++) {
		
		ptr2ptrarray[i][0] = '\0';
		ptr2ptrarray[i]++;
		
	}

	return i;
	
}

/**
* @brief Cargar en una estructura los datos de ZDA a partir de una cadena
* @param cadena: cadena ZDA
* @param nmea: puntero a nmea_t
* @return status_t : el estado en el que terminé la función (si fue todo bien ST_OK)
*/

status_t proc_zda(nmea_t* nmea, char* cadena){

	char* cad_arr[NMEA_DELIM_CANT_MAX];
	char * temp;

	if ( !cadena || !nmea )
		return ST_ERR_PUNT_NULL;

    /* split devuelve la cant de cadenas que separo. Si ese numero es menor a NMEA_DELIM_CANT_MIN, se descarta el dato*/
	if ( split_delim( cadena , cad_arr , NMEA_DELIM_CHAR ) < NMEA_DELIM_CANT_MIN )
		return ST_ERR_SENTENCIA_INVALIDA;
	
	/* convierto de cadena "hhmmss.ss" al tipo hora_t (struct hora) con la función str2hora (fecha.h) */
	if ( str2hora( cad_arr[NMEA_ZDA_HORA_POS] , &nmea->type.zda.hora ) != ST_OK )
		return ST_ERR_SENTENCIA_INVALIDA;

	/* verifico que el dia sea un numero y lo cargo en la estructura */
	nmea->type.zda.fecha.day = strtoul(cad_arr[NMEA_ZDA_DIA_POS], &temp, 10);
	
	if ( *temp != '\0' )
		return ST_ERR_SENTENCIA_INVALIDA;

	/* idem anterior para el mes */
	nmea->type.zda.fecha.month = strtoul(cad_arr[NMEA_ZDA_MES_POS], &temp, 10);
	
	if ( *temp != '\0' )
		return ST_ERR_SENTENCIA_INVALIDA;

	/* idem anterior para el año */
	nmea->type.zda.fecha.year = strtoul(cad_arr[NMEA_ZDA_ANIO_POS], &temp, 10);
	
	if ( *temp != '\0' )
		return ST_ERR_SENTENCIA_INVALIDA;

	/* verifico que zona horaria sea un numero y lo cargo en la estructura */
	nmea->type.zda.hh_utc = strtol(cad_arr[NMEA_ZDA_HHUTC_POS], &temp, 10);
	
	if ( *temp != '\0' )
		return ST_ERR_SENTENCIA_INVALIDA;

	/* idem anterior pero para los minutos de diferencia */
	nmea->type.zda.mm_utc = strtol(cad_arr[NMEA_ZDA_HHUTC_POS], &temp, 10);
	
	if ( *temp != '\0' )
		return ST_ERR_SENTENCIA_INVALIDA;
	
	return ST_OK;

}

/**
* @brief Cargar en una estructura los datos de RMC a partir de una cadena
* @param cadena: cadena RMC
* @param nmea: puntero a nmea_t
* @return status_t : el estado en el que terminé la función (si fue todo bien ST_OK)
*/

status_t proc_rmc(nmea_t* nmea, char* cadena){
	
	char* cad_arr[NMEA_DELIM_CANT_MAX];
	status_t st;
	char* ctemp;
	
	if ( !cadena || !nmea )
		return ST_ERR_PUNT_NULL;
	
	if ( split_delim( cadena , cad_arr , NMEA_DELIM_CHAR ) < NMEA_DELIM_CANT_MIN )
		return ST_ERR_SENTENCIA_INVALIDA;

	if ( ( st = str2hora( cad_arr[NMEA_RMC_HORA_POS] , &nmea->type.rmc.hora ) ) != ST_OK )
		return st;


	/* 	if ( strcmp( cad_arr[NMEA_RMC_ST_POS] , STR_RMC_ACTIVE ) == 0 )
		nmea->type.rmc.status = true;
	else 
		return ST_ERR_FIX_INVALIDA; */

	if ( ( st = str2lat( cad_arr[NMEA_RMC_LAT_POS], cad_arr[NMEA_RMC_LAT_POS + 1] , &nmea->type.rmc.latitud ) ) != ST_OK )
		return st;

	if ( ( st = str2lon( cad_arr[NMEA_RMC_LON_POS], cad_arr[NMEA_RMC_LON_POS + 1] , &nmea->type.rmc.longitud ) ) != ST_OK )
		return st;

	nmea->type.rmc.velocidad = strtod( cad_arr[NMEA_RMC_VEL_POS] , &ctemp );
	
	if ( *ctemp != '\0' )
		return ST_ERR_SENTENCIA_INVALIDA;
	
	nmea->type.rmc.ang_seg = strtod( cad_arr[NMEA_RMC_ANG_POS] , &ctemp );
	
	if ( *ctemp != '\0' )
		return ST_ERR_SENTENCIA_INVALIDA;
	
	if ( ( st = str2fecha( cad_arr[NMEA_RMC_FECHA_POS] , &nmea->type.rmc.fecha ) ) != ST_OK )
		return st;
	
	nmea->type.rmc.desv_mag = strtod( cad_arr[NMEA_RMC_DESV_POS] , &ctemp );
	
	if ( *ctemp != '\0' )
		return ST_ERR_SENTENCIA_INVALIDA;
	
	return ST_OK;
	
}

/**
* @brief Cargar en una estructura los datos de GGA a partir de una cadena
* @param cadena: cadena GGA
* @param nmea: puntero a nmea_t
* @return status_t : el estado en el que terminé la función (si fue todo bien ST_OK)
*/

status_t proc_gga(nmea_t* nmea, char* cadena){
	
	char* cad_arr[NMEA_DELIM_CANT_MAX];
	status_t st;
	char* ctemp;
	
	if ( !cadena || !nmea )
		return ST_ERR_PUNT_NULL;
	
	if ( split_delim( cadena , cad_arr , NMEA_DELIM_CHAR ) < NMEA_DELIM_CANT_MIN ){
		return ST_ERR_SENTENCIA_INVALIDA;
	}
	
	if ( ( st = str2hora( cad_arr[NMEA_GGA_HORA_POS] , &nmea->type.gga.hora ) ) != ST_OK ){
		return st;
	}
	if ( ( st = str2lat( cad_arr[NMEA_GGA_LAT_POS], cad_arr[NMEA_GGA_LAT_POS + 1] , &nmea->type.gga.latitud ) ) != ST_OK ){
		return st;
	}
	if ( ( st = str2lon( cad_arr[NMEA_GGA_LON_POS], cad_arr[NMEA_GGA_LON_POS + 1] , &nmea->type.gga.longitud ) ) != ST_OK ){
		return st;
	}
	
/* 	nmea->type.gga.calidad = strtoul( cad_arr[NMEA_GGA_CAL_POS] , &ctemp, 10 );

	if ( *ctemp != '\0' ){
		return ST_ERR_FIX_INVALIDO;
	}
	if ( nmea->type.gga.calidad < 1  || nmea->type.gga.calidad > MAX_CALIDAD ){
		return ST_ERR_FIX_INVALIDO;
	}
	
	nmea->type.gga.cant_satelites = strtoul( cad_arr[NMEA_GGA_SAT_POS] , &ctemp, 10 );

	if ( *ctemp != '\0' )
		return ST_ERR_FIX_INVALIDO;

	if ( nmea->type.gga.cant_satelites < 0  || nmea->type.gga.cant_satelites > MAX_SATELITES )
		return ST_ERR_FIX_INVALIDO;
	
	nmea->type.gga.hdop = strtod( cad_arr[NMEA_GGA_HDOP_POS] , &ctemp );
	
	if ( *ctemp != '\0' )
		return ST_ERR_SENTENCIA_INVALIDA;
	
	nmea->type.gga.elevacion = strtod( cad_arr[NMEA_GGA_ELE_POS] , &ctemp );
	
	if ( *ctemp != '\0' )
		return ST_ERR_SENTENCIA_INVALIDA;
	
	nmea->type.gga.sep_geoide = strtod( cad_arr[NMEA_GGA_SEP_POS] , &ctemp );
	
	if ( *ctemp != '\0' )
		return ST_ERR_SENTENCIA_INVALIDA; */
	
	return ST_OK;	
	
}

/**
* @brief Calcular el checksum de una cadena
* @param sentence : cadena con los chars a calcularle el checksum
* @return unsigned char : con el valor del cheksum
*/

unsigned char checksum ( const char * sentence ){
	
	unsigned char sum = 0;
	
	if ( !sentence )
		return 0;

	while ( *sentence ){
		sum ^= *sentence;
		sentence++;
    }
	
	return sum;
}

/**
* @brief Verificar el checksum de una cadena NMEA
* @param str_origen : cadena NMEA
* @return bool : true si se cumple el checksum, false si no
*/

bool verify_checksum ( char* str_origen ){
	
	char* ptr2chksum;
	char* temp;
	unsigned char char_temp;
	unsigned long int num_temp;

	temp = strchr(str_origen,NMEA_TOKEN_CHKSUM);
	
	if (!temp)
		return false;
	
	*temp = '\0';
	ptr2chksum = temp + 1;
	
	char_temp = checksum( str_origen + 1 );
	num_temp = strtoul( (ptr2chksum) , &temp , 16);
	
	if ( *temp != '\0' && *temp != '\n'  && *temp != '\r' ){		/*el '\r' para ser compatible con Windows (sistema usado para pruebas)*/
		return false;
	}
	
	if (char_temp == num_temp)
		return true;

	return false;

}

/**
* @brief Procesa una sentencia NMEA
* @param cadena : sentencia NMEA (char*)
* @param nmea : puntero a nmea_t (nmea_t*)
* @return status_t : el estado en el que termino (ST_OK si todo fue bien)
*/

status_t proc_nmea( char* cadena , nmea_t * nmea ){
	
	status_t st;
	status_t (*pfunc[ NMEA_CANT_TIPOS ])( nmea_t* , char* ) = { proc_rmc,  proc_zda,  proc_gga }; /*Puntero a funciones*/
	
	if ( !cadena || !nmea )
		return ST_ERR_PUNT_NULL;

	if ( verify_checksum( cadena ) == false ){
		return ST_ERR_SENTENCIA_INVALIDA;
	}

	if ( ( st = get_nmea_id( cadena , &(nmea->id) ) ) != ST_OK ){
		return st;
	}

	if ( ( st = (*pfunc[ nmea->id ])( nmea , cadena ) ) != ST_OK ){
		return st;
	}

	return ST_OK;
	
}

/**
* @brief Modifica un gpx_t con los datos del gga_t que viene en el nmea_t
* @param nmea : puntero al nmea_t del que se copiaran los datos del gga_t alli contenido
* @param gpx : puntero al gpx_t donde se guardaran los datos
* @return status_t : el estado en el que termino la función (ST_OK si salio bien)
*/

status_t gga2gpx( nmea_t* nmea , gpx_t* gpx){
	
	if ( !nmea || !gpx )
		return ST_ERR_PUNT_NULL;
	
	gpx->hora = nmea->type.gga.hora;
	gpx->latitud = nmea->type.gga.latitud;
	gpx->longitud = nmea->type.gga.longitud;
	gpx->elevacion= nmea->type.gga.elevacion;
	
	return ST_OK;
}

/**
* @brief Modifica un gpx_t con los datos del rmc_t que viene en el nmea_t
* @param nmea : puntero al nmea_t del que se copiaran los datos del rmc_t alli contenido
* @param gpx : puntero al gpx_t donde se guardaran los datos (como rmc_t no tiene datos de elevacion, le asignaremos 0)
* @return status_t : el estado en el que termino la función (ST_OK si salio bien)
*/

status_t rmc2gpx( nmea_t* nmea , gpx_t* gpx){
	
	if ( !nmea || !gpx )
		return ST_ERR_PUNT_NULL;
	
	gpx->hora = nmea->type.rmc.hora;
	gpx->latitud = nmea->type.rmc.latitud;
	gpx->longitud = nmea->type.rmc.longitud;
	gpx->elevacion= 0;
	
	return ST_OK;
}

/**
* @brief Modifica un gpx_t con los datos de fecha del zda_t que viene en el nmea_t
* @param nmea : puntero al nmea_t del que se copiaran los datos del zda_t alli contenido
* @param gpx : puntero al gpx_t donde se guardaran los datos (zda_t solo modifica la fecha)
* @return status_t : el estado en el que termino la función (ST_OK si salio bien)
*/

status_t zda2gpx( nmea_t* nmea , gpx_t* gpx){
	
	if ( !nmea || !gpx )
		return ST_ERR_PUNT_NULL;
	
	gpx->fecha = nmea->type.zda.fecha;
	
	return ST_OK;
}

/**
* @brief Obtiene el id de la cadena NMEA
* @param cadena : cadena NMEA (const)
* @param id : puntero a nmea_id
* @return status_t : el estado en el que termino la funcion (ST_OK si esta bien)
*/

status_t get_nmea_id ( const char *cadena , nmea_id* id ) {

	char * ptr2delim;
	
	if ( !cadena || !id )
		return ST_ERR_PUNT_NULL;
	
	ptr2delim = strchr ( cadena, NMEA_DELIM_CHAR );
  
 /*  Se valida ptr2coma para el caso en que es nulo. */
	if ( !ptr2delim )
		return ST_ERR_SENTENCIA_INVALIDA;

	if ( strncmp ( ptr2delim-NMEA_ID_LEN , NMEA_GGA_STR , NMEA_ID_LEN) == 0) {
		*id = GGA;
		return ST_OK;
	}
	if ( strncmp ( ptr2delim-NMEA_ID_LEN , NMEA_RMC_STR , NMEA_ID_LEN) == 0) {
		*id = RMC;
		return ST_OK;
	}
	if ( strncmp ( ptr2delim-NMEA_ID_LEN , NMEA_ZDA_STR , NMEA_ID_LEN) == 0) {
		*id = ZDA;
		return ST_OK;
	}
	
	return ST_ERR_ID_INVALIDO;

}
