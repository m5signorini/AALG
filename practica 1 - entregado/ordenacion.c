/**
 *
 * Descripcion: Implementacion de funciones de ordenacion
 *
 * Fichero: ordenacion.c
 * Autor: Carlos Aguirre
 * Version: 1.0
 * Fecha: 16-09-2019
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include "ordenacion.h"

/***************************************************/
/* Funcion: InsertSort    Fecha: 27-09-20          */
/* Autores:César Ramírez & Martín Sánchez          */
/*                                                 */
/* Funcion que ordena una tabla de menor a mayor   */
/* desde el indice ip y que termina en el indice   */
/* iu usando el algoritmo de ordenacion InsertSort */
/*                                                 */
/* Entrada:                                        */
/* tabla: Puntero a la tabla a ordenar             */
/* ip: Numero que indica el primer indice          */
/* iu: Numero que indica el ultimo indice          */
/* Salida:                                         */
/* int: devuelve ERR en caso de error o el         */
/* numero de veces que se ha ejecutado la OB       */
/*                                                 */
/***************************************************/


int InsertSort(int* tabla, int ip, int iu)
{
  if(tabla == NULL || ip < 0 || iu < ip) return ERR;

  int obs = 0;
  /*Numero de elementos ordenados/ proximo indice a ordenar */
  int j = ip+1;
  int i, swap;

  while(j <= iu) {
    /*i: ultimo indice ordenado*/
    i = j-1;
    while((i >= ip) && (++obs) && (tabla[i] > tabla[i+1])) {
      swap = tabla[i+1];
      tabla[i+1] = tabla[i];
      tabla[i] = swap;
      i--;
    }
    j++;
  }

  return obs;
}

/***************************************************/
/* Funcion: InsertSort    Fecha: 27-09-20          */
/* Autores:César Ramírez & Martín Sánchez          */
/*                                                 */
/* Funcion que ordena una tabla de mayor a menor   */
/* desde el indice ip y que termina en el indice   */
/* iu usando el algoritmo de ordenacion InsertSort */
/*                                                 */
/* Entrada:                                        */
/* tabla: Puntero a la tabla a ordenar             */
/* ip: Numero que indica el primer indice          */
/* iu: Numero que indica el ultimo indice          */
/* Salida:                                         */
/* int: devuelve ERR en caso de error o el         */
/* numero de veces que se ha ejecutado la OB       */
/*                                                 */
/***************************************************/
int InsertSortInv(int* tabla, int ip, int iu)
{
  if(tabla == NULL || ip < 0 || iu < ip) return ERR;

  int obs = 0;
  /*Numero de elementos ordenados/ proximo indice a ordenar */
  int j = ip+1;
  int i, swap;

  while(j <= iu) {
    /*i: ultimo indice ordenado*/
    i = j-1;
    while((i >= ip) && (++obs) && (tabla[i] < tabla[i+1])) {
      swap = tabla[i+1];
      tabla[i+1] = tabla[i];
      tabla[i] = swap;
      i--;
    }
    j++;
  }

  return obs;
}
