#include <string.h>
#include <threads.h>

#include "sutra-6.c"
#include "brute.c"

S strchrnul(const char *s,int c) { S f=strchr(s,c); R !f?s+strlen(s)+1:f; }
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
#define THREADN 4
LL ses[2*THREADN]; thrd_t t[THREADN]; mtx_t mtx;
#define ST ses[2*i]
#define END ses[2*i+1]
I gwrk(I id) { P(ses[2*id]<ses[2*id+1], 1); mtx_lock(&mtx);
	DO(THREADN, P(END-ST>1000, ses[2*id+1]=END, END=ses[2*id]=ST+(END-ST)/2, mtx_unlock(&mtx), 1)); mtx_unlock(&mtx); R 0; }
I work(V*ag) { LL*se=(LL*)ag; S s=calloc(1,l+pl+1); strcpy(s,ls); M r; A a=nA(); I c, id=(se-ses)/2; M pa[LIM], sa[LIM];
	while (gwrk(id)) { PF("(id %d) got [%ld %ld)\n",id,se[0],se[1]); for (; se[0]<se[1]; se[0]++) { if (f) goto dn; prog(se[0],pl); SRED(se[0],pl);
		if ((r=ps(s,0,a))&&(r=exb(r,&c,a,pa,sa),c>=0)&&teq(rs,r,0)) { PF("%s  |->  ",s); pr(r,0); puts(""); f=1; goto dn; }
		if (r&&(u=simp(s,l,r,a,c,pa,sa))<l) se[0]+=ipow(csl,l-u-1)-1; rc(a); } }
	dn: fr(a); free(s); }
I oflen(I len) { PF("length %d:\n",l=len); DO(2*THREADN,ses[i]=0); ses[1]=ipow(csl,l);
	DO(THREADN, thrd_create(t+i,work,ses+2*i)); DO(THREADN, I b; thrd_join(t[i],&b)); R f; }
S help="usage: ./find <before> <after> <characters>?\n"
	"examples: ./find '(B)(A)' '(B)(B)A'           # full search \n"
	"          ./find '(B)(A)' '(B)(B)A' '+-<>,~'  # search paren-less";
I findh(V*as) { S*args=(S*)as; S ls_=*args, rs_=args[1], cs_=args[2]; csl=strlen(cs=cs_); pl=strlen(ls=ls_); A a=nA();
	P(!ps(ls,0,a), fr(a), puts("doesn't parse")); greq(rs_); rs=ps(rs_,0,a); P(!rs, fr(a), puts("doesn't parse"));
	mtx_init(&mtx,mtx_plain); f=0; DO(99, if (oflen(i)) break); mtx_destroy(&mtx); fr(a); R 0; }
I find(S ls_,S rs_,S cs_,I td) { char ls[99], rs[99], cs[99]; strcpy(ls,ls_); strcpy(rs,rs_); strcpy(cs,cs_);
	S a[]={ls,rs,cs}; P(!td, findh(a)); thrd_t t; thrd_create(&t,findh,a); thrd_detach(t); }
I main(I argc,S argv[]) { P(argc!=3&&argc!=4,puts(help)); R find(argv[1],argv[2],argc==4?argv[3]:cs,0); }
