all: main

main: main.o tarefa.o subprocessos.o utilidades.o resultado.h
	gcc -o main main.o tarefa.o subprocessos.o utilidades.o -lpthread -lrt

main.o: main.c
	gcc -c main.c

tarefa.o: tarefa.c
	gcc -c tarefa.c

subprocessos.o: subprocessos.c
	gcc -c subprocessos.c
utilidades.o: utilidades.c
	gcc -c utilidades.c

clean:
	rm -rf *o main
