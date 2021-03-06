/**
* @file ubx.c
* @Author mauroarbuello
* @date 22/11/2019
* @brief Funciones para UBX
*/

#include "ubx.h"

/**
* @brief imprime en formato gpx los datos leidos en formato ubx
* @param files: estructura que contiene punteros a los flujos de entrada, salida
* @param maxlen: puntero a estructura gpx
* @return status_t : el estado en el que termina la funcion (si fue todo bien ST_OK)
*/
status_t ubx2gpx( Files_t * files, size_t maxlen){

	ubx2gpx_t funcion[] ={&pvt2gpx, &tos2gpx, &posllh2gpx};
	ubx_t * ubx;
	bool eof = false;
	uchar * sentencia;
	List lista;
	status_t st;
	gpx_t * gpx;
	fecha_t fecha_cur;
	hora_t hora_cur;
	bool flag_cont=false;

	if (!files)
		return ST_ERR_PUNT_NULL;

	if ( !files->fin || !files->fout )
		return ST_ERR_PUNT_NULL;

	srand(time(NULL));

	if ((st = get_currentdate(&fecha_cur, &hora_cur)) != ST_OK){
		print_logs(ERR_GET_DATE);
		return st;
	}

	if ((st = Make_list(&lista, maxlen)) != ST_OK){
		print_logs(ERR_LIST_MAKE);
		return st;
	}

	if ( !(ubx = (ubx_t*) calloc(1, sizeof(ubx_t))) ){
		print_logs( ERR_NO_MEM);
		return ST_ERR_NOMEM;
	}

	while( !eof ){
		
		flag_cont=false;
		
		readline_ubx(&sentencia, &eof, files->fin);
		
		if ((st = proc_ubx(sentencia, ubx)) != ST_OK){
			if ( st==ST_ERR_PUNT_NULL && eof )
				print_logs( DB_EOF );
			else{
				print_logs( ERR_INV_UBX );
			}
			flag_cont = true;
		}

		if ( !flag_cont ){
			print_logs( DB_MSJ_DET );
		}
		if ( !flag_cont ){
			switch ( ubx->id ){
				case NAV_PVT:

					fecha_cur = ubx->type.pvt.fecha;
					hora_cur = ubx->type.pvt.hora;
					print_logs( DB_DATE_ACT );
					break;

				case TIM_TOS:

					fecha_cur = ubx->type.tim_tos.fecha;
					hora_cur = ubx->type.tim_tos.hora;
					print_logs( DB_DATE_ACT );
					flag_cont = true;
					break;

				case NAV_POSLLH:

					break;

				default:
					flag_cont = true;
					break;
			}
		}


		if ( !flag_cont && !(gpx = (gpx_t*) calloc( 1, sizeof(gpx_t)))){
			print_logs( ERR_NO_MEM );
			free(ubx);
			ubx = NULL;
			Destroy_list(&lista, &free);
	    	return ST_ERR_NOMEM;
		}

		if ( !flag_cont && ( st = funcion[ubx->id]( ubx, gpx)) != ST_OK ) {
			free(gpx);
			gpx = NULL;
			if ( st == ST_ERR_FIX_INVALIDO ){
				print_logs( WARN_FIX_INV );
			}
			else{
				print_logs( WARN_GPX_CONV );
			}
			flag_cont = true;
		}
		
		if ( !flag_cont ){
			gpx->fecha = fecha_cur;
			gpx->hora = hora_cur;
		}

		if ( !flag_cont && (st = AppendR_list( &lista, gpx)) != ST_OK){
			free(gpx);
			gpx = NULL;
			print_logs( WARN_FULL_LIST );
		}
		if ( !flag_cont ){
			print_logs( DB_MSJ_UP );
		}

		if ( !flag_cont && rand()%10 <= 7 ){
			print_trkptGPX( PopL_list( &lista ) ,files->fout);
			Destroy_firstnode( &lista, &free );
			print_logs( DB_MSJ_PRINT );
		}
	}

	while ( Cant_act_list( &lista)){
		print_trkptGPX( PopL_list( &lista), files->fout);
		Destroy_firstnode( &lista, &free);
		print_logs( DB_MSJ_PRINT );
	}

	free(ubx);
	Destroy_list( &lista , &free );
	return ST_OK;
}

