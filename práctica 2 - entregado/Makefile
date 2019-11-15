#GRUPO 1201
#PAREJA 09

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
	./MergeSort_2 -num_min 1000 -num_max 2000 -incr 100 -numP 200 -fichSalida MergeSort-1000,2000,100,200.log

QuickSort_test:
		@echo Ejecutando QuickSort
		@valgrind --leak-check=full --show-leak-kinds=all \
		./QuickSort_1 -tamanio 20

QuickSort_analysis:
		@echo Ejecutando QuickSort recopilando datos
		@valgrind --leak-check=full --show-leak-kinds=all \
		./QuickSort_2  -num_min 1000 -num_max 2000 -incr 100 -numP 200 -fichSalida QuickSort-1000,2000,100,200-mediaStat.log

##################################
##################################


