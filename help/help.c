/**
* @file help.c
* @Author patovermal
* @date 26/11/2019
* @brief Impresion de la ayuda del programa
*/

#include "help.h"

/**
* @brief Imprime la ayuda del programa
* @param void: no recibe parámetros
* @return void : no devuelve nada
*/
void print_help (void) {
  fprintf(stdout , "%s\n\n", MSJ_AYUDA_INICIO);
  fprintf(stdout , "%s\n", SEPARADOR_);
  fprintf(stdout , "%s\n", SEPARADOR_);
  fprintf(stdout , "%s\n", MSJ_ARG_LCMD);
  fprintf(stdout , "%s\n", SEPARADOR_);

  /* help */
  fprintf(stdout , "%s\n", CMD_HELP1);
  fprintf(stdout , "%s\n", CMD_HELP2);
  fprintf(stdout , "%s\n", MSJ_CMD_EQ);

  fprintf(stdout , "%s%s%s\n", START_COMENT, COMENT_HELP, END_COMENT);
  fprintf(stdout , "%s\n", SEPARADOR_);

  /* nombre */
  fprintf(stdout , "%s %s\n", CMD_NOMBRE1, MSJ_NOMBRE);
  fprintf(stdout , "%s %s\n", CMD_NOMBRE2, MSJ_NOMBRE);

  fprintf(stdout , "%s\n", MSJ_CMD_EQ);
  fprintf(stdout , "%s %s %d\n", MSJ_FORMATO, FORMATO_NOMBRE, MAX_NOMBRE);
  fprintf(stdout , "%s %s\n", MSJ_EJEMPLO , EJ_NOMBRE);
  fprintf(stdout , "%s%s%s\n", START_COMENT, COMENT_NOMBRE, END_COMENT);
  fprintf(stdout , "%s\n", SEPARADOR_);

  /* protocolo */
  fprintf(stdout, "%s %s\n", CMD_PROTOCOLO_1, MSJ_PROTOCOLO);
  fprintf(stdout, "%s %s\n", CMD_PROTOCOLO_2, MSJ_PROTOCOLO);

  fprintf(stdout , "%s\n", MSJ_CMD_EQ);
  fprintf(stdout , "%s %s %s %s\n", MSJ_FORMATO, FORMATO_NMEA, CHAR_BARRA, FORMATO_UBX);
  fprintf(stdout , "%s%s%s\n", START_COMENT, COMENT_FORMATO, END_COMENT);
  fprintf(stdout , "%s\n", SEPARADOR_);

  /* archivo entrada */
  fprintf(stdout, "%s %s\n", CMD_ARCHIVO_IN_1, MSJ_ARCHIVO_IN);
  fprintf(stdout, "%s %s\n", CMD_ARCHIVO_IN_2, MSJ_ARCHIVO_IN);

  fprintf(stdout , "%s\n", MSJ_CMD_EQ);
  fprintf(stdout , "%s %s\n", MSJ_FORMATO, FORMATO_ARCHIVO_IN);
  fprintf(stdout , "%s %s\n", MSJ_EJEMPLO , EJ_ARCHIVO_IN);
  fprintf(stdout , "%s%s%s\n", START_COMENT, COMENT_ARCHIVO_IN, END_COMENT);
  fprintf(stdout , "%s\n", SEPARADOR_);

  /* archivo salida */
  fprintf(stdout, "%s %s\n", CMD_ARCHIVO_OUT_1, MSJ_ARCHIVO_OUT);
  fprintf(stdout, "%s %s\n", CMD_ARCHIVO_OUT_2, MSJ_ARCHIVO_OUT);

  fprintf(stdout , "%s\n", MSJ_CMD_EQ);
  fprintf(stdout , "%s %s\n", MSJ_FORMATO, FORMATO_ARCHIVO_OUT);
  fprintf(stdout , "%s %s\n", MSJ_EJEMPLO , EJ_ARCHIVO_OUT);
  fprintf(stdout , "%s%s%s\n", START_COMENT, COMENT_ARCHIVO_OUT, END_COMENT);
  fprintf(stdout , "%s\n", SEPARADOR_);

  /* archivo log */
  fprintf(stdout, "%s %s\n", CMD_ARCHIVO_LOG_1, MSJ_ARCHIVO_LOG);
  fprintf(stdout, "%s %s\n", CMD_ARCHIVO_LOG_2, MSJ_ARCHIVO_LOG);

  fprintf(stdout , "%s\n", MSJ_CMD_EQ);
  fprintf(stdout , "%s %s\n", MSJ_FORMATO, FORMATO_ARCHIVO_LOG);
  fprintf(stdout , "%s %s\n", MSJ_EJEMPLO , EJ_ARCHIVO_LOG);
  fprintf(stdout , "%s%s%s\n", START_COMENT, COMENT_ARCHIVO_LOG, END_COMENT);
  fprintf(stdout , "%s\n", SEPARADOR_);

  /* cantidad */
  fprintf(stdout, "%s %s\n", CMD_CANTIDAD_1, MSJ_CANTIDAD);
  fprintf(stdout, "%s %s\n", CMD_CANTIDAD_2, MSJ_CANTIDAD);

  fprintf(stdout , "%s\n", MSJ_CMD_EQ);
  fprintf(stdout , "%s %s %d\n", MSJ_FORMATO, FORMATO_CANTIDAD, MAX_CANTIDAD);
  fprintf(stdout , "%s%s%s\n", START_COMENT, COMENT_CANTIDAD, END_COMENT);
  fprintf(stdout , "%s\n", SEPARADOR_);
}
