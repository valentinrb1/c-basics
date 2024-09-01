/**
 * @file actividad2.h
 * @author Robledo, Valentín
 * @brief Encabezado del archivo C-arrays.c
 * @version 1.0
 * @date Agosto de 2022
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef __CARRAYS_H__
#define __CARRAYS_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>

char** getWords(char* file_name, u_int32_t* n);
void freeWords(char** words, u_int32_t n);
void upperCasePrintWords(char** words, u_int32_t n);

#endif //__CARRAYS_H__