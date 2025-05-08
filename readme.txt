SUTRA-6
=======

compiling: make (repl|bible|find|bb)

repl: a repl
bible: print all combinators up to a certain length
find: brute-force the shortest combinator with a certain effect
bb: brute-force busy beaver programs

the macro LIM in sutra-6.c is very important. it controls how long programs run before sutra-6 kills them, and the amount of stack space they get. increase this if you're brute-forcing busy beavers.

testing: make bible && ./bible 5 > b5 && diff b5 test/b5
