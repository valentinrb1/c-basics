/**
 * @file actividad3.h
 * @author Robledo, Valentín
 * @brief Encabezado del archivo C-structs.c
 * @version 1.0
 * @date Agosto de 2022
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef __CSTRUCTS_H__
#define __CSTRUCTS_H__

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct NODE
{
	int value;
	struct NODE *next;
} NODE;

typedef NODE* List;

void append(List* list, int value);
void printList(List list);

#endif //__CSTRUCTS_H__