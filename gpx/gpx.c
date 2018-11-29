/**
* @file gpx.c
* @author buyi97
* @date 22/11/2019
* @brief Funciones para el formato gpx
*/

#include "gpx.h"

/**
* @brief Imprime el encabezado del gpx
* @param fout : puntero al archivo de salida
* @return void : nada
*/

void print_headerGPX(FILE * fout){
	
	if ( !fout )
		return;
	
	/*imprimir primer linea*/
	fprintf(fout, "%c%c %s %s %c%c%s%c %s%c%c%s%c%c%c\n\n",
	CHAR_START, CHAR_QUESTION,
	MSJ_XML,
	MSJ_VERSION, CHAR_EQUAL, CHAR_COMILLAS, VERSION_XML, CHAR_COMILLAS,
	MSJ_ENCODING, CHAR_EQUAL, CHAR_COMILLAS, ENCODING, CHAR_COMILLAS
	CHAR_QUESTION, CHAR_END
	);
	/*imprimir la segunda linea*/
	fprintf(fout, "%c%s %s %c%c%s%c %s %c%c%s%c %s %c%c%s%c%c\n",
	CHAR_START,
	MSJ_GPX,
	MSJ_VERSION,CHAR_EQUAL,CHAR_COMILLAS,VERSION_GPX,CHAR_COMILLAS,
	MSJ_CREATOR,CHAR_EQUAL,CHAR_COMILLAS,CREATOR,CHAR_COMILLAS,
	MSJ_XMLNS, CHAR_EQUAL,CHAR_COMILLAS,XMLNS,CHAR_COMILLAS,
	CHAR_END);

}

/**
* @brief Imprime la metatada del gpx
* @param fix = puntero a Gpx_mtdt, estructura que contiene la metadata del gpx
* @param fout: puntero al archivo de salida
* @return void : nada (si se pasa NULL no hace nada)
*/

void print_metadataGPX(Gpx_mtdt * fix, FILE * fout){
	
	if ( !fix || !fout )
		return;
	
	fprintf(fout, "\t%c%s%c\n",
	CHAR_START,	MSJ_METADATA, CHAR_END);	/*imprime la primer linea de metadata*/

	fprintf(fout, "\t\t%c%s%c%s%c%c%s%c\n",
	CHAR_START,MSJ_NAME, CHAR_END,
	fix->nombre,
	CHAR_START,CHAR_BAR,MSJ_NAME, CHAR_END);	/*imprime el nombre del archivo*/

	fprintf(fout, "\t\t%c%s%c%d%c%02d%c%02d%c%02d%c%02d%c%02d%c%c%c%s%c\n",
	CHAR_START,MSJ_TIME, CHAR_END,
	fix->fecha.year,CHAR_FECHA_SEP,fix->fecha.month,CHAR_FECHA_SEP,fix->fecha.day,CHAR_FECHA_END, 	/*imprime la fecha*/
	fix->hora.hh,CHAR_HORA_SEP,fix->hora.mm,CHAR_HORA_SEP,(int)fix->hora.ss,CHAR_HORA_END, 				/*imprime la hora*/
	CHAR_START,CHAR_BAR,MSJ_TIME, CHAR_END);	/*imprime la fecha y hora*/

	fprintf(fout, "\t%c%c%s%c\n",
	CHAR_START,	CHAR_BAR, MSJ_METADATA, CHAR_END);	/*imprime la primer ultima de metadata*/

}

/**
* @brief Imprime el comienzo del track
* @param fout : puntero al archivo de salida
* @return void : nada
*/

void print_trk_startGPX(FILE * fout){
	
	if ( !fout )
		return;
	
	fprintf(fout, "\t%c%s%c\n",
	CHAR_START,	MSJ_TRK, CHAR_END);

	fprintf(fout, "\t\t%c%s%c\n",
	CHAR_START,	MSJ_TRKSEG, CHAR_END);

}

/**
* @brief Imprime el trackpoint
* @param fix : puntero a la estructura gpx
* @param fout : puntero al archivo de salida
* @return void : nada
*/

void print_trkptGPX(gpx_t* fix, FILE * fout){
	
	if ( !fix || !fout )
		return;
	
	fprintf(fout, "\t\t\t%c%s %s%c%c%lf%c %s%c%c%lf%c%c\n",
	CHAR_START, MSJ_TRKPT,
	MSJ_LAT, CHAR_EQUAL, CHAR_COMILLAS,fix->latitud,CHAR_COMILLAS,
	MSJ_LON, CHAR_EQUAL, CHAR_COMILLAS,fix->longitud,CHAR_COMILLAS,
	CHAR_END);	/*imprime la primer linea de trkpt	ejemplo: <trkpt lat="19.918633" lon="-77.709016">*/

	fprintf(fout, "\t\t\t\t%c%s%c%lf%c%c%s%c\n",
	CHAR_START,MSJ_ELE, CHAR_END,
	fix->elevacion,
	CHAR_START,CHAR_BAR,MSJ_ELE, CHAR_END); /*imprime la elevacion ejemplo: <ele>0.000000</ele>*/

	fprintf(fout, "\t\t\t\t%c%s%c%d%c%02d%c%02d%c%02d%c%02d%c%06.03lf%c%c%c%s%c\n",
	CHAR_START,MSJ_TIME, CHAR_END,
	fix->fecha.year,CHAR_FECHA_SEP,fix->fecha.month,CHAR_FECHA_SEP,fix->fecha.day,CHAR_FECHA_END, 	/*imprime la fecha*/
	fix->hora.hh,CHAR_HORA_SEP,fix->hora.mm,CHAR_HORA_SEP,fix->hora.ss,CHAR_HORA_END, 				/*imprime la hora*/
	CHAR_START,CHAR_BAR,MSJ_TIME, CHAR_END);	/*imprime la fecha y hora ejemplo: <time>2018-09-30T11:28:36.854Z</time>*/

	fprintf(fout, "\t\t\t%c%c%s%c\n",
	CHAR_START,CHAR_BAR,MSJ_TRKPT,CHAR_END); /*imprime la ultima linea de trkpt ejemplo: </trkpt>*/

	/*la funcion imprime los datos de un track*/

}

/**
* @brief Imprime el fin del track
* @param fout : puntero alarchivo de salida
* @return void : nada
*/

void print_trk_endGPX(FILE * fout){

	if( !fout )
		return;
	
	fprintf(fout, "\t\t%c%c%s%c\n",
	CHAR_START,CHAR_BAR, MSJ_TRKSEG, CHAR_END);

	fprintf(fout, "\t%c%c%s%c\n",
	CHAR_START, CHAR_BAR, MSJ_TRK, CHAR_END);

}

/**
* @brief Imprime el fin del gpx
* @param fout : puntero al archivo de salida
* @return void : nada
*/

void print_endGPX(FILE * fout){
	
	if( !fout )
		return;
	
	fprintf(fout, "%c%c%s%c\n",
	CHAR_START,CHAR_BAR, MSJ_GPX, CHAR_END);	/*imprime la ultima linea de gpx ejemplo </gpx>*/

}
