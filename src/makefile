all: main

main: main.o tarefa.o
	gcc -o main main.o tarefa.o

main.o: main.c
	gcc -c main.c

tarefa.o: tarefa.c
	gcc -c tarefa.c

clean:
	rm -rf *o main
