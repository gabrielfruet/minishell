CC = gcc
FLAGS = -Wall -Wextra -Wfloat-equal -Wshadow -Wpointer-arith -Wcast-align -Wconversion
TARGET=./target

all: minishell

run: all
	./minishell

src.o:
	make all -C ./src

OBJ_FILES = $(TARGET)/command.o $(TARGET)/main.o $(TARGET)/redirection.o

minishell: src.o
	$(CC) $(OBJ_FILES) -o minishell


