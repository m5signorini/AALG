/**
 *
 * Descripcion: Implementacion de funciones de generacion de permutaciones
 *
 * Fichero: permutaciones.c
 * Autor: Carlos Aguirre
 * Version: 1.0
 * Fecha: 16-09-2017
 *
 */


#include "permutaciones.h"
#include <stdlib.h>
#include <time.h>

#ifndef SWAP
  #define SWAP(X,Y) {int sw = (X); (X) = (Y); (Y) = sw;}
#endif

/***************************************************/
/* Funcion: aleat_num Fecha: 20/9/2019             */
/* Autores: César Ramírez & Martín Sánchez         */
/*                                                 */
/* Rutina que genera un numero aleatorio           */
/* entre dos numeros dados                         */
/*                                                 */
/* Entrada:                                        */
/* int inf: limite inferior                        */
/* int sup: limite superior                        */
/* Salida:                                         */
/* int: numero aleatorio                           */
/***************************************************/
int aleat_num(int inf, int sup)
{
  return(rand()/(RAND_MAX + 1.) * ((sup - inf) + 1) + inf);
}

/***************************************************/
/* Funcion: genera_perm Fecha: 20/9/2019           */
/* Autores: César Ramírez & Martín Sánchez         */
/*                                                 */
/* Rutina que genera una permutacion               */
/* aleatoria                                       */
/*                                                 */
/* Entrada:                                        */
/* int n: Numero de elementos de la                */
/* permutacion                                     */
/* Salida:                                         */
/* int *: puntero a un array de enteros            */
/* que contiene a la permutacion                   */
/* o NULL en caso de error                         */
/***************************************************/
int* genera_perm(int N)
{
  if(N <= 0) return NULL;

  int *perm = NULL;
  int i, a;

  perm = (int*)malloc(N*sizeof(int));
  if(perm == NULL) return NULL;

  for(i = 0; i < N; i++) {
    perm[i] = i+1;
  }

  for(i = 0; i < N; i++) {
    a = aleat_num(i, N-1);
    SWAP(perm[i], perm[a]);
  }

  return perm;
}

/***************************************************/
/* Funcion: genera_permutaciones Fecha: 20/9/2019  */
/* Autores: César Ramírez & Martín Sánchez         */
/*                                                 */
/* Funcion que genera n_perms permutaciones        */
/* aleatorias de tamanio elementos                 */
/*                                                 */
/* Entrada:                                        */
/* int n_perms: Numero de permutaciones            */
/* int N: Numero de elementos de cada              */
/* permutacion                                     */
/* Salida:                                         */
/* int**: Array de punteros a enteros              */
/* que apuntan a cada una de las                   */
/* permutaciones                                   */
/* NULL en caso de error                           */
/***************************************************/
int** genera_permutaciones(int n_perms, int N)
{
  if(n_perms <= 0 || N <= 0) return NULL;

  int** perms = NULL;
  int i;

  perms = (int**)malloc(n_perms*sizeof(int*));
  if(perms == NULL) return NULL;

  for(i = 0; i < n_perms; i++){
    perms[i] = genera_perm(N);
    /* Gestion de Errores*/
    if(perms[i] == NULL) {
      for(i--; i >= 0; i--) {
        free(perms[i]);
      }
      free(perms);
      return NULL;
    }
  }

  return perms;
}
