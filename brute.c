// helpers for brute forcing programs
S cs="()+-<>~,";
long long ipow(I b,I p) { long long r=1; DO(p, r*=b); R r; }
I up(I l,S s) { I p=0; DO(l, p+=(s[i]=='(')-(s[i]==')'); P(p<0,i)); R -1; } // skip invalid parens
#define prog(i,o) long long _j=i; DO(l, s[l-i-1+o]=cs[_j%8];_j/=8); I u=up(l,s+o); if (u>=0) { i+=ipow(8,l-u-1)-1; continue; }

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
	"~--", // == --
	"+>~", // == >+<
	">~-", // == ~->
	 0 };
I red(I l,S s) { I z=l; for (S*r=reds; *r; r++) { I n=(strstr(s,*r)-s)+strlen(*r)-1; (n>=0)&&(n<z)&&(z=n); } R z; }
#define SRED(o) if ((u=red(l,s+o))<l) { i+=ipow(8,l-u-1)-1; continue; } // skip redundant combinations
