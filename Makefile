# all: file_reader.o  list.o main.o dictionary.o parser.o
# 	gcc -std=c11 -o main main.o file_reader.o list.o dictionary.o parser.o
# 	make clean
#
#
# distclean: clean
# 	rm main

SRCDIR = ./src
BUILDDIR = ./build/
BIN = ./bin/

BASE = file_reader.o list.o dictionary.o parser.o
STTASKS = Ex1b.s.o Ex1d.s.o Ex1e.s.o
STNAMES = $(basename $(basename $(STTASKS)))
MPTASKS = Ex2a.mp.o Ex2b.mp.o Ex2c.mp.o Ex3a.mp.o Ex3b.mp.o Ex3c.mp.o
MPNAMES = $(basename $(basename $(MPTASKS)))
TASKS = Ex2a Ex2b Ex2c Ex2d Ex3a Ex3b Ex3c

# file_reader.o: file_reader.c
# 	gcc -c file_reader.c
#
# list.o: ./src/list.c
# 	gcc -c ./src/list.c -o ./build/list.o
#
# dictionary.o: dictionary.c
# 	gcc -c dictionary.c
#
# parser.o: parser.c
# 	gcc -c parser.c

first: mkdir $(STTASKS) $(MPTASKS) $(BASE)
	for i in $(STNAMES); do gcc -std=c11 $(addsuffix .s.o, $(addprefix $(BUILDDIR), $$i)) $(addprefix $(BUILDDIR), $(BASE)) -o $(addprefix $(BIN), $$i); done
	for i in $(MPNAMES); do gcc -fopenmp -std=c11 $(addsuffix .mp.o, $(addprefix $(BUILDDIR), $$i)) $(addprefix $(BUILDDIR), $(BASE)) -o $(addprefix $(BIN), $$i); done
#	for i in $(MPNAMES); do clang-omp -fopenmp -std=c11 $(addsuffix .mp.o, $(addprefix $(BUILDDIR), $$i)) $(addprefix $(BUILDDIR), $(BASE)) -o $(addprefix $(BIN), $$i); done

%.o: $(SRCDIR)/%.c
	gcc -c $< -o $(addprefix $(BUILDDIR), $@)

%.s.o: %/main.c
	gcc -c $< -o $(addprefix $(BUILDDIR), $@) -I$(SRCDIR)

%.mp.o: %/main.c
#	clang-omp -c $< -o $(addprefix $(BUILDDIR), $@) -I$(SRCDIR) -fopenmp
	gcc -c $< -o $(addprefix $(BUILDDIR), $@) -I$(SRCDIR) -fopenmp

mkdir:
	mkdir -p $(BUILDDIR)
	mkdir -p $(BIN)

clean:
	rm -f $(addprefix $(BUILDDIR), *)
#	rm -f $(addprefix $(BIN), *)

distclean:
	rm -rf $(BUILDDIR)
	rm -rf $(BIN)
