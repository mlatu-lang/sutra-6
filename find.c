#include <string.h>

#include "sutra-6.c"
#include "brute.c"

I teq(M t,M r,I*o) { P(t->t==CHR, r->t==CHR&&t->c==r->c); P(!o&&t->l!=r->l, 0); I f=0, *no=o?o:&f;
	P(r->t==CAT, teq(t,r->x,no)&&teq(t,r->y,no)); DO(r->l, P(!teq(t->a[o?(*o)++:i],r->a[i],0), 0)); R 1; }
I oflen(I l,S ls,M rs) { PF("length %d:\n",l); I pl=strlen(ls); S s=calloc(1,l+pl+1); strcpy(s,ls); M p,r; A a=nA(); I c, f=0;
	DO(ipow(8,l), prog(i,pl); SRED(pl); if (i&&!(i%100)) (fr(a), a=nA());
		if ((p=ps(s,0,a))&&(r=ex(p,&c,a),c>=0)&&teq(rs,r,0)&&PF("%s |-> ",s)&&pr(r,0)&&puts("")) { f=1; break; });
	fr(a); free(s); R f; }
S help="usage: ./find <before> <after>\nexample: ./find '(B)(A)' 'A'";
I main(I argc,S argv[]) { P(argc!=3,puts(help)); S ls=argv[1]; A a=nA(); M rs=ps(ls,0,a); P(!rs, fr(a), puts("doesn't parse"));
	rs=ps(argv[2],0,a); P(!rs, fr(a), puts("doesn't parse")); DO(11,P(oflen(i,ls,rs), fr(a), 0)); fr(a); }
