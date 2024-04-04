CC = gcc
FLAGS = -Wall -Wextra -Wfloat-equal -Wshadow -Wpointer-arith -Wcast-align -Wconversion
TARGET = ../../target

all: command.o redirection.o

command.o: command.c
	$(CC) -c command.c -o $(TARGET)/command.o $(FLAGS)

redirection.o: redirection.c
	$(CC) -c redirection.c -o $(TARGET)/redirection.o $(FLAGS)
