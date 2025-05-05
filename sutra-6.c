#include <stdio.h>
#include <stdlib.h>

#define R return
#define PF printf
#define P(c,...) if (c) R __VA_ARGS__
#define DO(n,x) do { long long _n=n; for (long long i=0;i<_n;i++) { x; } } while(0)
typedef int I; typedef void V; typedef char*S;

typedef struct a { I u; struct a *n, *a; } *A; // arena - used, next, current arena
#define LIM 1000 // max # of iterations before giving up, also max stack size before giving up
#define AS 4096*8 // arena size
A nA() { A a=calloc(1,AS); a->a=a; a->u=sizeof(struct a); R a; }
V*ma(I l,A m) { A a=m->a; if (l>AS-a->u) a=m->a=a->n=nA(); V*p=(char*)a+a->u; a->u+=l; R p; }
V fr(A a) { while (a) { A n=a->n; free(a); a=n; } }

// mlatu term - type, length. if CHR, c is the character. if ARR, a is the array. if CAT, x/y are the halves.
enum T { CHR,ARR,CAT }; typedef struct m { enum T t; I l; char c; struct m **a, *x, *y; } *M;
M nM(enum T t,A a) { M m=ma(sizeof(struct m),a); m->t=t; R m; } M nMC(char c,A a) { M m=nM(CHR,a); m->c=c; R m; }
I pr(M m,I p) { P(!m, 0); if (m->t==CHR) PF("%c",m->c); // print
	else { p&&PF("("); if (m->t==ARR) DO(m->l, pr(m->a[i],1)); else pr(m->x,0), pr(m->y,0); p&&PF(")"); }; }

S sp(S s) { I p=0; for (;*s;s++) { p+=(*s=='(')-(*s==')'); P(!p, s); } R s; } // skip to closing paren
I len(S s) { I l=0; for (;*s;s++) { P(*s==')', l); l++; P(!*(s=sp(s)), l); } R l; }
M ps(S s,I p,A a); M pq(S s,I p,A a) { M z=ps(s+1,p+1,a); P(!z||!*sp(s), 0); R z; } // parse, parse quote
M ps(S s,I p,A a) { M m=nM(ARR,a); m->l=len(s); m->a=ma(m->l*sizeof(M),a); // returns null on unmatched parens
	DO(m->l, P(*s==')', !p?0:m); P(!(m->a[i]=*s=='('?pq(s,p,a):nMC(*s,a)), 0); P(!*(s=sp(s)), 0); s++); P(!p&&*s, 0); R m; }

#define FIX(ip)   ((ip)+LIM)%LIM
#define TOS       s->a[s->l-1]
#define PUSH(elt) s->a[s->l++]=elt
#define POP       s->a[--s->l]
#define Q(a)      a->t!=CHR
#define Q1        s->l>0&&Q(TOS)
#define Q2        s->l>1&&Q(TOS)&&Q(s->a[s->l-2])
#define PRM(chr,cnd,act) case chr: if (cnd) { (*l)++; act; R 1; } R 0;
I uw(M m,M p,I ip) { P(m->t==CAT, ip=uw(m->x,p,ip), uw(m->y,p,ip)); DO(m->l, p->a[ip]=m->a[i]; ip=FIX(ip+1)); R ip; }
I chr(char c,M s,M p,I*ip,I*l,A a) { switch (c) {
	PRM('+', Q1, PUSH(TOS));
	PRM('-', Q1, POP);
	PRM('>', Q1, M m=nM(ARR,a); m->l=1; m->a=ma(sizeof(M),a); *m->a=TOS; TOS=m);
	PRM('~', Q2, M y=POP; M x=POP; PUSH(y); PUSH(x));
	PRM(',', Q2, M y=POP; M x=TOS; P(!y->l, 1); P(!x->l, TOS=y, 1); M m=nM(CAT,a); m->x=x; m->y=y; m->l=x->l+y->l; TOS=m);
	// catting to an empty quote is the other quote. thus, if a cat has length 0 (and ofc if <0), the length has overflowed
	PRM('<', Q1, M m=POP; P(m->t==CAT&&m->l<=0, p->l+=1+LIM, 1); P(m->l>LIM, 1); *ip=FIX(*ip-m->l); uw(m,p,FIX(*ip+1)); p->l+=m->l);
	default: R 0; } }
I ex1(M s,M p,I*ip,I*l,A a) { P(!p->l,1); M m=p->a[*ip]; if (m->t!=CHR||!chr(m->c,s,p,ip,l,a)) PUSH(m);
	P(p->l+s->l>LIM,*l=-1); p->l--; *ip=FIX(*ip+1); R !p->l; }
M pa[LIM], sa[LIM];
M ex(M p,I*l,A a) { M*oa=p->a; p->a=pa; DO(p->l, p->a[i]=oa[i]); M s=nM(ARR,a); s->a=sa; // l is # of rewrites or -1 if gave up
	I ip=*l=0; while (*l<LIM) P(ex1(s,p,&ip,l,a), s); *l=-1; R s; }
