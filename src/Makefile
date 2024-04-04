CC=gcc
FLAGS=-Wall -Wextra -Wfloat-equal -Wshadow -Wpointer-arith -Wcast-align -Wconversion
TARGET=../target

all: command.o main.o redirection.o

main.o: main.c
	$(CC) -c ./main.c  -o $(TARGET)/main.o $(FLAGS)

command.o redirection.o:
	make all -C ./command
