CC = gcc
CFLAGS = -Wall -Wextra -std=c99
SRC = src/main.c
OUT = tic_tac_toe

all: $(OUT)

$(OUT): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(OUT)

clean:
	rm -f $(OUT)
