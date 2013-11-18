#all: main

#main: main.o matriz.o tarefa.o sequencial.o subprocessos.o threads.o utilidades.o resultado.h
#	gcc -o main main.o matriz.o tarefa.o sequencial.o subprocessos.o threads.o utilidades.o -lpthread -lrt

#main.o: main.c
#	gcc -c main.c


all: main2

main2: main2.o matriz.o tarefa.o sequencial.o subprocessos.o threads.o utilidades.o resultado.h
	gcc -o main2 main2.o matriz.o tarefa.o sequencial.o subprocessos.o threads.o utilidades.o -lm -lpthread -lrt

main2.o: main2.c
	gcc -c main2.c

matriz.o: matriz.c
	gcc -c matriz.c

tarefa.o: tarefa.c
	gcc -c tarefa.c

sequencial.o: sequencial.c
	gcc -c sequencial.c

subprocessos.o: subprocessos.c
	gcc -c subprocessos.c

threads.o: threads.c
	gcc -c threads.c

utilidades.o: utilidades.c
	gcc -c utilidades.c

clean:
	rm -rf *o main
