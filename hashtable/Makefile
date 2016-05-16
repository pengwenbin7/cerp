CC = gcc
CFLAGS = `mysql_config --cflags` `pkg-config --cflags glib-2.0 json-glib-1.0`
LIBS = `mysql_config --libs` `pkg-config --libs glib-2.0 json-glib-1.0`

default: main.c
	$(CC) -c main.c $(CFLAGS)

install: main.o
	$(CC) main.o $(LIBS) -o main

clean:
	rm *.o

uninstall:
	rm main
