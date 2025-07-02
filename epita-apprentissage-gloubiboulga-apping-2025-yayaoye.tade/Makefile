CC = cc
CFLAGS = -std=c99 -Wall -Wextra -Werror -pedantic -Wvla

SRC = src/gloubiboulga.c
OBJ = $(SRC:.c=.o)

TARGET = test

.PHONY: all build clean

all: build

build: $(TARGET)

$(TARGET): main.o $(OBJ)
	$(CC) $(CFLAGS) -o $@ main.o $(OBJ)

main.o: main.c src/gloubiboulga.h
	$(CC) $(CFLAGS) -c main.c

src/gloubiboulga.o: src/gloubiboulga.c src/gloubiboulga.h
	$(CC) $(CFLAGS) -c src/gloubiboulga.c -o src/gloubiboulga.o

clean:
	rm -f $(TARGET) *.o src/*.o
