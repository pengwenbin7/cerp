CC = gcc
CFLAGS = `pkg-config --cflags glib-2.0`
LIBS = `pkg-config --libs glib-2.0`

default: main.c
	$(CC) main.c $(CFLAGS) $(LIBS) -o main
compile: main.c
	$(CC) -c main.c $(CFLAGS)

install: main.o
	$(CC) main.o $(LIBS) -o main

clean:
	rm *.o

uninstall:
	rm main
