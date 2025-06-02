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
	cd findwasm-src && emcc -sWASM=1 -sEXPORTED_FUNCTIONS=_findt,_malloc,_free -sEXPORTED_RUNTIME_METHODS=ccall -sINVOKE_RUN=0 -sALLOW_MEMORY_GROWTH -sPTHREAD_POOL_SIZE=4 -sPTHREAD_POOL_SIZE_STRICT=0 --pre-js prejs.js ../find.c -pthread -sPROXY_TO_PTHREAD

clean:
	rm repl bible find bb findwasm-src/a.out.js findwasm-src/a.out.wasm
