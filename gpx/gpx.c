/**
* @file gpx.c
* @Author buyi97
* @date 22/11/2019
* @brief Funciones para el formato gpx
*/

#include <stdio.h>
#include "fecha.h"
#include "gpx.h"

/**
* @brief Imprime el encabezado del gpx
* @param void : nada
* @return void : nada
*/

void print_header(void){
	/* imprimir primer linea */
	printf("%s%s %s %s %s%s%s%s %s%s%s%s%s%s\n\n",
	CHAR_START, CHAR_QUESTION,
	MSJ_XML,
	MSJ_VERSION, CHAR_EQUAL, CHAR_COMILLAS,VERSION_XML,CHAR_COMILLAS,
	MSJ_ENCODING,CHAR_EQUAL,CHAR_COMILLAS,ENCODING,CHAR_COMILLAS
	CHAR_QUESTION, CHAR_END
	);
	/* imprimir la segunda linea */
	printf("%s%s %s %s%s%s%s %s %s%s%s%s %s %s%s%s%s%s\n",
	CHAR_START,
	MSJ_GPX,
	MSJ_VERSION,CHAR_EQUAL,CHAR_COMILLAS,VERSION_GPX,CHAR_COMILLAS,
	MSJ_CREATOR,CHAR_EQUAL,CHAR_COMILLAS,CREATOR,CHAR_COMILLAS,
	MSJ_XMLNS, CHAR_EQUAL,CHAR_COMILLAS,XMLNS,CHAR_COMILLAS,
	CHAR_END);

}

/**
* @brief Imprime la metatada del gpx
* @param Gpx_mtdt* = puntero a Gpx_mtdt, estructura que contiene la metadata del gpx
* @return void : nada (si se pasa NULL no hace nada)
*/

void print_metadata(Gpx_mtdt * fix){
	
	if ( !fix || !(fix->nombre) )
		return;
	
	printf("\t%s%s%s\n",
	CHAR_START,	MSJ_METADATA, CHAR_END);	//imprime la primer linea de metadata

	printf("\t\t%s%s%s%s%s%s%s%s\n",
	CHAR_START,MSJ_NAME, CHAR_END,
	fix->nombre,
	CHAR_START,CHAR_BAR,MSJ_NAME, CHAR_END);	//imprime el nombre del archivo

	printf("\t\t%s%s%s%d%s%02d%s%02d%s%02d%s%02d%s%02d%s%s%s%s%s\n",
	CHAR_START,MSJ_TIME, CHAR_END,
	fix->fecha.year,CHAR_FECHA_SEP,fix->fecha.month,CHAR_FECHA_SEP,fix->fecha.day,CHAR_FECHA_END, 	//imprime la fecha
	fix->hora.hh,CHAR_HORA_SEP,fix->hora.mm,CHAR_HORA_SEP,(int)fix->hora.ss,CHAR_HORA_END, 				//imprime la hora
	CHAR_START,CHAR_BAR,MSJ_TIME, CHAR_END);	//imprime la fecha y hora

	printf("\t%s%s%s%s\n",
	CHAR_START,	CHAR_BAR, MSJ_METADATA, CHAR_END);	//imprime la ultima de metadata

}

/**
* @brief Imprime el comienzo del track
* @param void : nada
* @return void : nada
*/

void print_trk_start(void){

	printf("\t%s%s%s\n",
	CHAR_START,	MSJ_TRK, CHAR_END);	//imprime la primer linea de trk

	printf("\t\t%s%s%s\n",
	CHAR_START,	MSJ_TRKSEG, CHAR_END);	//imprime la primer linea de trkseg

/* 	ejemplo <trk>
				<trkseg> */
}

/**
* @brief Imprime el trackpoint
* @param gpx_t* : puntero a la estructura gpx
* @return void : nada
*/

void print_trkpt(gpx_t* fix){
	
	if ( !fix )
		return;
	
	printf("\t\t\t%s%s %s%s%s%lf%s %s%s%s%lf%s%s\n",
	CHAR_START, MSJ_TRKPT,
	MSJ_LAT, CHAR_EQUAL, CHAR_COMILLAS,fix->latitud,CHAR_COMILLAS,
	MSJ_LON, CHAR_EQUAL, CHAR_COMILLAS,fix->longitud,CHAR_COMILLAS,
	CHAR_END);	//imprime la primer linea de trkpt	ejemplo: <trkpt lat="19.918633" lon="-77.709016">

	printf("\t\t\t\t%s%s%s%lf%s%s%s%s\n",
	CHAR_START,MSJ_ELE, CHAR_END,
	fix->elevacion,
	CHAR_START,CHAR_BAR,MSJ_ELE, CHAR_END); //imprime la elevacion ejemplo: <ele>0.000000</ele>

	printf("\t\t\t\t%s%s%s%d%s%02d%s%02d%s%02d%s%02d%s%06.03lf%s%s%s%s%s\n",
	CHAR_START,MSJ_TIME, CHAR_END,
	fix->fecha.year,CHAR_FECHA_SEP,fix->fecha.month,CHAR_FECHA_SEP,fix->fecha.day,CHAR_FECHA_END, 	//imprime la fecha
	fix->hora.hh,CHAR_HORA_SEP,fix->hora.mm,CHAR_HORA_SEP,fix->hora.ss,CHAR_HORA_END, 				//imprime la hora
	CHAR_START,CHAR_BAR,MSJ_TIME, CHAR_END);	//imprime la fecha y hora ejemplo: <time>2018-09-30T11:28:36.854Z</time>

	printf("\t\t\t%s%s%s%s\n",
	CHAR_START,CHAR_BAR,MSJ_TRKPT,CHAR_END); //imprime la ultima linea de trkpt ejemplo: </trkpt>

	/* la funcion imprime los datos de un fix */

}

/**
* @brief Imprime el fin del track
* @param void : nada
* @return void : nada
*/

void print_trk_end(void){

	printf("\t\t%s%s%s%s\n",
	CHAR_START,CHAR_BAR, MSJ_TRKSEG, CHAR_END);	//imprime la ultima linea de trkseg

	printf("\t%s%s%s%s\n",
	CHAR_START, CHAR_BAR, MSJ_TRK, CHAR_END);	//imprime la ultima linea de trk


/* 	ejemplo 	</trkseg>
			</trk> */
}

/**
* @brief Imprime el fin del gpx
* @param void : nada
* @return void : nada
*/

void print_end(void){

	printf("%s%s%s%s\n",
	CHAR_START,CHAR_BAR, MSJ_GPX, CHAR_END);	//imprime la ultima linea de gpx ejemplo </gpx>

}
