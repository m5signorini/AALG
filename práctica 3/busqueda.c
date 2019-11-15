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

#include <stdlib.h>
#include <math.h>

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
void generador_claves_potencial(int *claves, int n_claves, int max)
{
  int i;

  for(i = 0; i < n_claves; i++) {
    claves[i] = .5+max/(1 + max*((double)rand()/(RAND_MAX)));
  }

  return;
}

PDICC ini_diccionario (int tamanio, char orden)
{
	if(tamanio <= 0 || (orden != ORDENADO && orden != NO_ORDENADO)) return NULL;

  PDICC dic = NULL;

  dic = (PDICC)malloc(sizeof(DICC));
  if(dic == NULL) return NULL;

  dic->tabla = (int*)malloc(tamanio*sizeof(int));
  if(dic->tabla == NULL) {
    free(dic);
    return NULL;
  }

  dic->n_datos = 0;
  dic->tamanio = tamanio;
  dic->orden = orden;
  return dic;
}

void libera_diccionario(PDICC pdicc)
{
	if(pdicc == NULL) return;
  free(pdicc->tabla);
  free(pdicc);
  return;
}

int inserta_diccionario(PDICC pdicc, int clave)
{
	if(pdicc == NULL || pdicc->tamanio <= pdicc->n_datos) return ERR;

  int i = 0;

  if(pdicc->orden == ORDENADO) {
    i = pdicc->ndatos - 1;
    while(i >= 0 && pdicc->tabla[i] > clave) {
      pdicc->tabla[i+1] = pdicc->tabla[i];
      i--;
    }
    pdicc->tabla[i+1] = clave;
  }
  else {
    pdicc->tabla[pdicc->n_datos] = clave;
  }

  pdicc->ndatos += 1;

  return OK;
}

int insercion_masiva_diccionario (PDICC pdicc, int* claves, int n_claves)
{
  if(pdicc == NULL || claves == NULL || n_claves <= 0) return ERR;
  /* La posibilidad de insertar claves ya se comprueba con inserta_diccionario */

  int i = 0;
  int stat = OK;

  for(i=0; i < n_claves; i++) {
    stat = inserta_diccionario(pdicc, claves[i]);
    if(stat == ERR) return ERR;
  }

  return OK;
}

int busca_diccionario(PDICC pdicc, int clave, int *ppos, pfunc_busqueda metodo)
{
  if(pdicc == NULL || ppos == NULL || metodo == NULL || pdicc->n_datos <= 0) return ERR;
  /* Metodo devuelve el control de errores pertinente */
  return metodo(pdicc->tabla, 0, pdicc->n_datos-1, clave, &ppos);
}


/* Funciones de busqueda del TAD Diccionario */
int bbin(int* tabla, int P, int U, int clave, int *ppos)
{
	if(tabla == NULL || P < 0 || P > U || ppos == NULL) return ERR;

}

int blin(int* tabla, int P, int U, int clave, int *ppos)
{
	if(tabla == NULL || P < 0 || P > U || ppos == NULL) return ERR;

  int obs = 0;
  int i = P;
  while(i <= U) {
    obs++;
    if(tabla[i] == clave) {
      return obs;
    }
    i++;
  }
  return NO_ENCONTRADO;
}

int blin_auto(int* tabla, int P, int U, int clave, int *ppos)
{
	/* vuestro codigo */
}
