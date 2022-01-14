CC=gcc
CFLAGS=`pkg-config --cflags --libs gtk+-3.0`
PROG=hello

$(PROG): $(PROG).o
	$(CC) -o $(PROG) $(PROG).o $(CFLAGS)

clean:
	-rm -rf $(PROG) *.o
