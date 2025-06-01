#include <string.h>
#include <threads.h>

#include "sutra-6.c"
#include "brute.c"

char req[99]; I reql; V greq(S s) { for (;*s;s++) *s!='('&&*s!=')'&&(*strchrnul(req,*s)=*s); reql=strlen(req); }
I trv(M r,I l,S fnd) { P(r->c, !l&&strchr("+-<>,~",r->c)?1:(fnd[strchrnul(req,r->c)-req]=1,0));
	P(r->x, trv(r->x,1,fnd)||trv(r->y,1,fnd)); DO(r->l, P(trv(r->a[i],1,fnd), 1)); R 0; }
I imp(M r,S fnd) { P(r->l&&r->a[r->l-1]->c, 1); memset(fnd,0,reql); DO(r->l, P(trv(r->a[i],0,fnd), 1));
	DO(reql, P(!fnd[i], 1)); R 0; }
I l, f, pl; S ls; M rs;
I simp(S s,I l,M r,A a,I c,M*pa,M*sa) { char fnd[99];
	while (l&&(!r||c<0||imp(r,fnd))) { s[pl+--l]=0; rc(a); r=ps(s,0,a); r&&(r=exb(r,&c,a,pa,sa)); } R l; }
I teq(M t,M r,I*o) { P(t->c, r->c&&t->c==r->c); P(!o&&t->l!=r->l, 0); I f=0,*no=o?o:&f;
	P(r->x, teq(t,r->x,no)&&teq(t,r->y,no)); DO(r->l, P(!teq(t->a[o?(*o)++:i],r->a[i],0), 0)); R 1; }
#define THREADN 100
I work(V*ag) { LL*se=(LL*)ag; S s=calloc(1,l+pl+1); strcpy(s,ls); M r; A a=nA(); I c; M pa[LIM], sa[LIM];
	for (LL i=*se; i<se[1]; i++) { if (f) break; prog(i,pl); SRED(pl); if (i%1000001==0) puts(s);
		if ((r=ps(s,0,a))&&(r=exb(r,&c,a,pa,sa),c>=0)&&teq(rs,r,0)) { PF("%s |-> ",s); pr(r,0); puts(""); f=1; break; }
		if (r&&(u=simp(s,l,r,a,c,pa,sa))<l) i+=ipow(csl,l-u-1)-1; rc(a); }
	fr(a); free(s); }
LL ses[2*THREADN]; thrd_t t[THREADN];
I oflen(I len) { PF("length %d:\n",l=len); LL tot=ipow(csl,l), sp=tot/THREADN; !sp&&(sp=1);
	DO(THREADN, LL*se=ses+2*i; *se=i*sp; se[1]=(i+1)*sp; (i==THREADN-1||se[1]>tot)&&(se[1]=tot); thrd_create(t+i,work,se));
	DO(THREADN, I b; thrd_join(t[i],&b)); R f; }
S help="usage: ./find <before> <after> <characters>?\n"
	"examples: ./find '(B)(A)' '(B)(B)A'           # full search \n"
	"          ./find '(B)(A)' '(B)(B)A' '+-<>,~'  # search paren-less";
I main(I argc,S argv[]) { P(argc!=3&&argc!=4,puts(help)); argc==4&&(csl=strlen(cs=argv[3]));
	pl=strlen(ls=argv[1]); A a=nA(); rs=ps(ls,0,a); P(!rs, fr(a), puts("doesn't parse"));
	greq(argv[2]); rs=ps(argv[2],0,a); P(!rs, fr(a), puts("doesn't parse")); DO(99, P(oflen(i), fr(a), 0)); fr(a); }
