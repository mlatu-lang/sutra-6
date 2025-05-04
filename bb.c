// good idea to increase LIM for this one, to be thorough

#include <string.h>

#include "sutra-6.c"
#include "brute.c"

I oflen(I l) { S s=calloc(1,l+1); M p,r; A a=nA(); I c, b=0;
	DO(ipow(8,l), prog(i,0); SRED(0); if (i&&!(i%100)) (fr(a), a=nA());
		(p=ps(s,0,a))&&(r=ex(p,&c,a),c>b)&&PF("%s: %d rewrites\n",s,b=c));
	fr(a); free(s); }
I main(I argc,S argv[]){ P(argc==1,puts("usage: ./bb <length>")); oflen(atoi(argv[1])); }
