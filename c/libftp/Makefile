#CC = cc  -g -I ./include -L ./lib  -m32
CC = cc  -g -I ./include -L ./lib

RECO_SRC = $(wildcard *.c)
DEBUG = -Wall
LIBS =  -lftp

all: $(RECO_SRC)
	$(CC) -o libftp  $(RECO_SRC) $(DEBUG) $(LIBS)
.SUFFIXES: .c.o
	.c.o:
	$(CC) -c -o $@ $< $(DEBUG) $(LIBS)


clean :
	find ./ -name "*.o" -exec rm -f {} +
	rm -f libftp
