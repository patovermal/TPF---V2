/**
* @file ubx.c
* @Author mauroarbuello
* @date 22/11/2019
* @brief Funciones para UBX
*/

#include "ubx.h"

int main (void){
	uchar *sentencia;
	bool eof = false;
	FILE *fin,
	     *fout;
	int i=0;
	
	fin = fopen("UBXtest.txt", "rb");
	fout = fopen("prueba.txt", "wb");

	while(!eof){
		readline_ubx(&sentencia, &eof, fin);
		if(!eof){
			i++;
			fwrite(sentencia, 1, 98, fout);
		}
	}

	printf("se leyeron %d setencias UBX.\n", i);
	printf("%d\n", NAV_PVT);
 
	fclose(fin);
	fclose(fout);

	return EXIT_SUCCESS;
}

status_t proc_ubx(uchar * sentencia, ubx_t * ubx){
	proc_ubx_t funcion[] = {&proc_nav_pvt, &proc_tim_tos, &proc_nav_posllh};

	if ( !sentencia || !ubx )
		return ST_ERR_PUNT_NULL;

	/*lee el id*/
	switch(letol(sentencia, ID_POS, ID_LEN)){
		case UBX_NAV_PVT_ID:
			ubx->id = NAV_PVT;
			break;

		case UBX_TIM_TOS_ID:
			ubx->id = TIM_TOS;
			break;

		case UBX_NAV_POSLLH_ID:
			ubx->id = NAV_POSLLH;
			break;

		default:	
			/*PRINT LOG*/
			return ST_ERR_ID_INVALIDO;
	}

	return funcion[ubx->id](sentencia, ubx);
}

/**
* @brief Cargar en una estructura los datos de UBX_NAV_PVT a partir de un arreglo de bytes
* @param sentencia: arreglo de bytes
* @param ubx: puntero a ubx_t
* @return status_t : el estado en el que termina la función (si fue todo bien ST_OK)
*/

status_t proc_nav_pvt(const uchar * payload, ubx_t * ubx){
	if(!payload || !ubx){
		/*IMPRIMIR LOG*/
		return ST_ERR_PUNT_NULL;
	}

	/*carga el estado del fix*/
	ubx->type.pvt.gns_fix_ok = (payload[UBX_PVT_GNS_FIX_OK_POS] & UBX_PVT_GNS_FIX_OK_MASK)>>UBX_PVT_GNS_FIX_OK_SHIFT;

	/*carga el posicionamiento*/
	ubx->type.pvt.latitud = lotof(letol(payload,UBX_PVT_LATITUD_POS ,UBX_PVT_LATITUD_LEN));
	ubx->type.pvt.longitud = lotof(letol(payload,UBX_PVT_LONGITUD_POS ,UBX_PVT_LONGITUD_LEN));
	ubx->type.pvt.elevacion = (int) sletol(payload, UBX_PVT_ELEVACION_POS, UBX_PVT_ELEVACION_LEN);
	
	/*carga la fecha*/
	ubx->type.pvt.fecha.year = (int) letol(payload, UBX_PVT_YEAR_POS, UBX_PVT_YEAR_LEN);
	ubx->type.pvt.fecha.month = (int) letol(payload, UBX_PVT_MONTH_POS, UBX_PVT_MONTH_LEN);
	ubx->type.pvt.fecha.day = (int) letol(payload, UBX_PVT_DAY_POS, UBX_PVT_DAY_LEN);
	
	/*carga la hora*/
	ubx->type.pvt.hora.hh = (int) letol(payload, UBX_PVT_HH_POS, UBX_PVT_HH_LEN);
	ubx->type.pvt.hora.mm = (int) letol(payload, UBX_PVT_MM_POS, UBX_PVT_MM_LEN);
	ubx->type.pvt.hora.ss = (int) letol(payload, UBX_PVT_SS_POS, UBX_PVT_SS_LEN);

	return ST_OK;
}

