CC = gcc
SRC = $(wildcard *.c)
OPTS = -g
DEBUG = -D THPOOL_DEBUG
LIBS = -pthread
APP = ping_check

all: $(SRC)
	$(CC) -o $(APP)  $(SRC) $(OPTS) $(DEBUG) $(LIBS)
.SUFFIXES: .c.o
	.c.o:
	$(CC) -c -o $@ $< $(OPTS) $(DEBUG) $(LIBS)


clean :
	find ./ -name "*.o" -exec rm -f {} +
	rm -f $(APP)