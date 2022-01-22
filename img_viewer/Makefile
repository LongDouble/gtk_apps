CC = gcc
CFLAGS = `pkg-config --cflags --libs gtk+-3.0 gmodule-2.0`
OBJECTS = img_viewer.o callbacks.o

charter: $(OBJECTS)
	$(CC) -o img_viewer $(OBJECTS) $(CFLAGS)

img_viewer.o: img_viewer.c support.h
	$(CC) -c img_viewer.c $(CFLAGS)

callbacks.o: callbacks.c support.h
	$(CC) -c callbacks.c $(CFLAGS)

clean:
	-rm -f *.o img_viewer
