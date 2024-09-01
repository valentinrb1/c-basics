/**
 * @file Main.c
 * @author Robledo, Valentín
 * @brief Se implementa la resolucion de todos los ejercicios del laboratiorio 2, Sistemas Operativos I.
 * 
 * Para compilar y poder ejecutar el programa se deben compilar de manera conjunta los archivos:
 *  - Main.c
 *  - actividad1.c
 *  - actividad2.c
 *  - actividad3.c
 * 
 * Se puede realizar esta tarea utilizando el comando:
 *  $ gcc Actividad1/actividad1.c Actividad2/actividad2.c Actividad3/actividad3.c Main.c -o <nombre del archivo de salida> -Wall -Werror -pedantic 
 * 
 * @version 1.0
 * @date Agosto de 2022
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "/home/valentinrb/Documentos/SISTEMAS_OPERATIVOS_I/soi---2022---laboratorio-2-valentinrb/Trabajos/Actividad1/actividad1.h"
#include "/home/valentinrb/Documentos/SISTEMAS_OPERATIVOS_I/soi---2022---laboratorio-2-valentinrb/Trabajos/Actividad2/actividad2.h"
#include "/home/valentinrb/Documentos/SISTEMAS_OPERATIVOS_I/soi---2022---laboratorio-2-valentinrb/Trabajos/Actividad3/actividad3.h"

int main(void)
{  
    u_int32_t n;
    List rand_list = NULL; // Creamos una lista vacia
    char** words = getWords("/proc/version", &n); // Obtenemos las palabras del archivo dado

    srand(time(NULL));
    for(int i = 0; i < 20; i++) // Rellenamos la lista con elementos aleatorios
    {
        append(&rand_list, rand());
    } 

    printCpuInfo(); // Mostramos por consola la informacion del CPU
    printMemoryInfo(); // Mostramos por consola la informacion de la memoria

    upperCasePrintWords(words, n); // Mostramos por consola las palabras obtenidas en mayuscula

    printList(rand_list); // Mostramos por consola todos los elementos de la lista generada

    freeWords(words, n); // Liberamos la memoria utilizada para almacenar las palabras

    return 0;
}