/**
* @brief Cargar en una estructura los datos de UBX_TIM_ a partir de un arreglo de bytes
* @param sentencia: arreglo de bytes
* @param ubx: puntero a ubx_t
* @return status_t : el estado en el que termina la función (si fue todo bien ST_OK)
*/

status_t proc_tim_tos(const uchar * payload, ubx_t * ubx){
	if(!payload || !ubx){
		/*IMPRIMIR LOG*/
		return ST_ERR_PUNT_NULL;
	}

	/*carga la fecha*/
	ubx->type.tim_tos.fecha.year = (int) letol(payload, UBX_TIM_TOS_YEAR_POS, UBX_TIM_TOS_YEAR_LEN);
	ubx->type.tim_tos.fecha.month = (int) letol(payload, UBX_TIM_TOS_MONTH_POS, UBX_TIM_TOS_MONTH_LEN);
	ubx->type.tim_tos.fecha.day = (int) letol(payload, UBX_TIM_TOS_DAY_POS, UBX_TIM_TOS_DAY_LEN);
	
	/*carga la hora*/
	ubx->type.tim_tos.hora.hh = (int) letol(payload, UBX_TIM_TOS_HH_POS, UBX_TIM_TOS_HH_LEN);
	ubx->type.tim_tos.hora.mm = (int) letol(payload, UBX_TIM_TOS_MM_POS, UBX_TIM_TOS_MM_LEN); 
	ubx->type.tim_tos.hora.ss = (int) letol(payload, UBX_TIM_TOS_SS_POS, UBX_TIM_TOS_SS_LEN);

	return ST_OK;
}

/**
* @brief Cargar en una estructura los datos de UBX_NAV_POS a partir de un arreglo de bytes
* @param sentencia: arreglo de bytes
* @param ubx: puntero a ubx_t
* @return status_t : el estado en el que termina la función (si fue todo bien ST_OK)
*/

status_t proc_nav_posllh(const uchar * payload, ubx_t * ubx){
	if(!payload || !ubx){
		/*IMPRIMIR LOG*/
		return ST_ERR_PUNT_NULL;
	}

	/*carga el posicionamiento*/
	ubx->type.posllh.latitud = lotof(letol(payload, UBX_NAV_POSLLH_LATITUD_POS ,UBX_NAV_POSLLH_LATITUD_LEN));
	ubx->type.posllh.longitud = lotof(letol(payload, UBX_NAV_POSLLH_LONGITUD_POS ,UBX_NAV_POSLLH_LONGITUD_LEN));
	ubx->type.posllh.elevacion = (int) sletol(payload, UBX_NAV_POSLLH_ELEVACION_POS, UBX_NAV_POSLLH_ELEVACION_LEN);

	return ST_OK;
}

/**
* @brief Deja apuntando al arreglo de bytes a partir de los bytes de sincronismo
* @param sentencia: puntero a arreglo de bytes
* @param eof: puntero a bool, que indicará si se llegó o no a EOF
* @param fin: puntero al archivo de entrada
* @return status_t : el estado en el que termina la función (si fue todo bien ST_OK)
*/

/*Si el archivo tiene una sentencia UBX la función la carga en el buffer y devuelve un puntero "sentencia" al principio de la misma (no incluye los caracteres de sincronismo). Cuando el archivo se termina y no se encontraron sentencias devuelve eof=true y sentencia=NULL*/
status_t readline_ubx(uchar ** sentencia, bool * eof, FILE * fin){
	static uchar buffer[BUFFER_LEN];
	 static bool buffer_empty = true;

	/*punteros no nulos*/
	if(!sentencia || !eof || !fin){
		/*IMPRIMIR LOG*/
		return ST_ERR_PUNT_NULL;
	}

	/*carga inicial del buffer*/
	if(buffer_empty){
		fread_grind(buffer, 1, BUFFER_LEN, fin, eof);
		buffer_empty = false;
	}

	*eof = false;

	/*busca y devuelve sentencias UBX validadas hasta llegar a EOF*/
	while(get_sentence(buffer, eof, fin)){   
		if(checksum(buffer)){   
			*sentencia = buffer;
			return ST_OK;
		}else{
			/*IMPRIMIR LOG*/
		}
	}
	
	/*si salió del while es porque no hay más sentencias*/
	*sentencia = NULL;
	*eof=true;
	return ST_OK;
}

