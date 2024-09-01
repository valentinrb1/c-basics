/**
 * @file actividad3.c
 * @author Robledo, Valentín
 * @brief Resolución del ejercicio de structs del laboratorio 2, Sistemas Operativos I.
 * @version 1.0
 * @date Agosto de 2022
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "actividad3.h"

/**
 * @brief Agrega un nuevo elemento al final de una lista.
 * 
 * @param list puntero a la lista a la cual se le quiere añadir un elemento.
 * @param value valor del nuevo elemento a añadir.
 */
void append(List* list, int value)
{
    NODE* aux = malloc(sizeof(NODE)); // Reservamos memoria para el nuevo elemento

	aux->value = value;
	aux->next = NULL; // Como se agrega al final no tiene un elemento al cual apuntar

    if (*list != NULL) 
    {
        NODE* head = *list;

        while (head->next != NULL) // En caso de que la lista contenga elementos nos movemos al frente de la lista
        {
            head = head->next;
        }

        head->next = aux; // agregamos el nuevo elemento al final
    }
    else
	    *list = aux; // Si la lista esta vacia añadimos el primer elemento creado
}


/**
 * @brief Imprime por consola todos los elementos de una lista.
 * 
 * @param list lista a mostrar por consola.
 */
void printList(List list)
{  
    int i = 0;
    NODE* node = list;
    
    printf("- LINKED LIST:\n");

    while (node != NULL) // Recorremos todos los elementos de la lista
    {
        i++;

		printf("    %d - |%d|\n", i, node->value); // Imprimimos el valor del elemento junto con una numeracion que sirve de guia

		node = node->next; // Avanzamos al elemento anterior elemento
    }

    printf("\n\n");
}