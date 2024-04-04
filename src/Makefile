CC=gcc
FLAGS=-Wall -Wextra -Wfloat-equal -Wshadow -Wpointer-arith -Wcast-align -Wconversion
TARGET=../target

all: command.o main.o

main.o:
	$(CC) -c ./main.c  -o $(TARGET)/main.o $(FLAGS)

command.o:
	make all -C ./command
