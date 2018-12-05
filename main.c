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

	if ( ( st = proc_args( argc , argv , &config ) ) != ST_OK  ){
		fprintf(stderr, "%s\n", MSJ_ERR_OPEN_FILE);
		return EXIT_FAILURE;
	}

	if ( config.help == true ){
		print_help();
		return EXIT_SUCCESS;
	}

	if ( !config.bool_prot){
		fprintf(stderr, "%s\n", MSJ_ERR_NO_PROTOCOL);
		return EXIT_FAILURE;
	}

	if ( !config.maxlen ){
		config.maxlen = MAX_LEN_DEFAULT;
	}

	/* apertura de archivos */
	if ( !strcmp( config.fin , STR_STDIN ) || !config.bool_fin ){
		files.fin = stdin ;
	}
	else if ( config.protocol == P_NMEA ){
		if ( !(files.fin = fopen( config.fin , "r" ) ) ){
			fprintf(stderr, "%s\n", MSJ_ERR_OPEN_FILE);
			return EXIT_FAILURE;
		}
	}
	else if ( config.protocol == P_UBX ){
		if ( !(files.fin = fopen( config.fin , "rb" ) ) ){
			fprintf(stderr, "%s\n", MSJ_ERR_OPEN_FILE);
			return EXIT_FAILURE;
		}
	}
	else {
		fprintf(stderr, "%s\n", MSJ_ERR_NO_PROTOCOL);
	}

	if (!strcmp( config.fout , STR_STDOUT ) || !config.bool_fout ){
		files.fout = stdout ;
	}
	else if ( !(files.fout = fopen( config.fout , "w" ) ) ){
		fprintf(stderr, "%s\n", MSJ_ERR_OPEN_FILE);
		return EXIT_FAILURE;
	}
	if (!strcmp( config.flog , STR_STDERR ) || !config.bool_flog ){
		files.flog = stderr ;
	}

	else if ( ( init_logger(config.flog) ) != ST_OK ){
		fprintf(stderr, "%s\n", MSJ_ERR_OPEN_FILE);
		return EXIT_FAILURE;
	}

	/* fin de apertura de archivos */

	strncpy( metadata.nombre , config.nombre , MAX_NOMBRE );
	metadata.nombre[ MAX_NOMBRE ] = '\0';

	if ( get_currentdate( &metadata.fecha , &metadata.hora ) != ST_OK ){
		print_logs( ERR_GET_DATE );
		return EXIT_FAILURE;
	}

	print_headerGPX( files.fout );
	print_metadataGPX( &metadata , files.fout );
	print_trk_startGPX( files.fout );

	if ( (*pfunc[ config.protocol ])( &files , config.maxlen ) != ST_OK ){

		print_logs( ERR_PROC_FILE );

		if ( files.fin != stdin )
			fclose( files.fin );
		if ( files.fout != stdout )
			fclose( files.fout );
		if ( files.flog != stderr )
			close_logger();

		return EXIT_FAILURE;
	}

	print_trk_endGPX( files.fout );
	print_endGPX( files.fout );

	if ( files.fin != stdin )
		fclose( files.fin );
	if ( files.fout != stdout )
		fclose( files.fout );
	if ( files.flog != stderr )
		close_logger();

	return EXIT_SUCCESS;
}