/**
* @brief Deja apuntando al arreglo de bytes a partir de los bytes de sincronismo
* @param sentencia: puntero a arreglo de bytes
* @param eof: puntero a bool, que indicará si se llegó o no a EOF
* @param fin: puntero al archivo de entrada
* @return status_t : el estado en el que termina la función (si fue todo bien ST_OK)
*/

/*busca una sentencia UBX y la mueve al principio del buffer (no incluye los caracteres de sincronismo)*/
bool get_sentence(uchar * buffer, bool * eof, FILE * fin){
	int i = 0;

	/*busca los dos caracteres de sincronismo en el buffer excepto en los dos últimos bytes*/
	for(i = 0 ; i < BUFFER_LEN-2 ; i++){
		if(buffer[i] == SYNC_CHAR1){ 
			if(buffer[i + 1] == SYNC_CHAR2){
				/*mueve la sentencia al principio del buffer*/
				load_buffer(buffer, i + 2, eof, fin);
				return true;
			}	
		}		
	}

	/*si salió del 'for' y se terminó el archivo es porque no hay más sentencias para leer*/
	if(feof(fin)){
		*eof = true;
		return false;
	}

	/*si salió del 'for' y no se terminó el archivo mueve los dos ultimos bytes al principio del buffer y vuelve a empezar*/
	load_buffer(buffer, BUFFER_LEN-2, eof, fin);
	return get_sentence(buffer, eof, fin);	
}

/*borra los bytes que se encuentran antes de la posición 'pos' y carga la misma cantidad al final del buffer leyendo del archivo. 'pos' queda ubicado al principo del buffer*/
void load_buffer(uchar * buffer, size_t pos, bool * eof, FILE * fin){
	int i;

	/*mueve la sentencia al principio del buffer*/
	for(i = 0 ; i < BUFFER_LEN-pos ; i++){
		buffer[i] = buffer[pos + i];
	}

	
	/*sobreescribe la parte final del buffer*/
	fread_grind(buffer + BUFFER_LEN - pos, 1, pos, fin, eof);
	return;
}

/*lee del archivo y sobreescribe la parte final del buffer */
void fread_grind(void *ptr, size_t size, size_t nmemb, FILE *stream, bool * eof){
	if(fread(ptr, size, nmemb, stream) != nmemb){ 
			if (ferror(stream)){
				/*IMPRIMIR LOG*/
			}
			if(feof(stream)){ 
				*eof = true;
				/*IMPRIMIR LOG*/
			}
	}
	return;
}

/*calcula el checksum*/
bool checksum(const uchar *buffer){
	uchar ck_a = 0,
	      ck_b = 0;
	long largo = 0;
	int i;
	
	/*lee el largo*/
	largo = letol(buffer, POS_LARGO, LEN_LARGO);
	
	/*si el largo leído es mayor a la máxima longitud de una sentencia UBX hay un error en la sentencia*/
	if(largo > BUFFER_LEN)
		/*IMPRIMIR LOG*/
		return false;

	/*Calcula el checksum*/
	for(i = 0 ; i < (POS_PAYLOAD + largo) ; i++){
		ck_a = ck_a + buffer[i];
		ck_b = ck_b + ck_a;
	}

	/*compara el checksum calculado*/
	if (ck_a == buffer[i++] && ck_b == buffer[i]){ /*al finalizar el 'for' anterior la posición 'i' corresponde al primer caracter de sincronismo*/
		return true;
	}else{
		return false;	
	}	
}