/**
* @brief Carga en una estructura gpx_t los datos de una sentencia pvt
* @param ubx: puntero a estructura ubx
* @param gpx: puntero a estructura gpx
* @return status_t : el estado en el que termina la funcion (si fue todo bien ST_OK)
*/

status_t pvt2gpx( ubx_t * ubx, gpx_t * gpx){

	if ( !ubx || !gpx ){
		return ST_ERR_PUNT_NULL;
	}
	if(ubx->id != NAV_PVT){
		return ST_ERR_ID_INVALIDO;
	}
	if( !ubx->type.pvt.gns_fix_ok ){
		return ST_ERR_FIX_INVALIDO;
	}
	
	gpx->latitud = ubx->type.pvt.latitud;
	gpx->longitud = ubx->type.pvt.longitud;
	gpx->elevacion = ubx->type.pvt.elevacion;

	return ST_OK;
}

/**
* @brief Carga en una estructura gpx_t los datos de una sentencia posllh
* @param ubx: puntero a estructura ubx
* @param gpx: puntero a estructura gpx
* @return status_t : el estado en el que termina la funcion (si fue todo bien ST_OK)
*/
status_t tos2gpx( ubx_t* ubx , gpx_t* gpx){
/*se utilizaba en una implementacion anterior y se conserva en caso de ser necesaria en futuras implementaciones*/


	if ( !ubx || !gpx ){
		return ST_ERR_PUNT_NULL;
	}
	if(ubx->id != TIM_TOS){
		return ST_ERR_ID_INVALIDO;
	}
	
	gpx->fecha = ubx->type.tim_tos.fecha;
	gpx->hora = ubx->type.tim_tos.hora;

	return ST_OK;
}

/**
* @brief Carga en una estructura gpx_t los datos de una sentencia posllh
* @param ubx: puntero a estructura ubx
* @param gpx: puntero a estructura gpx
* @return status_t : el estado en el que termina la funcion (si fue todo bien ST_OK)
*/
status_t posllh2gpx( ubx_t* ubx , gpx_t* gpx){

	if ( !ubx || !gpx )
		return ST_ERR_PUNT_NULL;

	if(ubx->id != NAV_POSLLH)
		return ST_ERR_ID_INVALIDO;

	gpx->latitud = ubx->type.posllh.latitud;
	gpx->longitud = ubx->type.posllh.longitud;
	gpx->elevacion = ubx->type.posllh.elevacion;

	return ST_OK;
}

/**
* @brief Cargar en una estructura los datos de de una sentencia UBX a partir de un arreglo de bytes
* @param sentencia: arreglo del que se lee la sentencia
* @param ubx: puntero a estructura ubx
* @return status_t : el estado en el que termina la funcion (si fue todo bien ST_OK)
*/
status_t proc_ubx(uchar * sentencia, ubx_t * ubx){
	proc_ubx_t funcion[] = {&proc_nav_pvt, &proc_tim_tos, &proc_nav_posllh};

	if ( !sentencia || !ubx )
		return ST_ERR_PUNT_NULL;

	/*lee el id*/
	switch(letol(sentencia, ID_POS, ID_LEN)){
		case UBX_NAV_PVT_ID:
			ubx->id = NAV_PVT;
			print_logs( DB_ID_DETECT);
			break;

		case UBX_TIM_TOS_ID:
			print_logs( DB_ID_DETECT);
			ubx->id = TIM_TOS;
			break;

		case UBX_NAV_POSLLH_ID:
			print_logs( DB_ID_DETECT );
			ubx->id = NAV_POSLLH;
			break;

		default:
			print_logs( WARN_ID_DESC );
			return ST_ERR_ID_INVALIDO;
	}

	return funcion[ubx->id]( &sentencia[PAYLOAD_POS], ubx);
}


