CFLAGS = `xml2-config --cflags`
LIBS = `xml2-config --libs`

parse: readfile.c
	gcc readfile.c $(LIBS) $(CFLAGS) -o readfile
