#ifndef LIST__H
#define LIST__H

/**
 * @file list.h
 * Modulo de nodo y lista
 *
 * El modulo tiene la estructura List, que contiene un puntero al primer Node, la cantidad actual de nodos, y la cantidad maxima.
 * Node es una estructura con un void* al dato actual y un puntero al siguiente Node.
 *
 * @author buyi97
 * @date 22/11/2019
 */

#include <stdlib.h>
#include <string.h>
#include "status.h"
 
/*Estructura para el nodo*/
typedef struct node{
	void* act;
	struct node* sig;
}Node;

/*Variable LISTA, contiene la cantidad máxima de mensajes guardados, la cantidad actual, y un puntero a la primera posición de la lista*/
typedef struct list{
	size_t cant_max;
	size_t cant_actual;
	Node* ptr;
}List;

/*Prototipos*/
Node* Make_node( void* );
void Destroy_node( Node**, void (*)(void*) );
status_t Make_list(List* , size_t );
status_t AppendL_list( List* , void* );
status_t AppendR_list( List* , void* );
void Destroy_firstnode( List* , void(*)(void*) );
void Destroy_list( List* , void(*)(void*) );
void* PopL_list( List* );
void* PopR_list( List* );


#endif