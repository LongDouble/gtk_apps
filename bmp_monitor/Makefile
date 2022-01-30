CC = gcc
CFLAGS = `pkg-config --cflags --libs gtk+-3.0 gmodule-2.0`
OBJECTS = bmp_monitor.o callbacks.o

charter: $(OBJECTS)
	$(CC) -o bmp_monitor $(OBJECTS) $(CFLAGS)

bmp_monitor.o: bmp_monitor.c support.h
	$(CC) -c bmp_monitor.c $(CFLAGS)

callbacks.o: callbacks.c support.h
	$(CC) -c callbacks.c $(CFLAGS)

clean:
	-rm -f *.o bmp_monitor
