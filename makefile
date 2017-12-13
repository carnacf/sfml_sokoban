CC = g++
CFLAGS = -std=c++11 -O2 -g -Wall
SRCS = ./src/*.cpp ./src/generator/*.cpp main.cpp 
PROG = exec

LIBS = -lsfml-graphics -lsfml-window -lsfml-system

$(PROG):$(SRCS)
	$(CC) $(CFLAGS) -o $(PROG) $(SRCS) $(LIBS)