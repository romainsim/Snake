# Projet Snake : fichier Makefile

but : menu

OFILES = snake.o \
	 menu.o \
	 fin.o

CC = gcc

CFLAGS = -Wall -ansi -pedantic -g

snake.o : snake.h

menu.o : snake.h

fin.o : fin.h

menu : $(OFILES)
	$(CC) $(CFLAGS) -o menu $(OFILES) -lgraph
