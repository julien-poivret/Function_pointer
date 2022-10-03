CC=gcc
SRC=main.c
BIN=out
FLAGS=-std=c11 -Wall -O3 -mfpu=vfp
$(BIN):$(SRC)
	@($(CC) $(SRC) -o $(BIN) $(FLAGS) && strip $(BIN))
	@(echo "Compilation done.")
