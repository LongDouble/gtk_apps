CC = gcc
CFLAGS = `pkg-config --cflags --libs gtk+-3.0 gmodule-2.0`
OBJECTS = bmp_monitor.o callbacks.o resources.o

charter: $(OBJECTS)
	$(CC) -o bmp_monitor $(OBJECTS) $(CFLAGS)

bmp_monitor.o: bmp_monitor.c support.h
	$(CC) -c bmp_monitor.c $(CFLAGS)

callbacks.o: callbacks.c support.h
	$(CC) -c callbacks.c $(CFLAGS)

resources.o: resources.c
	$(CC) -c resources.c $(CFLAGS)

resources.c: bmp_monitor.gresource.xml bmp_monitor.glade
	glib-compile-resources --target=resources.c --generate-source bmp_monitor.gresource.xml

clean:
	-rm -f *.o bmp_monitor resources.c
