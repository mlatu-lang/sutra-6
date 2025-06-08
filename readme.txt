SUTRA-6
=======

compiling: make (repl|bible|find|bb)

repl: a repl

bible: print all combinators up to a certain length
example:
 ./bible 5 > b5
 grep '|(E)(D)(C)((B)A)$' b5  # find cons

find: brute-force the shortest combinator with a certain effect
example:
 ./find '(B)(A)' '((B)A)' | tail -n 1  # find cons

findwasm: build a WASM version of the find program
 host findwasm-src/findwasm.html with an http server to use

bb: brute-force busy beaver programs

the macro LIM in sutra-6.c is very important. it controls how long programs run before sutra-6 kills them, and the amount of stack space they get. increase this if you're brute-forcing busy beavers.

testing: make bible && ./bible 5 > b5 && diff b5 test/b5
