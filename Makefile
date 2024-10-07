CC = gcc
CFLAGS = -g -Wall -Werror -std=c99

all: csim

csim: cachesim.c cache.c
	$(CC) $(CFLAGS) -o cachesim cachesim.c cache.c -lm 

#
# cleanup
#
clean:
	rm -rf *.o
	rm -rf *.tmp
	rm -f cachesim
	rm -f trace.all trace.f*

