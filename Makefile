# all: file_reader.o  list.o main.o dictionary.o parser.o
# 	gcc -std=c11 -o main main.o file_reader.o list.o dictionary.o parser.o
# 	make clean
#
# clean: file_reader.o  list.o  main  main.o
# 	rm file_reader.o
# 	rm list.o
# 	rm main.o
#
# distclean: clean
# 	rm main

file_reader.o: file_reader.c
	gcc -c file_reader.c

list.o: ./SPP\ Praktikum\ 1/list.c
	gcc -c list.c

dictionary.o: dictionary.c
	gcc -c dictionary.c

parser.o: parser.c
	gcc -c parser.c
