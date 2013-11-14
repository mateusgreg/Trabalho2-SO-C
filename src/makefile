all: main

main: main.o tarefa.o subprocessos.o
	gcc -o main main.o tarefa.o subprocessos.o

main.o: main.c
	gcc -c main.c

tarefa.o: tarefa.c
	gcc -c tarefa.c

subprocessos.o: subprocessos.c
	gcc -c subprocessos.c

clean:
	rm -rf *o main
