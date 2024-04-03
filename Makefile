CC = gcc
FLAGS = -Wall -Wextra -Wfloat-equal -Wshadow -Wpointer-arith -Wcast-align -Wconversion

all: minishell.o

run: all
	./minishell

minishell.o: 
	$(CC) ./src/main.c -o minishell $(FLAGS)
