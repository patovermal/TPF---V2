#ifndef BIT_FX__H
#define BIT_FX__H

/*máscaras y shifts*/
#define LOTOF_MASK_SIGNO	0x80000000
#define SHIFT_SIGNO			31
#define SLETOL_MASK_SIGNO	0X80
#define MASK_EXPONENTE 		0x7f800000
#define SHIFT_EXPONENTE		23
#define MASK_MANTISA 		0x007fffff
#define MASK_BIT_IMPLICITO	0x80000000
#define SHIFT_BYTE 			8

ulong letol(const uchar * string, size_t pos, size_t len);
long sletol(const uchar *string, size_t pos, size_t len);
double lotof(ulong entero);

#endif
