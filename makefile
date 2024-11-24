CC = g++

FLAGS = -lSDL2 -lSDL2_image -g

SRCS = \
			main.cpp \
			game.cpp \
			game_object.cpp
	
OUT = ./main

build:
	$(CC) $(SRCS) -o $(OUT) $(FLAGS)

clean:
	rm $(OUT)

all: clean build

run:
	$(OUT)
