CC = gcc 
CFLAGS = -Wall -Wpedantic -std=gnu99

all: parse_jvm

parse_jvm: bin/parse_jvm.o bin
	$(CC) -o bin/parse_jvm bin/parse_jvm.o 

bin/parse_jvm.o: src/parse_jvm.c src/types.h bin
	$(CC) $(CFLAGS) -c -o bin/parse_jvm.o src/parse_jvm.c

bin:
	mkdir bin

clean:
	-rm -rf bin