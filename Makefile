CC=gcc
opt=-O2

.PHONY: all clean

all: repl bible find bb

repl: sutra-6.c repl.c
	$(CC) $(opt) repl.c -o repl

bible: sutra-6.c brute.c bible.c
	$(CC) $(opt) bible.c -o bible

find: sutra-6.c brute.c find.c
	$(CC) $(opt) find.c -o find

bb: sutra-6.c brute.c bb.c
	$(CC) $(opt) bb.c -o bb

clean:
	rm repl bible find bb
