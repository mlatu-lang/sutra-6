// helpers for brute forcing programs
S cs="+-<>~,()"; I csl=8;
LL ipow(I b,I p) { LL r=1; DO(p, r*=b); R r; }
I up(I l,S s) { I p=0; DO(l, p+=(s[i]=='(')-(s[i]==')'); P(p<0,i)); R -1; } // skip invalid parens
#define prog(ix,o) LL _j=ix; DO(l, s[l-i-1+o]=cs[_j%csl];_j/=csl); I u=up(l,s+o); if (u>=0) { ix+=ipow(csl,l-u-1)-1; continue; }

S reds[]={
	"+-", // ==
	"+~", // == +
	">-", // == -
	"><", // ==
	"~~", // ==
	",-", // == --
	")-", // ==
	")<", // == unwrapped contents of quote

	"(),", // ==
	"+>~", // == >+<
	"~--", // == --
	">~-", // == ~->
	 0 };
I red(I l,S s) { I z=l; for (S*r=reds; *r; r++) { I n=(strstr(s,*r)-s)+strlen(*r)-1; (n>=0)&&(n<z)&&(z=n); } R z; }
#define SRED(i,o) if ((u=red(l,s+o))<l) { i+=ipow(csl,l-u-1)-1; continue; } // skip redundant combinations
