CC = cc  -g -I ./include -L ./lib  -m32

RECO_SRC = $(wildcard *.c)
DEBUG = -Wall
LIBS = -lm -lpthread -lhdfs -ljvm

all: $(RECO_SRC)
	$(CC) -o hdfstest  $(RECO_SRC) $(DEBUG) $(LIBS)
.SUFFIXES: .c.o
	.c.o:
	$(CC) -c -o $@ $< $(DEBUG) $(LIBS)


clean :
	find ./ -name "*.o" -exec rm -f {} +
	rm -f hdfstest

