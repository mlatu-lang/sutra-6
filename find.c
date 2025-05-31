#include <string.h>

#include "sutra-6.c"
#include "brute.c"

char req[99], fnd[99]; I reql; V greq(S s) { for (;*s;s++) *s!='('&&*s!=')'&&(*strchrnul(req,*s)=*s); reql=strlen(req); }
I trv(M r,I l) { P(r->c, !l&&strchr("+-<>,~",r->c)?1:(fnd[strchrnul(req,r->c)-req]=1,0));
	P(r->x, trv(r->x,1)||trv(r->y,1)); DO(r->l, P(trv(r->a[i],1), 1)); R 0; }
I imp(M r) { P(r->l&&r->a[r->l-1]->c, 1); memset(fnd,0,reql); DO(r->l, P(trv(r->a[i],0), 1)); DO(reql, P(fnd[i]!=1, 1)); R 0; }
I simp(S s,I pl,I l,M r,A a,I c) { while (l&&(!r||c<0||imp(r))) { s[pl+--l]=0; rc(a); r=ps(s,0,a); r&&(r=ex(r,&c,a)); } R l; }
I teq(M t,M r,I*o) { P(t->c, r->c&&t->c==r->c); P(!o&&t->l!=r->l, 0); I f=0,*no=o?o:&f;
	P(r->x, teq(t,r->x,no)&&teq(t,r->y,no)); DO(r->l, P(!teq(t->a[o?(*o)++:i],r->a[i],0), 0)); R 1; }
I oflen(I l,S ls,M rs) { PF("length %d:\n",l); I pl=strlen(ls); S s=calloc(1,l+pl+1); strcpy(s,ls); M r; A a=nA(); I c, f=0;
	DO(ipow(csl,l), prog(i,pl); SRED(pl); if (i%1000001==0) puts(s);
		if ((r=ps(s,0,a))&&(r=ex(r,&c,a),c>=0)&&teq(rs,r,0)&&PF("%s |-> ",s)&&pr(r,0)&&puts("")) { f=1; break; }
		if (r&&(u=simp(s,pl,l,r,a,c))<l) { i+=ipow(csl,l-u-1)-1; rc(a); continue; }
		rc(a));
	fr(a); free(s); R f; }
S help="usage: ./find <before> <after> <characters>?\n"
	"examples: ./find '(B)(A)' '(B)(B)A'           # full search \n"
	"          ./find '(B)(A)' '(B)(B)A' '+-<>,~'  # search paren-less";
I main(I argc,S argv[]) { P(argc!=3&&argc!=4,puts(help)); argc==4&&(csl=strlen(cs=argv[3]));
	S ls=argv[1]; A a=nA(); M rs=ps(ls,0,a); P(!rs, fr(a), puts("doesn't parse"));
	greq(argv[2]); rs=ps(argv[2],0,a); P(!rs, fr(a), puts("doesn't parse")); DO(99,P(oflen(i,ls,rs), fr(a), 0)); fr(a); }
