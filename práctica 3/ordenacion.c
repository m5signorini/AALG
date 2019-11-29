/**
 *
 * Descripcion: Implementacion de funciones de ordenacion
 *
 * Fichero: ordenacion.c
 * Autor: César Ramírez & Martin Sanchez
 * Version: 1.0
 * Fecha: 16-09-2019
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include "ordenacion.h"

#ifndef SWAP
  #define SWAP(X,Y) {int sw = (X); (X) = (Y); (Y) = sw;}
#endif

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

/***************************************************/
/* Funcion: MergeSort    Fecha: 27-09-20          */
/* Autores:César Ramírez & Martín Sánchez          */
/*                                                 */
/* Funcion que ordena una tabla de menor a mayor   */
/* desde el indice ip y que termina en el indice   */
/* iu usando el algoritmo de ordenacion MergeSort  */
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
int MergeSort(int* tabla, int ip, int iu)
{
  if(tabla == NULL || ip < 0 || iu < ip) return ERR;
  if(ip == iu) return 0;

  int imedio = (iu+ip)/2;
  int obs = 0;
  int total = 0;

  /* Comprobaciones de error necesarias pues merge reserva memoria */
  obs = MergeSort(tabla, ip, imedio);
  if(obs == ERR) return ERR;
  total += obs;

  obs = MergeSort(tabla, imedio+1, iu);
  if(obs == ERR) return ERR;
  total += obs;

  obs = merge(tabla, ip, iu, imedio);
  if(obs == ERR) return ERR;
  total += obs;

  return total;
}

/***************************************************/
/* Funcion: merge    Fecha: 27-09-20               */
/* Autores:César Ramírez & Martín Sánchez          */
/*                                                 */
/* Funcion auxiliar de MergeSort cuya función es   */
/* ordenar y combinar las subtablas que MergeSort  */
/* le va pasando de menor a mayor                  */
/*                                                 */
/* Entrada:                                        */
/* tabla: Puntero a la subtabla a ordenar          */
/* ip: Numero que indica el primer indice          */
/* iu: Numero que indica el ultimo indice          */
/* imedio: Numero que indica el indice intermedio  */
/* Salida:                                         */
/* int: devuelve ERR en caso de error o el         */
/* numero de veces que se ha ejecutado la OB       */
/*                                                 */
/***************************************************/
int merge(int* tabla, int ip, int iu, int imedio)
{
  if(tabla == NULL || ip < 0 || iu < ip || imedio < ip || imedio > iu) return ERR;
  if(ip == iu) return 0;

  int* Taux = NULL;
  int i = 0;
  int j = 0;
  int k = 0;
  int obs = 0;

  Taux = (int*)malloc((iu-ip+1)*sizeof(int));
  if(Taux == NULL) {
    return ERR;
  }

  /* Combinacion de las subtablas */
  i = ip;       /* i va de ip a imedio*/
  j = imedio+1; /* j va de imedio+1 a iu*/

  while(i <= imedio && j <= iu) {
    obs++;
    if(tabla[i] < tabla[j]) {
      Taux[k++] = tabla[i++];
    }
    else {
      Taux[k++] = tabla[j++];
    }
  }

  /* Si el indice desbordado es i, volcamos j*/
  for(; j <= iu; j++) {
    Taux[k++] = tabla[j];
  }
  /* Si el indice desbordado es j, volcamos i*/
  for(; i <= imedio; i++) {
    Taux[k++] = tabla[i];
  }

  /* Copiar la Taux en tabla, k = tam de Taux */
  for(i = 0; i < k; i++) {
    tabla[i + ip] = Taux[i];
  }

  free(Taux);
  return obs;
}

/***************************************************/
/* Funcion: QuickSort    Fecha: 27-09-20          */
/* Autores:César Ramírez & Martín Sánchez          */
/*                                                 */
/* Funcion que ordena una tabla de menor a mayor   */
/* desde el indice ip y que termina en el indice   */
/* iu usando el algoritmo de ordenacion QuickSort  */
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
int QuickSort(int* tabla, int ip, int iu) {
  if(tabla == NULL || ip < 0 || iu < ip) return ERR;
  if(ip == iu) return 0;

  int ipiv = 0; /* Index del pivote tras partir */
  int obs = 0;
  int total = 0;

  obs = partir(tabla, ip, iu, &ipiv);
  if(obs == ERR) return ERR;
  total += obs;

  /* Si ip < ipiv - 1 hace falta seguir ordenando la parte izquierda */
  if(ip < ipiv-1) {
    obs = QuickSort(tabla, ip, ipiv-1);
    if(obs == ERR) return ERR;
    total += obs;
  }
  /* Si iu > ipiv + 1 hace falta seguir ordenando la parte derecha */
  if(iu > ipiv+1) {
    obs = QuickSort(tabla, ipiv+1, iu);
    if(obs == ERR) return ERR;
    total += obs;
  }

  return total;
}

