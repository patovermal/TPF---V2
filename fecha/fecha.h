#ifndef FECHA__H
#define FECHA__H

#include "status.h"

#define EPOCH_TM_Y 	1900
#define EPOCH_TM_M 	1
#define EPOCH_TM_D 	0

typedef struct fecha_t{	int year;	/* estructura para la fecha */
			int month;
			int day;
			}fecha_t;

typedef struct hora_t{	int hh;		/* estructura para la hora */
			int mm;
			double ss;
			}hora_t;
      
status_t str2hora(char* cadena, hora_t* hora);
status_t str2fecha(char* cadena, fecha_t* hora);
status_t get_currentdate(fecha_t* fecha, hora_t* hora);

#endif