CC = gcc
CFLAGS = `pkg-config --cflags --libs gtk+-3.0 gmodule-2.0`
OBJECTS = charter.o callbacks.o

charter: $(OBJECTS)
	$(CC) -o charter $(OBJECTS) $(CFLAGS)

charter.o: charter.c support.h
	$(CC) -c charter.c $(CFLAGS)

callbacks.o: callbacks.c support.h
	$(CC) -c callbacks.c $(CFLAGS)

clean:
	-rm -f *.o charter
