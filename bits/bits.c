/**
* @file logs.h
* @author mauroarbuello
* @date 24/11/2018
* @brief Funciones que operan con bits.
*/

#include "bits.h"

/**
* @brief Convierte de little-endian a entero sin signo.
* @param string: arreglo de bytes sin signo.
* @param pos: posicion del del numero a convertir en el arreglo.
* @param len: largo en bytes del numero a convertir.
* @return ulong: numero convertido.
*/
ulong letol(const uchar *string, size_t pos, size_t len){
	ulong entero = 0;
	int i;
	
	if ( !string )
		return 0;
	
	for(i = 0 ; i < len ; i++)
		entero |= string[pos + i] << SHIFT_BYTE*i;

	return entero;
}


/**
* @brief Convierte de little-endian (magnitud y signo) a entero con signo .
* @param string : arreglo de bytes.
* @param pos : posicion del numero a convertir en el arreglo.
* @param len : largo en bytes del numero a convertir.
* @return long : numero convertido.
*/
long sletol(const uchar *string, size_t pos, size_t len){
	long entero = 0,
		 signo;
	int i;
		
	if ( !string )
		return 0;

	/*convierte de little-endian a long*/
	for(i = 0 ; i < len-1 ; i++)
		entero |= string[pos + i] << SHIFT_BYTE*i;
	
	/*lee el signo y asigna su valor a la variable signo*/
	signo = ( string[pos + i]>>(SHIFT_BYTE-1)? -1 : 1 ;

	/*elimina el bit de signo y termina de convertir de little-endian a long*/
	entero |= ( (string[pos + i] & ~SLETOL_MASK_SIGNO)<< (SHIFT_BYTE*(len -1)) );

	return signo*entero;
}

/**
* @brief Convierte un decimal expresado en Estandar IEEE 754 a float.
* @param entero : Un numero decimal expresado en Estandar IEEE 754.
* @return Un double.
*/

/* convierte un decimal expresado en Estandar IEEE 754 a float */
double lotof(ulong entero){
	int i,
		signo = 0,
		exponente = 0,
		mantisa_int = 0;
	double decimal,
		   mantisa_double = 1;/*se inicializa con el bit implicito*/

    /* lee el signo */
	signo = (entero & LOTOF_MASK_SIGNO) >> SHIFT_SIGNO;
    	signo = ( signo == 1 ) ? -1 : 1;

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

/**
* @brief Convierte de little-endian a entero con signo.
* @param string: arreglo de bytes sin signo.
* @param pos: posicion del del número a convertir en el arreglo.
* @param len: largo en bytes del numero a convertir.
* @return long: numero convertido.
*/

long msletol(const uchar *string, size_t pos, size_t len){
	long entero = 0;
	size_t i;
		
	if ( !string )
		return 0;

	/*convierte de little-endian a long*/
	for(i = 0 ; i < len ; i++){
		entero |= string[pos + i] << SHIFT_BYTE*i;
	}
	
	return entero;
}
