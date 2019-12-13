/**
 *
 * Descripcion: Implementacion funciones para busqueda
 *
 * Fichero: busqueda.c
 * Autor: Carlos Aguirre
 * Version: 1.0
 * Fecha: 11-11-2016
 *
 */

#include "busqueda.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#ifndef SWAP
  #define SWAP(X,Y) {int sw = (X); (X) = (Y); (Y) = sw;}
#endif

/**
 *  Funciones de geracion de claves
 *
 *  Descripcion: Recibe el numero de claves que hay que generar
 *               en el parametro n_claves. Las claves generadas
 *               iran de 1 a max. Las claves se devuelven en
 *               el parametro claves que se debe reservar externamente
 *               a la funcion.
 */

/**
 *  Funcion: generador_claves_uniforme
 *               Esta fucnion genera todas las claves de 1 a max de forma
 *               secuencial. Si n_claves==max entonces se generan cada clave
 *               una unica vez.
 */
void generador_claves_uniforme(int *claves, int n_claves, int max)
{
  int i;

  for(i = 0; i < n_claves; i++) claves[i] = 1 + (i % max);

  return;
}

/**
 *  Funcion: generador_claves_potencial
 *               Esta funcion genera siguiendo una distribucion aproximadamente
 *               potencial. Siendo los valores mas pequenos mucho mas probables
 *               que los mas grandes. El valor 1 tiene una probabilidad del 50%,
 *               el dos del 17%, el tres el 9%, etc.
 */


 /*Solo para Bbin auto*/
void generador_claves_potencial(int *claves, int n_claves, int max)
{
  int i;

  for(i = 0; i < n_claves; i++) {
    claves[i] = .5+max/(1 + max*((double)rand()/(RAND_MAX)));
  }

  return;
}

/***************************************************/
/* Funcion: ini_diccionario    Fecha: 1-12-19      */
/* Autores:César Ramírez & Martín Sánchez          */
/*                                                 */
/* Funcion que inicializa un diccionario de un     */
/* determinado tamanio                             */
/*                                                 */
/* Entrada:                                        */
/* tamanio: Tamanio de la lista de claves del dicc */
/* orden: Si están o no ordenadas las claves       */
/* Salida:                                         */
/* PDICC: Puntero a un nuevo diccionario           */
/*                                                 */
/***************************************************/
PDICC ini_diccionario (int tamanio, char orden)
{
  if(tamanio <= 0 || (orden != ORDENADO && orden != NO_ORDENADO)) {
    return NULL;
  }

	PDICC dicc = NULL;
  int * tabla = NULL;
  dicc = (PDICC)malloc(sizeof(DICC));
  if (dicc == NULL){
    return NULL;
  }

  tabla = (int*)malloc(tamanio*sizeof(int));
  if (tabla == NULL){
    free(dicc);
    return NULL;
  }

  dicc->tabla = tabla;
  dicc->tamanio = tamanio;
  dicc->orden = orden;
  dicc->n_datos = 0;

  return dicc;
}

void libera_diccionario(PDICC pdicc)
{
	if (pdicc == NULL){
    return;
  }

  free(pdicc->tabla);
  free(pdicc);
}

/***************************************************/
/* Funcion: inserta_diccionario    Fecha: 1-12-19  */
/* Autores:César Ramírez & Martín Sánchez          */
/*                                                 */
/* Funcion que inserta clave en un diccionario     */
/*                                                 */
/* Entrada:                                        */
/* pdicc: puntero a diccionario                    */
/* clave: clave a insertar                         */
/* Salida:                                         */
/* int: OK o ERROR en caso de que ocurra un error  */
/*                                                 */
/***************************************************/
int inserta_diccionario(PDICC pdicc, int clave)
{
  int i;
	if (pdicc == NULL || (pdicc->orden != ORDENADO && pdicc->orden != NO_ORDENADO) || pdicc->tamanio < (pdicc->n_datos + 1)){
    return ERR;
  }
  if (pdicc->orden == NO_ORDENADO){
    pdicc->tabla[pdicc->n_datos] = clave;
    pdicc->n_datos++;

    return OK;
  }

  i = pdicc->n_datos - 1;
  while (i >= 0 && pdicc->tabla[i] > clave){
    pdicc->tabla[i+1] = pdicc->tabla[i];
    i--;
  }
  pdicc->tabla[i+1] = clave;
  pdicc->n_datos++;

  return OK;
}