/**
* @brief Cargar en una estructura los datos de  UBX_NAV_PVT a partir de un arreglo de bytes
* @param payload: arreglo del que se lee el payload
* @param ubx: puntero a estructura ubx
* @return status_t : el estado en el que termina la funcion (si fue todo bien ST_OK)
*/
status_t proc_nav_pvt(const uchar * payload, ubx_t * ubx){
	if(!payload || !ubx){
		return ST_ERR_PUNT_NULL;
	}

	/*carga el estado del fix*/
	ubx->type.pvt.gns_fix_ok = (payload[UBX_PVT_GNS_FIX_OK_POS] & UBX_PVT_GNS_FIX_OK_MASK)>>UBX_PVT_GNS_FIX_OK_SHIFT;

	/*carga el posicionamiento*/
	ubx->type.pvt.latitud =  UBX_INT_SCALE*msletol(payload,UBX_PVT_LATITUD_POS ,UBX_PVT_LATITUD_LEN);
	ubx->type.pvt.longitud = UBX_INT_SCALE*msletol(payload,UBX_PVT_LONGITUD_POS ,UBX_PVT_LONGITUD_LEN);
	ubx->type.pvt.elevacion = msletol(payload, UBX_PVT_ELEVACION_POS, UBX_PVT_ELEVACION_LEN);

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

/*
* @brief Cargar en una estructura los datos de UBX_TIM_TOS a partir de un arreglo de bytes
* @param payload: arreglo del que se lee el payload
* @param ubx: puntero a estructura ubx
* @return status_t : el estado en el que termina la funcion (si fue todo bien ST_OK)
*/
status_t proc_tim_tos(const uchar * payload, ubx_t * ubx){
	if(!payload || !ubx){
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
* @brief Cargar en una estructura los datos de UBX_NAV_POSLLH a partir de un arreglo de bytes
* @param payload: arreglo del que se lee el payload
* @param ubx: puntero a estructura ubx
* @return status_t : el estado en el que termina la funcion (si fue todo bien ST_OK)
*/
status_t proc_nav_posllh(const uchar * payload, ubx_t * ubx){
	if(!payload || !ubx){
		return ST_ERR_PUNT_NULL;
	}

	/*carga el posicionamiento*/
	ubx->type.posllh.latitud = UBX_INT_SCALE*msletol(payload, UBX_NAV_POSLLH_LATITUD_POS ,UBX_NAV_POSLLH_LATITUD_LEN);
	ubx->type.posllh.longitud = UBX_INT_SCALE*msletol(payload, UBX_NAV_POSLLH_LONGITUD_POS ,UBX_NAV_POSLLH_LONGITUD_LEN);
	ubx->type.posllh.elevacion = msletol(payload, UBX_NAV_POSLLH_ELEVACION_POS, UBX_NAV_POSLLH_ELEVACION_LEN);

	return ST_OK;
}

/**
* @brief busca una sentencia UBX valida y la mueve al principio del buffer (no incluye caracteres de sincronismo)
* @param sentencia: direccion de un puntero a uchar al que se le asignara la direccion de la sentencia ubx
* @param fin: flujo de entrada
* @return status_t: estado en que termino la funcion
*/
/*Si el archivo tiene una sentencia UBX la funcion la carga en el buffer y devuelve un puntero "sentencia" al principio de la misma (no incluye los caracteres de sincronismo). Cuando el archivo se termina y no se encontraron sentencias devuelve eof=true y sentencia=NULL*/
status_t readline_ubx(uchar ** sentencia, bool * eof, FILE * fin){
	static uchar buffer[BUFFER_LEN];
	 static bool buffer_empty = true;

	/*punteros no nulos*/
	if(!sentencia || !eof || !fin){
		return ST_ERR_PUNT_NULL;
	}

	/*carga inicial del buffer*/
	if(buffer_empty){
		size_t leido; /*se declara variables dentro del if porque solo son necesarias la primera vez que se llama a la funcion*/
	 	int i;

		leido = fread_grind(buffer, 1, BUFFER_LEN, fin);

		/*completa el final del buffer con ceros si no hay mas datos para leer del archivo*/
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
		if(checksum(buffer)){
			print_logs( DB_VALID_CHKSUM );
			*sentencia = buffer;
			return ST_OK;
		}else{
			print_logs( ERR_INV_CHKSUM );
		}
	}

	/*si salio del while es porque no hay mas sentencias*/
	*sentencia = NULL;
	*eof=true;
	return ST_OK;
}

/**
* @brief busca una sentencia UBX y la mueve al principio del buffer (no incluye caracteres de sincronismo)
* @param buffer: direccion del buffer
* @param fin: flujo de entrada
* @return bool: true si encontro la sentencia. false si se termino el archivo y no hay mas sentencias para leer en el buffer.
*/
bool get_sentence(uchar * buffer, FILE * fin){
	int i;
	
	print_logs( DB_BYTES_SYNC_SEARCH );
	
	/*busca los dos caracteres de sincronismo en el buffer excepto en los dos ultimos bytes*/
	for(i = 0 ; i < BUFFER_LEN-2 ; i++){
		if(buffer[i] == SYNC_CHAR1){
			if(buffer[i + 1] == SYNC_CHAR2){

				print_logs( DB_BYTES_SYNC_OK );
				/*mueve la sentencia al principio del buffer*/
				load_buffer(buffer, i + 2, fin);
				return true;
			}
		}
	}

	/*si salio del 'for' y se termino el archivo es porque no hay mas sentencias para leer*/
	if( feof(fin) )
		return false;


	/*si salio del 'for' y no se termino el archivo mueve los dos ultimos bytes al principio del buffer y vuelve a empezar*/
	load_buffer(buffer, BUFFER_LEN-2, fin);
	return get_sentence(buffer, fin);
}

/**
* @brief mueve la sentencia al principio del buffer y completa el resto del buffer leyendo del archivo
* @param buffer: direccion del buffer
* @param pos: posicion de la sentencia
* @param fin: flujo de entrada
* @return void
*/
void load_buffer(uchar * buffer, size_t pos, FILE * fin){
	int i;
	size_t leido;

	/*mueve la sentencia al principio del buffer*/
	for(i = 0 ; i < BUFFER_LEN - pos ; i++){
		buffer[i] = buffer[pos + i];
	}


	/*sobreescribe la parte final del buffer*/
	if((leido = fread_grind(buffer + BUFFER_LEN - pos, 1, pos, fin)) != pos){

		/*completa el final del buffer con ceros si no hay mas datos para leer del archivo*/
		if(feof(fin)){
			for(i = BUFFER_LEN - pos + leido ; i < BUFFER_LEN ; i++){
				buffer[i] = 0;
			}
		}
	}

	return;
}

 /**
* @brief lee del archivo y valida los pametros de fread
* @param ptr: puntero a un bloque de memoria con un tamanio minimo de size*nmemb bytes
* @param size: tamanio en bytes de cada elemento a leer
* @param nmemb:	cantidad de elementos a leer
* @param steam: puntero a FILE que especifica un flujo de entrada
* @return size_t: true si el checksum concuerda
*/
size_t fread_grind(void *ptr, size_t size, size_t nmemb, FILE *stream){
	size_t leido;

	if((leido = fread(ptr, size, nmemb, stream)) != nmemb){
			if (ferror(stream)){
				/*IMPRIMIR LOG*/
			}
			if(feof(stream)){
				/*IMPRIMIR LOG*/
			}
	}
	return leido;
}

/**
* @brief calcula el checksum
* @param sentencia: sentencia en la que se va a calcular el  checksum
* @return bool : true si el checksum concuerda
*/
bool checksum(const uchar *sentencia){
	uchar ck_a = 0,
	      ck_b = 0;
	long largo = 0;
	int i;

	/*lee el largo*/
	largo = letol(sentencia, LARGO_POS, LARGO_LEN);

	/*si el largo leido es mayor al espacio disponible en el buffer no se puede realizar la lectura*/
	if(largo > BUFFER_LEN - ID_LEN - LARGO_LEN - CHECKSUM_LEN){
		print_logs( ERR_INV_CHKSUM );
		return false;
	}

	/*Calcula el checksum*/
	for(i = 0 ; i < (PAYLOAD_POS + largo) ; i++){
		ck_a = ck_a + sentencia[i];
		ck_b = ck_b + ck_a;
	}

	/*compara el checksum calculado*/
	return (ck_a == sentencia[i++] && ck_b == sentencia[i])? true : false; /*al finalizar el 'for' anterior la posicion 'i' corresponde al primer caracter de sincronismo*/
}
