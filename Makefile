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

findwasm: sutra-6.c brute.c find.c
	cd findwasm-src && emcc -O2 -sWASM=1 -sEXPORTED_FUNCTIONS=_find,_malloc,_free -sEXPORTED_RUNTIME_METHODS=ccall --pre-js prejs.js ../find.c -pthread

clean:
	rm repl bible find bb findwasm-src/a.out.js findwasm-src/a.out.wasm