/***********************************************************/
/* Funcion: insercion_masiva_diccionario    Fecha: 1-12-19 */
/* Autores:César Ramírez & Martín Sánchez                  */
/*                                                         */
/* Funcion que inserta muchas claves en un diccionario     */
/*                                                         */
/* Entrada:                                                */
/* pdicc: puntero a diccionario                            */
/* claves: array de claves a insertar                      */
/* n_claves: tamaño del array de claves                    */
/* Salida:                                                 */
/* int: OK o ERROR en caso de que ocurra un error          */
/*                                                         */
/***********************************************************/
int insercion_masiva_diccionario (PDICC pdicc,int *claves, int n_claves)
{
  int i;

  if( pdicc == NULL || claves == NULL || n_claves < 1){
    return ERR;
  }

  for(i = 0; i < n_claves; i++){
    if(inserta_diccionario(pdicc, claves[i]) == ERR){
      return ERR;
    }
  }

  return OK;
}

/***************************************************/
/* Funcion: busca_diccionario    Fecha: 1-12-19    */
/* Autores:César Ramírez & Martín Sánchez          */
/*                                                 */
/* Funcion que busca una clave en un diccionario     */
/*                                                 */
/* Entrada:                                        */
/* pdicc: puntero a diccionario                    */
/* clave: clave a buscar                           */
/* ppos: salida, posicion de la clave              */
/* metodo: metodo de busqueda                      */
/* Salida:                                         */
/* int: Número de OBS                              */
/*                                                 */
/***************************************************/
int busca_diccionario(PDICC pdicc, int clave, int *ppos, pfunc_busqueda metodo)
{
	if (pdicc == NULL || ppos == NULL || metodo == NULL || pdicc->n_datos <= 0){
    return ERR;
  }
  return metodo(pdicc->tabla, 0, pdicc->n_datos-1, clave, ppos); /* ppos porque metodo ya te lo hace *ppos*/
}


/* Funciones de busqueda del TAD Diccionario */
/***************************************************/
/* Funcion: bbin                 Fecha: 1-12-19    */
/* Autores:César Ramírez & Martín Sánchez          */
/*                                                 */
/* Funcion de busqueda binaria                     */
/*                                                 */
/* Entrada:                                        */
/* tabla: lista de claves                          */
/* clave: clave a buscar                           */
/* P: posicion cero de la tabla                    */
/* U: posicion ultima de la tabla                  */
/* ppos: salida, posicion de la clave              */
/* Salida:                                         */
/* int: Número de OBS                              */
/*                                                 */
/***************************************************/
int bbin(int *tabla,int P,int U, int clave, int *ppos)
{
  if (tabla == NULL || U < P || ppos == NULL || clave < 0){
    return ERR;
  }

  int m = 0, obs = 0;

  while (P <= U) {
    obs ++;
    m = (P + U)/2;
    if (tabla[m] == clave){
      *ppos = m;
      return obs;
    }
    else if (clave < tabla[m]){
      U = m - 1;
    }
    else{
      P = m + 1;
    }
  }
    *ppos = NO_ENCONTRADO;
    return obs;
}

/***************************************************/
/* Funcion: blin                 Fecha: 1-12-19    */
/* Autores:César Ramírez & Martín Sánchez          */
/*                                                 */
/* Funcion de busqueda lineal                      */
/*                                                 */
/* Entrada:                                        */
/* tabla: lista de claves                          */
/* clave: clave a buscar                           */
/* P: posicion cero de la tabla                    */
/* U: posicion ultima de la tabla                  */
/* ppos: salida, posicion de la clave              */
/* Salida:                                         */
/* int: Número de OBS                              */
/*                                                 */
/***************************************************/
int blin(int *tabla,int P,int U,int clave,int *ppos)
{
  if (tabla == NULL || U < P || ppos == NULL || clave < 0){
    return ERR;
  }

  int i = P, obs = 0;

  while (i <= U){
    obs ++;
    if(tabla[i] == clave){
      *ppos = i;
      return obs;
    }
    i++;
  }

  *ppos = NO_ENCONTRADO;
  return obs;
}

/*Igual que blin sin auto pero en esta SWAP(tabla[i], tabla[i-1])*/
/***************************************************/
/* Funcion: blin_auto            Fecha: 1-12-19    */
/* Autores:César Ramírez & Martín Sánchez          */
/*                                                 */
/* Funcion de busqueda lineal auto-organizada      */
/*                                                 */
/* Entrada:                                        */
/* tabla: lista de claves                          */
/* clave: clave a buscar                           */
/* P: posicion cero de la tabla                    */
/* U: posicion ultima de la tabla                  */
/* ppos: salida, posicion de la clave              */
/* Salida:                                         */
/* int: Número de OBS                              */
/*                                                 */
/***************************************************/
int blin_auto(int *tabla,int P,int U,int clave,int *ppos)
{
  if (tabla == NULL || U < P || ppos == NULL || clave < 0){
    return ERR;
  }

  int i = P, obs = 0;

  while (i <= U){
    obs ++;
    if(tabla[i] == clave){
      if(i > P){
        SWAP(tabla[i], tabla[i-1]);
        i--;
      }
      *ppos = i;
      return obs;
    }
    i++;
  }

  *ppos = NO_ENCONTRADO;
  return obs;
}
