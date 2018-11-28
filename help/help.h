#ifndef HELP__H
#define HELP__H

#include <stdio.h>
#include <string.h>

#define MAX_NOMBRE			50
#define MAX_STR 			500
#define MAX_CANTIDAD        100

/* signos */
#define CHAR_BARRA "/"
#define CHAR_COMA ","
#define START_COMENT "/*"
#define END_COMENT "*/"

#define MSJ_AYUDA_INICIO "------AYUDA------"
#define MSJ_ARG_LCMD "#LISTA DE COMANDOS VALIDOS CON SUS RESPECTIVOS FORMATOS#"
#define MSJ_INFO_PROG "#INFORMACION SOBRE EL PROGRAMA#"

/* formatos */
#define FORMATO_NOMBRE "max char leidos ="

/* mensajes std para todos los comandos */
#define MSJ_CMD_EQ "Ambos comandos son equivalentes."
#define MSJ_FORMATO "Formato esperado:"
#define MSJ_EJEMPLO "Ejemplo:"
#define MSJ_VALIDEZ "Condiciones de validez: "
#define SEPARADOR_ "------------------------------------"


/* help */
#define CMD_HELP1 "-h"
#define CMD_HELP2 "--help"

/* nombre */
#define CMD_NOMBRE1 "-n"
#define CMD_NOMBRE2 "--name"
#define MSJ_NOMBRE "nombre"


/* protocolo */
#define CMD_PROTOCOLO_1 "-p"
#define CMD_PROTOCOLO_2 "--protocol"
#define MSJ_PROTOCOLO "protocolo"
#define FORMATO_NMEA "nmea"
#define FORMATO_UBX "ubx"

/* archivo entrada */
#define CMD_ARCHIVO_IN_1 "-i"
#define CMD_ARCHIVO_IN_2 "--infile"
#define MSJ_ARCHIVO_IN "archivo_in"
#define FORMATO_ARCHIVO_IN "archivo_in.txt"

/* archivo salida */
#define CMD_ARCHIVO_OUT_1 "-o"
#define CMD_ARCHIVO_OUT_2 "--outfile"
#define MSJ_ARCHIVO_OUT "archivo_out"
#define FORMATO_ARCHIVO_OUT "archivo_out.txt"

/* archivo log */
#define CMD_ARCHIVO_LOG_1 "-l"
#define CMD_ARCHIVO_LOG_2 "-logfile"
#define MSJ_ARCHIVO_LOG "archivo_log"
#define FORMATO_ARCHIVO_LOG "archivo_logs.txt"

/* cantidad */
#define CMD_CANTIDAD_1 "-m"
#define CMD_CANTIDAD_2 "--maxlen"
#define MSJ_CANTIDAD "cantidad"
#define FORMATO_CANTIDAD "Máxima cantidad de mensajes a almacenar ="

/* ejemplos */
#define EJ_NOMBRE "@1_nombre_1@"
#define EJ_ARCHIVO_IN "datos_1.txt"
#define EJ_ARCHIVO_OUT "gpx_1.txt"
#define EJ_ARCHIVO_LOG "logs.txt"

/* comentarios */
#define COMENT_HELP "Se muestra una ayuda"
#define COMENT_NOMBRE "Modifica el metadato nombre"
#define COMENT_FORMATO "Indica el protocolo a leer"
#define COMENT_ARCHIVO_IN "Indica ell nombre del archivo a utilizar como entrada de datos"
#define COMENT_ARCHIVO_OUT "Indica el nombre a utilizar para el archivo gpx"
#define COMENT_ARCHIVO_LOG "Indica el nombre del archivo de logs"
#define COMENT_CANTIDAD "Indica la máxima cantidad de mensajes que se pueden almacenar en una lista"

/* info del programa */
#define MSJ_HORA_SIS "En caso de un error de lectura, se tomaran los datos del sistema"
#define MSJ_MAX_CHAR "El largo máximo de la cadena a procesar es "

/*Prototipos*/
void print_help(void);

#endif
