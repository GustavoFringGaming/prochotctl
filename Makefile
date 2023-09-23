# Makefile

CC=gcc
CFLAGS=-Wall

prochotctl:
	$(CC) src/main.c -o prochotctl $(CFLAGS)

clean:
	rm prochotctl

install: prochotctl
	cp prochotctl /usr/bin