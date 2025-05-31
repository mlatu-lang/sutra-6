#include <string.h>

#include "sutra-6.c"
#include "brute.c"

S prelude="(E)(D)(C)(B)(A)";
I comb(M m) { P(m->c, !!strchr("ABCDE",m->c));
	P(!m->l, 0); P(m->x, comb(m->x)&&comb(m->y)); DO(m->l, P(!comb(m->a[i]),0)); R 1; }
I oflen(I l) { I pl=strlen(prelude); S s=calloc(1,l+pl+1); strcpy(s,prelude); M p,r; A a=nA(); I c;
	DO(ipow(8,l), prog(i,pl); (p=ps(s,0,a))&&(r=ex(p,&c,a),c>=0)&&comb(r)&&PF("%s|",s)&&pr(r,0)&&puts(""); rc(a));
	fr(a); free(s); }
I main(I argc,S argv[]){ P(argc==1,puts("usage: ./bible <length>")); DO(1+atoi(argv[1]),oflen(i)); }
