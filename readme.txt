SUTRA-6
=======

compiling: make (repl|bible|find|bb)

repl: a repl
bible: print all combinators up to a certain length
find: brute-force the shortest combinator with a certain effect
bb: brute-force busy beaver programs

the variable LIM in sutra-6.c is very important. it controls how long programs run before sutra-6 kills them, and the amount of stack space they get. increase this if you're brute-forcing busy beavers.

currently, this can only brute-force up to length 10. there are 8^11 > 2^32 combinations of length 11, and that number doesn't fit into an int. fix: use longs, but i haven't gotten around to it yet
