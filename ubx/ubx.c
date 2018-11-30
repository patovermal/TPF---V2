s (256 sloc)  9.34 KB
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
	
	fin = fopen("ubx-nav-posllh_short.ubx", "rb");
	fout = fopen("prueba.txt", "wb");

	if(ferror(fin))
		printf("error de lectura\n");

	if(!fin){
		printf("%s\n", "no existe el archivo de entrada");
		return EXIT_FAILURE;
	}


	while(!eof){
		if(readline_ubx(&sentencia, &eof, fin) != ST_OK){
			/*PRINT LOG*/
			printf("puntero nulo\n");
			break;
		}

		if(sentencia){
			i++;
			fwrite(sentencia, 1, 98, fout);
		}
	}

	printf("se leyeron %d setencias UBX.\n", i);
 
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
		size_t leido; /*se declara variables dentro del if porque solo son necesarias la primera vez que se llama a la función*/
	 	int i;

		leido = fread_grind(buffer, 1, BUFFER_LEN, fin);
		printf("leido = %d\n",(int)leido );
		/*completa el final del buffer con ceros si no hay más datos para leer del archivo*/
		if(feof(fin)){
			for(i = leido ; i < BUFFER_LEN ; i++){
				buffer[i] = 0; 
			}
		}
		buffer_empty = false;	
	}

	*eof = false;

	/*busca y devuelve sentencias UBX validadas hasta llegar a EOF*/
	while(get_sentence(buffer, fin)){ 
		if(checksum(buffer)){   printf("checksum: ok\n"); 
			*sentencia = buffer;
			return ST_OK;
		}else{
			/*IMPRIMIR LOG*/ printf("checksum: nop\n"); 
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
bool get_sentence(uchar * buffer, FILE * fin){
	int i;
	
	if (!buffer ||!fin)
		return ST_ERR_PUNT_NULL;

	/*busca los dos caracteres de sincronismo en el buffer excepto en los dos últimos bytes*/
	for(i = 0 ; i < BUFFER_LEN-2 ; i++){
		if(buffer[i] == SYNC_CHAR1){ 
			if(buffer[i + 1] == SYNC_CHAR2){ printf("encontró la sentencia %02x%02x\n le sigue %02x%02x (%02x%02x)\n",buffer[96], buffer[97], buffer[98], buffer[99],buffer[196], buffer[197]); 
				/*mueve la sentencia al principio del buffer*/
				load_buffer(buffer, i + 2, fin);
				return true;
			}	
		}		
	}

	/*si salió del 'for' y se terminó el archivo es porque no hay más sentencias para leer*/
	if(feof(fin))
		return false;


	/*si salió del 'for' y no se terminó el archivo mueve los dos últimos bytes al principio del buffer y vuelve a empezar*/
	load_buffer(buffer, BUFFER_LEN-2, fin);
	return get_sentence(buffer, fin);	
}

/* mueve al principio del buffer la sentencia ubicada en la posición 'pos' y completa el resto del buffer leyendo del archivo*/
void load_buffer(uchar * buffer, size_t pos, FILE * fin){
	int i;
	size_t leido;
	
	if (!buffer || !fin)
		return ST_ERR_PUNT_NULL;

	/*mueve la sentencia al principio del buffer*/
	for(i = 0 ; i < BUFFER_LEN - pos ; i++){
		buffer[i] = buffer[pos + i];
	}

	/*sobreescribe la parte final del buffer*/
	if((leido = fread_grind(buffer + BUFFER_LEN - pos, 1, pos, fin)) != pos){
		/*completa el final del buffer con ceros si no hay más datos para leer del archivo*/
		if(feof(fin)){ printf("pos = %d\nleido = %d \n empieza a poner ceros en %02x%02x%02x%02x\n",(int)pos,(int)leido,buffer[BUFFER_LEN - pos + leido],buffer[BUFFER_LEN - pos + leido+1],buffer[BUFFER_LEN - pos + leido+2],buffer[BUFFER_LEN - pos + leido+3]);
			for(i = BUFFER_LEN - pos + leido ; i < BUFFER_LEN ; i++){
				buffer[i] = 0;
			} 

		}
	}	
	
	return;
}

/*lee del archivo y valida los pámetros de fread*/
size_t fread_grind(void *ptr, size_t size, size_t nmemb, FILE *stream){
	size_t leido;
	
	if (!ptr || !stream)
		return ST_ERR_PUNT_NULL;
	
	if((leido = fread(ptr, size, nmemb, stream)) != nmemb){ 
			if (ferror(stream)){
				/*IMPRIMIR LOG*/
			}
			if(feof(stream)){ 
				/*IMPRIMIR LOG*/printf("%s\n","EOF (fread_grind)" );printf("leido = %d (fread_grind)\n",(int)leido );
			}
	}
	return leido;
}

/*calcula el checksum*/
bool checksum(const uchar *buffer){
	uchar ck_a = 0,
	      ck_b = 0;
	long largo = 0;
	int i;
	
	if (!buffer)
		return ST_ERR_PUNT_NULL;
	
	/*lee el largo*/
	largo = letol(buffer, LARGO_POS, LARGO_LEN);
	
	/*si el largo leído es mayor al espacio disponible en el buffer no se puede realizar la lectura*/
	if(largo > BUFFER_LEN - ID_LEN - LARGO_LEN - CHECKSUM_LEN)
		/*IMPRIMIR LOG*/
		return false;

	/*Calcula el checksum*/
	for(i = 0 ; i < (PAYLOAD_POS + largo) ; i++){
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
