/**
* @file list.c
* @Author buyi97
* @date 22/11/2019
* @brief Funciones para List y Node
*/

#include <stdlib.h>
#include <string.h>
#include "status.h"
#include "list.h"

/**
* @brief Crea un nodo a partir del dato(con memoria dinámica)
* @param Puntero al dato que va a guardar el nodo
* @return Un puntero al nodo creado, NULL si falla
*/

Node* Make_node( void* dato ){
	
	Node* nodo;
	
	if ( !dato )
		return NULL;
	
	if ( !( nodo = (Node*)malloc(sizeof(Node)) ) )
		return NULL;

	nodo->act = dato;
	nodo->sig = NULL;
	
	return nodo;
	
}

/**
* @brief Destruye (libera) un nodo
* @param Puntero a la lista (List*), puntero a la funcion que destruye el dato
* @return Nada(void)
*/

void Destroy_node( Node** nodo, void (*destruir)(void*) ){
	
	if ( !nodo || !destruir || !(*nodo) )
		return;

	(*destruir)((*nodo)->act);
	
	(*nodo)->act = NULL; /*No es necesario*/
	(*nodo)->sig = NULL; /*No es necesario*/
	free(*nodo);
	(*nodo) = NULL;
	
}

/**
* @brief Inicializa una lista (pone el puntero a NULL y la cantidad actual de nodos en 0)
* @param Puntero a la lista (List*), cantidad máxima a setear (size_t)
* @return El estado en el que terminó la función (si fue todo bien ST_OK)
*/

status_t Make_list(List* lista, size_t max){
	
	if ( !lista )
		return ST_ERR_PUNT_NULL;
	
	lista->ptr = NULL;
	lista->cant_max = max;
	lista->cant_actual = 0;
	
	return ST_OK;
	
}

/**
* @brief Agrega un nodo al principio (Append left)
* @param Puntero a la lista (List*), puntero al dato que va a guardar el nodo
* @return El estado en el que terminó la función (si fue todo bien ST_OK)
*/

status_t AppendL_list( List* lista, void* dato ){
	
	Node* nodo;
	
	if ( !lista || !dato )
		return ST_ERR_PUNT_NULL;
	
	if ( lista->cant_actual == lista->cant_max )
		return ST_ERR_LIST_FULL;
	
	nodo = Make_node( dato );
	
	if ( !nodo )
		return ST_ERR_MAKE_NODE;
	
	nodo->sig = lista->ptr;
	lista->ptr = nodo;
	(lista->cant_actual)++;
	
	return ST_OK;
}

/**
* @brief Agrega un nodo al final (Append right)
* @param Puntero a la lista (List*), puntero al dato que va a guardar el nodo
* @return El estado en el que terminó la función (si fue todo bien ST_OK)
*/

status_t AppendR_list( List* lista, void* dato ){
	
	Node* nodo;
	Node* aux;
	
	if ( !lista || !dato )
		return ST_ERR_PUNT_NULL;
	
	if ( lista->cant_actual == lista->cant_max )
		return ST_ERR_LIST_FULL;
	
	nodo = Make_node( dato );
	
	if ( !nodo )
		return ST_ERR_MAKE_NODE;
	
	aux = lista->ptr;
	
	/*Busco el puntero que va a NULL, es decir el último registro de la lista, y le agrego el gpx que me pasan*/
	while ( aux->sig ){ 
		aux = aux->sig;
	}
	
	aux->sig = nodo;
	(lista->cant_actual)++;
	
	return ST_OK;
}

/**
* @brief Destruye (libera) el primer nodo de la lista
* @param Puntero a la lista (List*), puntero a la función que destruye el dato
* @return Nada (void)
*/

void Destroy_firstnode( List* lista, void(*destruir)(void*) ){
	
	Node* aux;
	
	if ( !lista || !destruir || !(lista->ptr) )
		return;
	
	aux = lista->ptr;
	lista->=aux->sig;
	(lista->cant_actual)--;
	
	Destroy_node(&aux, destruir);
	
}

/**
* @brief Destruye (libera) la lista (libera todos los nodos)
* @param Puntero a la lista (List*), puntero a la función que destruye el dato
* @return Nada (void)
*/

void Destroy_list( List* lista , void(*destruir)(void*) ){
	
	Node* siguiente;
	
	if( !lista || !destruir || !(lista->ptr) ){
		lista->cant_actual = 0;
		return;
	}
	
	Destroy_firstnode( lista->ptr , destruir );
	
	return Destroy_list( lista->ptr , destruir );
	
}

/**
* @brief Devuelve el dato contenido en el primer nodo de la lista
* @param Puntero a la lista (List*), puntero a la función que destruye el dato
* @return Nada (void)
*/

void* PopL_list( List* lista ){
	
	if ( !lista || !(lista->ptr) )
		return NULL;
	
	return lista->ptr->act;
	
}

/**
* @brief Devuelve el dato contenido en el primer nodo de la lista
* @param Puntero a la lista (List*), puntero a la función que destruye el dato
* @return Nada (void)
*/

void* PopR_list( List* lista ){
	
	Node* aux;
	
	if ( !lista || !(lista->ptr) )
		return NULL;
	
	aux = lista->ptr;
	
	/*Busco el puntero que va a NULL, es decir el último registro de la lista, y le agrego el gpx que me pasan*/
	while ( aux->sig ){ 
		aux = aux->sig;
	}
	
	return aux->act;
	
}
