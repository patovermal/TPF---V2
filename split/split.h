/**
* @file split.h
* @author buyi97
* @date 22/11/2019
* @brief Prototipos y includes para split.c
*/

#ifndef NMEA__H
#define NMEA__H

#include <stdlib.h>
#include <string.h>

size_t split_delim(char * cadena, char ** ptr2ptrarray, char delim);

#endif