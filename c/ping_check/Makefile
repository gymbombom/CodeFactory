CC = gcc
SRC = $(wildcard *.c)
DEBUG = -g
LIBS = -pthread
APP = ping_check

all: $(SRC)
	$(CC) -o $(APP)  $(SRC) $(DEBUG) $(LIBS)
.SUFFIXES: .c.o
	.c.o:
	$(CC) -c -o $@ $< $(DEBUG) $(LIBS)


clean :
	find ./ -name "*.o" -exec rm -f {} +
	rm -f $(APP)