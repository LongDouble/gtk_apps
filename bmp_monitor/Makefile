CC = gcc
CFLAGS = `pkg-config --cflags --libs gtk+-3.0 gmodule-2.0` -lm
OBJECTS = main.o callbacks.o resources.o

bmp_monitor: $(OBJECTS)
	$(CC) -o bmp_monitor $(OBJECTS) $(CFLAGS)

main.o: main.c main.h
	$(CC) -c main.c $(CFLAGS)

callbacks.o: callbacks.c
	$(CC) -c callbacks.c $(CFLAGS)

resources.o: resources.c
	$(CC) -c resources.c $(CFLAGS)

resources.c: bmp_monitor.gresource.xml bmp_monitor.glade
	glib-compile-resources --target=resources.c --generate-source bmp_monitor.gresource.xml

clean:
	-rm -f *.o bmp_monitor resources.c
