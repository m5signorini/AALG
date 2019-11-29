#GRUPO 1201
#PAREJA 09

CC = gcc -ansi -pedantic -g
CFLAGS = -Wall -std=c99
EXE = ejercicio1 ejercicio2

all : $(EXE)

.PHONY : clean
clean :
	rm -f *.o core $(EXE)

$(EXE) : % : %.o ordenacion.o tiempos.o permutaciones.o busqueda.o
	@echo "#---------------------------"
	@echo "# Generando $@ "
	@echo "# Depende de $^"
	@echo "# Ha cambiado $<"
	$(CC) $(CFLAGS) -o $@ $@.o ordenacion.o tiempos.o permutaciones.o busqueda.o

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

busqueda.o : busqueda.c busqueda.h
	@echo "#---------------------------"
	@echo "# Generando $@"
	@echo "# Depende de $^"
	@echo "# Ha cambiado $<"
	$(CC) $(CFLAGS) -c $<


ejercicio1_test:
	@echo Ejecutando Ejercicio 1
	@valgrind --leak-check=full --show-leak-kinds=all \
	./ejercicio1 -tamanio 20 -clave 16

num_min = 1000
num_max = 5000
incr = 500
n_veces = 1000
fs = data/blin_auto_$(num_min)_$(num_max)_$(incr)_$(n_veces)_potencial

ejercicio2_test:
	@echo Ejecutando Ejercicio 2
	@valgrind --leak-check=full --show-leak-kinds=all \
	./ejercicio2 -num_min $(num_min) -num_max $(num_max) -incr $(incr) -n_veces $(n_veces) -fichSalida $(fs).log
##################################
##################################
