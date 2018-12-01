#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "ubx.h"
#include "bits.h"

bool checksum(const uchar *buffer);

int main (void){
	int i,
		j,
		ok=0,
		fail=0;
	FILE * fout;
	uchar ck_a = 0,
	      ck_b = 0,
	      sentence[100];

	srand(92);
	if(!(fout = fopen("UBXtest.txt", "wb"))
		return EXIT_FAILURE;

	/*primeros caracteres de sentencia PVT*/
	sentence[0] = 0xB5;      
	sentence[1] = 0X62;
	sentence[2] = 0x01; 
	sentence[3] = 0x07;
	sentence[4] = 0x5C; /*largo igual a 92, sentencia PVT*/
	sentence[5] = 0x00; 
	

	for(j = 0 ; j < 4000 ; j++){
		/*carga el payload con bytes aleatorio*/
		for(i = 6 ; i < 98 ; i++){
			sentence[i] = rand()%255;
		}

		/*Calcula el checksum*/
		for(i = 2 ; i < 98 ; i++){
			ck_a = ck_a + sentence[i];
			ck_b = ck_b + ck_a;
		}

		sentence[98]=ck_a;
		sentence[99]=ck_b;
		ck_a = 0;
		ck_b = 0;

		fwrite(sentence,1,100,fout);
		
		if(checksum(sentence + 2))
			ok++;
		else 
			fail++;
		
	}

	printf("checksum OK: %d \nchecksum fail: %d\n", ok, fail);


	fclose(fout);

	return EXIT_SUCCESS;
}

