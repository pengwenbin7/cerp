CC = gcc
CFLAGS = `mysql_config --cflags` `pkg-config --cflags glib-2.0 json-glib-1.0`
LIBS = `mysql_config --libs` `pkg-config --libs glib-2.0 json-glib-1.0`

default: base.c
	$(CC) -c base.c $(CFLAGS)

install: base.o
	$(CC) base.o $(LIBS) -o base

clean:
	rm *.o

uninstall:
	rm base
