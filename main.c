#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "./fecha/fecha.h"
#include "./args/args.h"
#include "./nmea/nmea.h"
#include "./gpx/gpx.h"
#include "./status/status.h"
#include "./help/help.h"
#include "./logs/logs.h"
#include "./files/files.h"
#include "./ubx/ubx.h"

int main(int argc, char* argv[]){

	config_t config;
	status_t st;
	Files_t files;
	status_t (*pfunc[])( Files_t * , size_t ) = { nmea2gpx , ubx2gpx  }; /*Puntero a funciones*/
	Gpx_mtdt metadata;

	strncpy( config.nombre , DEFAULT_NOMBRE , MAX_NOMBRE );
	config.nombre[MAX_NOMBRE] = '\0';
	
	init_logger(NULL); /* inicializa a stderr como archivo de log */
	
	/* proceso de argumentos por linea de comandos */
	if ( ( st = proc_args( argc , argv , &config ) ) != ST_OK  ){
		print_logs( ERR_PROC_ARGS );
		return EXIT_FAILURE;
	}
	/* fin proceso de argumentos por linea de comandos */
	
	/* comprobacion de comando de ayuda activado */
	if ( config.help == true ){
		print_help();
		return EXIT_SUCCESS;
	}
	/* fin comprobacion de comando de ayuda activado */
	
	
	/* apertura de archivos */
	
		/* log */
	if ( strcmp( config.flog , STR_STDERR ) && config.bool_flog && ( init_logger(config.flog) ) != ST_OK ) {
		print_logs( ERR_OPEN_FILE );
		return EXIT_FAILURE;
	}	
	
		/* in */
	if ( !strcmp( config.fin , STR_STDIN ) || !config.bool_fin ){
		files.fin = stdin ;
	}
	else if ( config.protocol == P_NMEA ){
		if ( !(files.fin = fopen( config.fin , "r" ) ) ){
			print_logs( ERR_OPEN_FILE );
			
			/*cierre de archivos*/
			close_logger();
			
			return EXIT_FAILURE;
		}
	}
	else if ( config.protocol == P_UBX ){
		if ( !(files.fin = fopen( config.fin , "rb" ) ) ){
			print_logs( ERR_OPEN_FILE );
			
			/*cierre de archivos*/
			close_logger();
			
			return EXIT_FAILURE;
		}
	}
	else {
		print_logs( ERR_NO_PROTOCOL );
		
		/*cierre de archivos*/
		close_logger();
		
		return EXIT_FAILURE;
	}
	
		/* out */
	if (!strcmp( config.fout , STR_STDOUT ) || !config.bool_fout ){
		files.fout = stdout ;
	}
	else if ( !(files.fout = fopen( config.fout , "w" ) ) ){
		print_logs( ERR_OPEN_FILE );
		
		/*cierre de archivos*/
		if ( files.fin != stdin )
			fclose( files.fin );
		close_logger();
		
		return EXIT_FAILURE;
	}
	/* fin de apertura de archivos */

	if ( !config.maxlen ){
		config.maxlen = MAX_LEN_DEFAULT;
	}	

	strncpy( metadata.nombre , config.nombre , MAX_NOMBRE );
	metadata.nombre[ MAX_NOMBRE ] = '\0';

	if ( get_currentdate( &metadata.fecha , &metadata.hora ) != ST_OK ){
		print_logs( ERR_GET_DATE );
		
		/*cierre de archivos*/
		if ( files.fin != stdin )
			fclose( files.fin );
		if ( files.fout != stdout )
			fclose( files.fout );
		close_logger();
		
		return EXIT_FAILURE;
	}
	
	if ( !config.bool_prot ){
		print_logs( ERR_NO_PROTOCOL );
		
		/*cierre de archivos*/
		if ( files.fin != stdin )
			fclose( files.fin );
		if ( files.fout != stdout )
			fclose( files.fout );
		close_logger();
		
		return EXIT_FAILURE;		
	}
	
	/* impresion de los headers y demas del gpx */
	print_headerGPX( files.fout );
	print_metadataGPX( &metadata , files.fout );
	print_trk_startGPX( files.fout );
	
	/* procesamiento del archivo de entrada */
	if ( (*pfunc[ config.protocol ])( &files , config.maxlen ) != ST_OK ){

		print_logs( ERR_PROC_FILE );
		
	}
	
	/* impresion de los ends del gpx */
	print_trk_endGPX( files.fout );
	print_endGPX( files.fout );
	
	/*cierre de archivos*/
	if ( files.fin != stdin )
		fclose( files.fin );
	if ( files.fout != stdout )
		fclose( files.fout );
	close_logger();

	return EXIT_SUCCESS;
}
