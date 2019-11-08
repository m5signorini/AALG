/***********************************************/
/* Programa: ejercicio1     Fecha:03-10-2019   */
/* Autores: César Ramírez & Martín Sánchez     */
/*                                             */
/* Programa que genera numeros aleatorios      */
/* entre dos numeros dados                     */
/*                                             */
/* Entrada: Linea de comandos                  */
/* -limInf: limite inferior                    */
/* -limSup: limite superior                    */
/* -numN: cantidad de numeros                  */
/* Salida: 0: OK, -1: ERR                      */
/***********************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "permutaciones.h"

int main(int argc, char** argv)
{
  int i;
  unsigned int inf, sup, num, j;
  int* frecuencias = NULL;
  int x;
  FILE *pf = NULL;

  srand(time(NULL));

  if (argc != 7) {
    fprintf(stderr, "Error en los parametros de entrada:\n\n");
    fprintf(stderr, "%s -limInf <int> -limSup <int> -numN <int>\n", argv[0]);
    fprintf(stderr, "Donde:\n");
    fprintf(stderr, " -limInf : Limite inferior.\n");
    fprintf(stderr, " -limSup : Limite superior.\n");
    fprintf(stderr, " -numN : Cantidad de numeros a generar.\n");
    exit(-1);
  }
  printf("Practica numero 1, apartado 1\n");
  printf("Realizada por: César Ramírez & Martín Sánchez\n");
  printf("Grupo: 120\n");

  /* comprueba la linea de comandos */
  for(i = 1; i < argc; i++) {
    if (strcmp(argv[i], "-limInf") == 0) {
      inf = atoi(argv[++i]);
    } else if (strcmp(argv[i], "-limSup") == 0) {
      sup = atoi(argv[++i]);
    } else if (strcmp(argv[i], "-numN") == 0) {
      num = atoi(argv[++i]);
    } else {
      fprintf(stderr, "Parametro %s es incorrecto\n", argv[i]);
    }
  }

  /* creamos la tabla para las frecuencias */
  frecuencias = (int*)malloc((sup-inf+1)*sizeof(int));
  if (frecuencias == NULL) {
    fprintf(stderr, "Error de memoria para las frecuencias\n");
    return -1;
  }
  for(j = 0; j < sup-inf+1; j++) {
    frecuencias[j] = 0;
  }

  /* imprimimos los datos */
  for(j = 0; j < num; j++) {
    x = aleat_num(inf, sup);
    frecuencias[x-inf] += 1;
    printf("%d\n", x);
  }

  pf = fopen("frecuencias.log", "w");
  if(pf == NULL) {
    free(frecuencias);
    fprintf(stderr, "No se puede abrir el fichero frecuencias.log\n");
    return -1;
  }

  /* guardamos los datos en el fichero */
  for(j = 0; j<sup-inf+1; j++) {
    fprintf(pf, "%d %d\n", inf+j, frecuencias[j]);
  }

  free(frecuencias);
  fclose(pf);


  return 0;
}
