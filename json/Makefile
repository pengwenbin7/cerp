CC = gcc
CFLAGS = `pkg-config --cflags glib-2.0 json-glib-1.0`
LIBS = `pkg-config --libs glib-2.0 json-glib-1.0`

default: builder.c
	$(CC) -c builder.c $(CFLAGS)

install: builder.o
	$(CC) builder.o $(LIBS) -o builder

clean:
	rm *.o

uninstall:
	rm builder
