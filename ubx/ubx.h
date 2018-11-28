#ifndef UBX__H
#define UBX__H
#include "fecha.h"

#define BUFFER_LEN 120 /*La longitúd del buffer debe ser mayor a la máxima longitud posible para una sentencia UBX*/

/*valores fijos de sentencias UBX*/
#define SYNC_CHAR1 			0xB5
#define SYNC_CHAR2 			0X62
#define ID_POS				0
#define ID_LEN 				2
#define POS_LARGO 			2
#define LEN_LARGO 			2 
#define POS_PAYLOAD 		4 

/*identificador de mensaje*/
#define UBX_NAV_PVT_ID 			0x0701 /*little-endian*/
#define UBX_TIM_TOS_ID			0X120d /*little-endian*/
#define UBX_NAV_POSLLH_ID 		0X0201 /*little-endian*/

/*macros para procesar el payload PVT*/
#define UBX_PVT_GNS_FIX_OK_MASK	1
#define UBX_PVT_GNS_FIX_OK_POS	21
#define UBX_PVT_GNS_FIX_OK_SHIFT 0
#define UBX_PVT_ELEVACION_POS	32
#define UBX_PVT_ELEVACION_LEN	4
#define UBX_PVT_LATITUD_POS 	28
#define UBX_PVT_LATITUD_LEN 	4
#define UBX_PVT_LONGITUD_POS 	24
#define UBX_PVT_LONGITUD_LEN 	4
#define UBX_PVT_YEAR_POS 		4
#define UBX_PVT_YEAR_LEN 		2
#define UBX_PVT_MONTH_POS 		6
#define UBX_PVT_MONTH_LEN		1
#define UBX_PVT_DAY_POS 		7
#define UBX_PVT_DAY_LEN			1
#define UBX_PVT_HH_POS 			8
#define UBX_PVT_HH_LEN			1
#define UBX_PVT_MM_POS 			9
#define UBX_PVT_MM_LEN			1
#define UBX_PVT_SS_POS 			10
#define UBX_PVT_SS_LEN			1

/*macros para procesar el payload TIM_TOS*/
#define UBX_TIM_TOS_YEAR_POS 	8
#define UBX_TIM_TOS_YEAR_LEN	2
#define UBX_TIM_TOS_MONTH_POS	10
#define UBX_TIM_TOS_MONTH_LEN	1
#define UBX_TIM_TOS_DAY_POS		11
#define UBX_TIM_TOS_DAY_LEN		1
#define UBX_TIM_TOS_HH_POS		12
#define UBX_TIM_TOS_HH_LEN		1
#define UBX_TIM_TOS_MM_POS		13
#define UBX_TIM_TOS_MM_LEN		1
#define UBX_TIM_TOS_SS_POS		14
#define UBX_TIM_TOS_SS_LEN		1

/*macros para procesar el payload NAV_POSLLH*/
#define UBX_NAV_POSLLH_ELEVACION_POS 	12
#define UBX_NAV_POSLLH_ELEVACION_LEN 	4
#define UBX_NAV_POSLLH_LATITUD_POS		8
#define UBX_NAV_POSLLH_LATITUD_LEN		4
#define UBX_NAV_POSLLH_LONGITUD_POS 	4
#define UBX_NAV_POSLLH_LONGITUD_LEN 	4

#define UBX_CANT_TIPOS 		3

typedef unsigned char uchar; 
typedef unsigned long ulong; 

/*Tipo para el id de las sentencia UBX*/
typedef enum ubx_id{
	NAV_PVT,
	TIM_TOS,
	NAV_POSLLH
}ubx_id;

/*Estructura para nav_pvt, con los datos a guardar*/
typedef struct nav_pvt{
	bool gns_fix_ok;
	fecha_t fecha;
	hora_t hora;
	double latitud;
	double longitud;
	double elevacion;
}nav_pvt_t;

/*Estructura para tim_tos, con los datos a guardar*/
typedef struct tim_tos{
	fecha_t fecha;
	hora_t hora;
}tim_tos_t;

/*Estructura para nav_posllh, con los datos a guardar*/
typedef struct nav_posllh{
	double latitud;
	double longitud;
	double elevacion;
}nav_posllh_t;

typedef struct ubx{
	ubx_id	id;
	union type {
   		nav_pvt_t pvt;
   		nav_posllh_t posllh;
   		tim_tos_t tim_tos;
	}type;  
}ubx_t;

typedef status_t (*proc_ubx_t)(const uchar *, ubx_t *);


status_t proc_nav_posllh(const uchar * payload, ubx_t * pvt);
status_t proc_tim_tos(const uchar * payload, ubx_t * pvt);
status_t proc_nav_pvt(const uchar * payload, ubx_t * pvt);
status_t readline_ubx(uchar ** sentencia, bool * eof, FILE * fin);
bool get_sentence(uchar * buffer, bool * eof, FILE * fin);
void load_buffer(uchar * buffer, size_t pos, bool * eof, FILE * fin);
void fread_grind(void *ptr, size_t size, size_t nmemb, FILE *stream, bool * eof);
bool checksum(const uchar *buffer);



#endif
