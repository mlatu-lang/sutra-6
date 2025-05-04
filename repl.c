#include "sutra-6.c"
#include <string.h>

S welc=" bye to exit",
	perr="unbalanced parens",
	err="that one makes your computer explode (if it does halt, try increasing LIM)";
I run(S in) { A a=nA(); M p=ps(in,0,a); P(!p, fr(a), puts(perr)); I l; M s=ex(p,&l,a);
	l==-1?puts(err):(PF("|-> "),pr(s,0),puts(""),PF("%d rewrite%s\n",l,l==1?"":"s")); fr(a); }
I main() { puts(welc); char in[99]; while (1) { fgets(in,99,stdin); in[strlen(in)-1]=0; P(!strcmp(in,"bye"),0); run(in); } }
// (a)(b)>(->)(-)>,>,+,<->,<>,>,+,<->,<
