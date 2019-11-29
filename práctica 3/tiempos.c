/**
 *
 * Descripcion: Implementacion de funciones de tiempo
 *
 * Fichero: tiempos.c
 * Autor: Carlos Aguirre Maeso
 * Version: 1.0
 * Fecha: 16-09-2017
 *
 */

#include <limits.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include "tiempos.h"
#include "ordenacion.h"
#include "permutaciones.h"

/***************************************************/
/* Funcion: tiempo_medio_ordenacion Fecha:12-10-19          */
/*                                                          */
/* Autores:César Ramírez & Martín Sánchez                   */
/*                                                          */
/* Funcion que ordena una tabla de menor a mayor            */
/* desde el indice ip y que termina en el indice            */
/* iu usando el algoritmo de ordenacion InsertSort          */
/* n_perms: numero de permutaciones a generar y ordenar     */
/* N: tamano de cada tabla a ordenar                        */
/* ptiempo: puntero a TIEMPO para guardar los resultados    */
/* Salida:                                                  */
/* short: ERR en caso de error o OK en caso de exito        */
/***************************************************/
short tiempo_medio_ordenacion(pfunc_ordena metodo,
                              int n_perms,
                              int N,
                              PTIEMPO ptiempo)
{
  if(metodo == NULL || ptiempo == NULL || n_perms <= 0 || N <= 0) return ERR;

  int **tablas = NULL;
  clock_t t1;
  clock_t t2;
  int j = 0;
  int obs_total = 0;
  int obs_min = INT_MAX;
  int obs_max = -1;
  int obs = 0;

  ptiempo->N = N;
  ptiempo->n_elems = n_perms;

  /* Generamos las n_perms tablas de tamaño N a ordenar*/
  tablas = genera_permutaciones(n_perms, N);
  if(tablas == NULL) return ERR;

  /* Calculamos el tiempo necesario para ordenar las tablas como la diferencia */
  /* entre t1 y t2 */

  t1 = clock();
  if(t1 == ERR) {
    for(j=0; j<n_perms; j++) {
      free(tablas[j]);
    }
    free(tablas);
    return ERR;
  }

  for(j=0; j<n_perms; j++) {
    obs = metodo(tablas[j], 0, N-1);
    if(obs == ERR) {
      for(j=0; j<n_perms; j++) {
        free(tablas[j]);
      }
      free(tablas);
    }
    if(obs < obs_min) {
      obs_min = obs;
    }
    else if(obs > obs_max) {
      obs_max = obs;
    }
    obs_total += obs;
  }

  t2 = clock();
  if(t2 == ERR) {
    for(j=0; j<n_perms; j++) {
      free(tablas[j]);
    }
    free(tablas);
    return ERR;
  }

  ptiempo->tiempo = (double)(t2 - t1)/n_perms;
  ptiempo->medio_ob = ((double)obs_total)/n_perms;
  ptiempo->min_ob = obs_min;
  ptiempo->max_ob = obs_max;

  for(j=0; j<n_perms; j++) {
    free(tablas[j]);
  }
  free(tablas);

  return OK;
}

/***************************************************/
/* Funcion: genera_tiempos_ordenacion Fecha:12-10-19        */
/*                                                          */
/* Autores:César Ramírez & Martín Sánchez                   */
/*                                                          */
/* Funcion que genera una lista de tiempos en los que       */
/* se guarda la informacion obtenida de tiempo_medio_ord    */
/* La lista va generando tiempos para permutaciones de      */
/* tamanos que van cambiando entre num_min y num_max        */
/*                                                          */
/* metodo: funcion que se usara pra ordenar                 */
/* fichero: fichero en el que se guardarán los resultados   */
/* num_min: tamano minimo de las permutaciones a ordenar    */
/* num_max: tamano maximo de las permutaciones a ordenar    */
/* incr: incremento en el tamano de las permutaciones       */
/* n_perms: numero de permutaciones por tamano para testear */
/* Salida:                                                  */
/* short: ERR en caso de error o OK en caso de exito        */
/***************************************************/
short genera_tiempos_ordenacion(pfunc_ordena metodo, char* fichero,
                                int num_min, int num_max,
                                int incr, int n_perms)
{
  if(metodo == NULL || fichero == NULL || num_min < 1 || num_max < num_min ||
    incr < 1 || n_perms < 1) return ERR;

  /* Vamos a ir calculando los tiempos que se tarda en ordenar n_perms    */
  /* permutaciones de tablas de N elementos, yendo N desde num_min hasta  */
  /* num_max de incr en incr. Luego necesitamos un array cuyo tamaño      */
  /* sera (num_max - num_min)/incr  + 1                                   */

  int size = (num_max - num_min)/incr + 1;  /* Numero de tiempos a medir*/
  int j = 0;
  int N = num_min;
  PTIEMPO tiempos = NULL;

  tiempos = (PTIEMPO)malloc(size*sizeof(TIEMPO));
  if (tiempos == NULL) return ERR;

  for(j=0; j<size; j++) {
    /* Guardamos en tiempos[j] el tiempo medio para ordenar n_perms de tam N */
    if(tiempo_medio_ordenacion(metodo, n_perms, N, &tiempos[j]) == ERR) {
      free(tiempos);
      return ERR;
    }
    N+=incr;
  }

  if(guarda_tabla_tiempos(fichero, tiempos, size)==ERR) {
    free(tiempos);
    return ERR;
  }

  free(tiempos);
  return OK;
}

