CC = gcc
CFLAGS = -std=c99 -Wall -Werror -pedantic -g
LDFLAGS = -lm
OBJECTS = main.o palabra.o wordle.o colores.o
PROGRAM = wordle

all: $(PROGRAM)

$(PROGRAM): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(PROGRAM) $(LDFLAGS)

palabra.o: palabra.c palabra.h
	$(CC) $(CFLAGS) -c palabra.c

wordle.o: wordle.c wordle.h palabra.h
	$(CC) $(CFLAGS) -c wordle.c

colores.o: colores.c colores.h
	$(CC) $(CFLAGS) -c colores.c

main.o: main.c palabra.h wordle.h
	$(CC) $(CFLAGS) -c main.c

clean:
	rm -vf *.o
