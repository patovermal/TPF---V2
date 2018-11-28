/**
* @file logs.h
* @author pulpo
* @date 24/11/2018
* @brief Funciones que operan con bits.
*/

#include <math.h>
#include "bits.h"

/**
* @brief Convierte de little-endian a entero sin signo.
* @param string
* @param pos
* @param len
* @return ulong : Un entero sin signo
*/
ulong letol(const uchar *string, size_t pos, size_t len){
	ulong entero = 0;
	int i;

	for(i = 0 ; i < len ; i++)
		entero |= string[pos + i] << SHIFT_BYTE*i;

	return entero;
}


/**
* @brief Convierte de little-endian a entero con signo.
* @param string
* @param pos
* @param len
* @return ulong : Un entero con signo
*/
long sletol(const uchar *string, size_t pos, size_t len){
	long entero = 0,
		 signo;
	int i;
		

	/*lee el signo y asigna su valor a la variable signo*/
	if(string[pos + len -1]>>7){ 
			signo = -1;
	}else{
		signo = 1;
	}

	/*convierte de little-endian a long*/
	for(i = 0 ; i < len-1 ; i++)
		entero |= string[pos + i] << SHIFT_BYTE*i;

	/*elimina el bit de signo y termina de convertir de little-endian a long*/
	entero |= ((string[pos + len -1] & ~SLETOL_MASK_SIGNO)<< SHIFT_BYTE*(len -1));

	return signo*entero;
}

/**
* @brief Convierte un decimal expresado en Estándar IEEE 754 a float.
* @param entero : Un numero en decimal expresado según el estándar IEEE.
* @return Un double.
*/

/* convierte un decimal expresado en Estándar IEEE 754 a float */
double lotof(ulong entero){
	int i,
		signo = 0,
		exponente = 0,
		mantisa_int = 0; 
	double decimal,
		   mantisa_double = 1;/*se inicializa con el bit implícito*/

	/* lee el signo */
	signo = (entero & LOTOF_MASK_SIGNO) >> SHIFT_SIGNO;
	if(signo==1){
		signo = -1;
	}else{
		signo = 1;
	}

	/*lee el exponente*/
	exponente = (entero & MASK_EXPONENTE) >> SHIFT_EXPONENTE;
	exponente -= 127;

	/*lee la mantisa*/
	mantisa_int = entero & MASK_MANTISA;
	for(i = 0 ; i < 23 ; i++){
		if((mantisa_int>>(22-i))&1)
			mantisa_double += ldexp(1, -i - 1);
	}
	
	/*calcula el valor en punto flotante */
	decimal = signo * ldexp(mantisa_double, exponente);

	return decimal;
}


