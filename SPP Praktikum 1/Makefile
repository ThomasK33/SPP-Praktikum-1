all: file_reader.o  list.o main.o 
	gcc -std=c11 -o main main.o file_reader.o list.o
	make clean

clean: file_reader.o  list.o  main  main.o
	rm file_reader.o
	rm list.o
	rm main.o

distclean: clean
	rm main

main.o: main.c
	gcc -c main.c

file_reader.o: file_reader.c
	gcc -c file_reader.c
	
list.o: list.c
	gcc -c list.c