/***************************************************/
/* Funcion: partir    Fecha: 27-09-20              */
/* Autores:César Ramírez & Martín Sánchez          */
/*                                                 */
/* Funcion auxiliar de QuickSort cuya función es   */
/* ordenar relativamente los elementos de la tabla */
/* con respecto a un pivote elegido gracias a otra */
/*  función encargada de ello.                     */
/* Entrada:                                        */
/* tabla: Puntero a la tabla a ordenar             */
/* ip: Numero que indica el primer indice          */
/* iu: Numero que indica el ultimo indice          */
/* * pos: indica la posición de la tabla en la que */
/* se encuentra el pivote elegido                  */
/* Salida:                                         */
/* int: devuelve ERR en caso de error o el         */
/* numero de veces que se ha ejecutado la OB       */
/*                                                 */
/***************************************************/
int partir(int* tabla, int ip, int iu, int *pos) {
  if(tabla == NULL || ip < 0 || iu < ip || pos==NULL) return ERR;

  int obs = 0;
  int k = 0;
  int i = 0;

  /* pos es la posicion del pivote */
  obs = medio_stat(tabla, ip, iu, pos);
  if(obs == ERR) return ERR;

  /* ordenar relativamente al pivote pos */
  k = tabla[*pos];
  SWAP(tabla[*pos], tabla[ip]);
  *pos = ip;

  for(i = ip+1; i <= iu; i++) {
    /* pos va representando la posicion final del pivote */
    /* aumenta de 1 en 1 por cada elemento menor (izq) */
    obs++;
    if(tabla[i] < k) {
      *pos += 1;
      SWAP(tabla[i], tabla[*pos]);
    }
  }
  SWAP(tabla[ip], tabla[*pos]);
  return obs;
}

/***************************************************/
/* Funcion: medio    Fecha: 27-09-20              */
/* Autores:César Ramírez & Martín Sánchez          */
/*                                                 */
/* Funcion auxiliar de QuickSort cuya función es   */
/* elegir el pivote en torno al que partir         */
/* ordenará los elementos de la tabla.             */
/* En concreto, esta función elige siempre         */
/* como pivote el primer elemento de la tabla      */
/* Entrada:                                        */
/* tabla: Puntero a la tabla a ordenar             */
/* ip: Numero que indica el primer indice          */
/* iu: Numero que indica el ultimo indice          */
/* * pos: indica la posición de la tabla en la que */
/* se encuentra el pivote elegido                  */
/* Salida:                                         */
/* int: devuelve ERR en caso de error o el         */
/* 0 en caso de éxito                              */
/*                                                 */
/***************************************************/
int medio(int *tabla, int ip, int iu, int *pos) {
  if(tabla == NULL || ip < 0 || iu < ip || pos == NULL) return ERR;
  *pos = ip;
  return 0;
}

/***************************************************/
/* Funcion: medio_avg    Fecha: 27-09-20           */
/* Autores:César Ramírez & Martín Sánchez          */
/*                                                 */
/* Funcion auxiliar de QuickSort cuya función es   */
/* elegir el pivote en torno al que partir         */
/* ordenará los elementos de la tabla.             */
/* En concreto, esta función elige siempre         */
/* como pivote el elemento que se encuentra en     */
/* en la posición intermedia de la tabla.          */
/* Entrada:                                        */
/* tabla: Puntero a la tabla a ordenar             */
/* ip: Numero que indica el primer indice          */
/* iu: Numero que indica el ultimo indice          */
/* * pos: indica la posición de la tabla en la que */
/* se encuentra el pivote elegido                  */
/* Salida:                                         */
/* int: devuelve ERR en caso de error o el         */
/* 0 en caso de éxito                              */
/*                                                 */
/***************************************************/
int medio_avg(int *tabla, int ip, int iu, int *pos) {
  if(tabla == NULL || ip < 0 || iu < ip || pos == NULL) return ERR;
  *pos = (ip + iu)/2;
  return 0;
}

/***************************************************/
/* Funcion: medio_stat    Fecha: 27-09-20          */
/* Autores:César Ramírez & Martín Sánchez          */
/*                                                 */
/* Funcion auxiliar de QuickSort cuya función es   */
/* elegir el pivote en torno al que partir         */
/* ordenará los elementos de la tabla.             */
/* En concreto, esta función compara               */
/* el valor de los elementos que se encuentran     */
/* en la primera, intermedia y última posición     */
/* y elige como pivote el elemento de los tres     */
/* cuyo valor sea el intermedio                    */
/* Entrada:                                        */
/* tabla: Puntero a la tabla a ordenar             */
/* ip: Numero que indica el primer indice          */
/* iu: Numero que indica el ultimo indice          */
/* * pos: indica la posición de la tabla en la que */
/* se encuentra el pivote elegido                  */
/* Salida:                                         */
/* int: devuelve ERR en caso de error o el         */
/* numero de veces que se ha ejecutado la OB       */
/*                                                 */
/***************************************************/
int medio_stat(int *tabla, int ip, int iu, int *pos) {
  if(tabla == NULL || ip < 0 || iu < ip || pos == NULL) return ERR;
  int im = (ip + iu)/2;

  if(tabla[ip] < tabla[iu]) {
    if(tabla[ip] > tabla[im]) {
      *pos = ip;
      return 2;
    }
    if(tabla[im] > tabla[iu]) {
      *pos = iu;
      return 3;
    }
    *pos = im;
    return 3;
  }

  if(tabla[iu] > tabla[im]) {
    *pos = iu;
    return 2;
  }
  if(tabla[im] > tabla[ip]) {
    *pos = ip;
    return 3;
  }

  *pos = im;
  return 3;
}







/**/