/***************************************************/
/* Funcion: guarda_tabla_tiempos Fecha:12-10-19             */
/*                                                          */
/* Autores:César Ramírez & Martín Sánchez                   */
/*                                                          */
/* Funcion que guarda en un fichero los datos obtenidos     */
/* tras realizar la funcion genera_tiempos_ordenacion       */
/*                                                          */
/* fichero: fichero en el que se guardarán los resultados   */
/* tiempo: puntero a la lista de tiempos para guardar       */
/* n_tiempos: tamano de la lista de tiempos                 */
/* Salida:                                                  */
/* short: ERR en caso de error o OK en caso de exito        */
short guarda_tabla_tiempos(char* fichero, PTIEMPO tiempo, int n_tiempos)
{
  if(fichero==NULL || tiempo == NULL || n_tiempos < 1) return ERR;

  int i = 0;
  FILE* pf = NULL;
  TIEMPO t;

  pf = fopen(fichero, "w");
  if(pf == NULL) return ERR;

  for(i=0; i<n_tiempos; i++) {
    t = tiempo[i];
    if(fprintf(pf, "%d %lf %lf %d %d\n", t.N, t.tiempo, t.medio_ob, t.min_ob, t.max_ob)<0) {
      fclose(pf);
      return ERR;
    }
  }

  fclose(pf);

  return OK;
}

short tiempo_medio_busqueda(pfunc_busqueda metodo, pfunc_generador_claves generador,
                              int orden,
                              int N,
                              int n_veces,
                              PTIEMPO ptiempo){
  if(metodo == NULL || generador == NULL  || (orden != NO_ORDENADO && orden != ORDENADO) || n_veces < 1 || ptiempo == NULL || N < 1){
    return ERR;
  }

  clock_t t1;
  clock_t t2;
  int * perm = NULL;
  int pos = 0;
  PDICC pdicc = NULL;
  int* claves = NULL;
  int j = 0;
  int obs_total = 0;
  int obs_min = INT_MAX;
  int obs_max = -1;
  int obs = 0;
  int n_claves = N*n_veces;

  ptiempo->N = N;
  ptiempo->n_elems = n_claves;

  pdicc = ini_diccionario(N, orden);
  if (pdicc == NULL){
    return ERR;
  }

  perm = genera_perm(N);
  if (perm == NULL){
    libera_diccionario(pdicc);
    return ERR;
  }
  if (insercion_masiva_diccionario(pdicc,perm, N) == ERR){
    libera_diccionario(pdicc);
    free(perm);
    return ERR;
  }

  free(perm);

  claves = (int*)malloc(n_claves*sizeof(int));
  if(claves == NULL){
    libera_diccionario(pdicc);
    return ERR;
  }

  generador(claves, n_claves, N);

  t1=clock();
  if(t1 == ERR) {
    libera_diccionario(pdicc);
    free(claves);
    return ERR;
  }

  for(j = 0; j < n_claves; j++){
    obs = busca_diccionario(pdicc, claves[j], &pos , metodo);
    if(obs == ERR){
      libera_diccionario(pdicc);
      free(claves);
      return ERR;
    }

    if(obs < obs_min) {
      obs_min = obs;
    }
    else if(obs > obs_max) {
      obs_max = obs;
    }
    obs_total += obs;
  }

 t2=clock();
 if(t2 == ERR) {
   libera_diccionario(pdicc);
   free(claves);
   return ERR;
 }

 ptiempo->tiempo = (double)(t2 - t1)/n_claves;
 ptiempo->medio_ob = ((double)obs_total)/n_claves;
 ptiempo->min_ob = obs_min;
 ptiempo->max_ob = obs_max;

 libera_diccionario(pdicc);
 free(claves);

 return OK;

}

short genera_tiempos_busqueda(pfunc_busqueda metodo, pfunc_generador_claves generador,
                                int orden, char* fichero,
                                int num_min, int num_max,
                                int incr, int n_veces){
  if(metodo == NULL || generador == NULL  || (orden != NO_ORDENADO && orden != ORDENADO) || n_veces < 1 || fichero == NULL || num_min < 0 || num_max < num_min || incr < 1){
    return ERR;
  }
  int size = (num_max - num_min)/incr + 1;  /* Numero de tiempos a medir*/
  int j = 0;
  int N = num_min;
  PTIEMPO tiempos = NULL;

  tiempos = (PTIEMPO)malloc(size*sizeof(TIEMPO));
  if (tiempos == NULL) return ERR;

  for(j=0; j<size; j++) {
  /* Guardamos en tiempos[j] el tiempo medio para ordenar n_perms de tam N */
    if(tiempo_medio_busqueda(metodo, generador, orden, N ,n_veces, &tiempos[j]) == ERR) {
      free(tiempos);
      return ERR;
    }
    N += incr;
  }

  if(guarda_tabla_tiempos(fichero, tiempos, size)==ERR) {
    free(tiempos);
    return ERR;
  }

  free(tiempos);
  return OK;
}
