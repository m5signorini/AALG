#-----------------------
# IMPORTANTE: Los valores de los parametros de los ejercicio?_test deben ajustarse.
# Se asume que los ficheros fuente se llaman ejercicio1.c, ejercicio2.c,...,ordenar.h
#-----------------------

CC = gcc -ansi -pedantic -g
CFLAGS = -Wall -std=c99
EXE = MergeSort_1 MergeSort_2 QuickSort_1 QuickSort_2

all : $(EXE)

.PHONY : clean
clean :
	rm -f *.o core $(EXE)

$(EXE) : % : %.o ordenacion.o tiempos.o permutaciones.o
	@echo "#---------------------------"
	@echo "# Generando $@ "
	@echo "# Depende de $^"
	@echo "# Ha cambiado $<"
	$(CC) $(CFLAGS) -o $@ $@.o ordenacion.o tiempos.o permutaciones.o

permutaciones.o : permutaciones.c permutaciones.h
	@echo "#---------------------------"
	@echo "# Generando $@"
	@echo "# Depende de $^"
	@echo "# Ha cambiado $<"
	$(CC) $(CFLAGS) -c $<

ordenacion.o : ordenacion.c ordenacion.h
	@echo "#---------------------------"
	@echo "# Generando $@"
	@echo "# Depende de $^"
	@echo "# Ha cambiado $<"
	$(CC) $(CFLAGS) -c $<

tiempos.o : tiempos.c tiempos.h
	@echo "#---------------------------"
	@echo "# Generando $@"
	@echo "# Depende de $^"
	@echo "# Ha cambiado $<"
	$(CC) $(CFLAGS) -c $<


MergeSort_test:
	@echo Ejecutando MergeSort
	@valgrind --leak-check=full --show-leak-kinds=all \
	./MergeSort_1 -tamanio 20

MergeSort_analysis:
	@echo Ejecutando MergeSort recopilando datos
	@valgrind --leak-check=full --show-leak-kinds=all \
	./MergeSort_2 -num_min 1000 -num_max 10000 -incr 500 -numP 1000 -fichSalida MergeSort-1000,10000,500,1000.log

QuickSort_test:
		@echo Ejecutando QuickSort
		@valgrind --leak-check=full --show-leak-kinds=all \
		./QuickSort_1 -tamanio 20

QuickSort_analysis:
		@echo Ejecutando QuickSort recopilando datos
		@valgrind --leak-check=full --show-leak-kinds=all \
		./QuickSort_2  -num_min 1000 -num_max 2000 -incr 100 -numP 200 -fichSalida QuickSort-1000,2000,100,200.log

##################################
##################################

ejercicio1_test:
	@echo Ejecutando ejercicio1
	@valgrind --leak-check=full --show-leak-kinds=all ./ejercicio1 -limInf 1 -limSup 5 -numN 10
	#valgrind --leak-check=full

ejercicio2_test:
	@echo Ejecutando ejercicio2
	@valgrind --leak-check=full --show-leak-kinds=all ./ejercicio2 -tamanio 5 -numP 5

ejercicio3_test:
	@echo Ejecutando ejercicio3
	@valgrind --leak-check=full --show-leak-kinds=all ./ejercicio3 -tamanio 5 -numP 5

ejercicio4_test:
	@echo Ejecutando ejercicio4
	@valgrind --leak-check=full --show-leak-kinds=all ./ejercicio4 -tamanio 10

ejercicio5_test:
	@echo Ejecutando ejercicio5
	@valgrind --leak-check=full --show-leak-kinds=all ./ejercicio5 -num_min 1 -num_max 100 -incr 1 -numP 2000 -fichSalida ejercicio5.log
