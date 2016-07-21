FLAGS=-pthread -I/usr/include/glib-2.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include -I/usr/include/libsoup-2.4 -I/usr/include/libxml2  -lsoup-2.4 -lgio-2.0 -lgobject-2.0 -lglib-2.0
http:
	gcc http.c -o http $(FLAGS)
head:
	gcc head.c -o head $(FLAGS)
get:
	gcc get.c -o get $(FLAGS)
post:
	gcc post.c -o post $(FLAGS)
