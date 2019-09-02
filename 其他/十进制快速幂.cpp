//xi=x(i-1)*a+x(i-2)*b,求xn，n贼大那种
const int K = 2;
ll mod;
struct matrix {
	ll c[K][K];

	matrix operator ^ (const char *s) const {
		matrix res, x = *this, y = x; res.clear();
		for (int i = 0; i < K; i ++) res.c[i][i] = 1;
		int len = strlen(s + 1);
		for (int i = len; i >= 1; i --) {
			for (int j = 1; j < 10; j ++) {
				if (s[i] == '0' + j) res = res * y;
				y = y * x;
			}
			x = y;
		} return res;
	}
}a, b;
char s[N];
int main(){
    scanf("%lld %lld %lld %lld %s %lld", 
    	&a.c[0][0], &a.c[0][1], 
    	&b.c[1][1], &b.c[0][1],
    	s + 1, &mod);
    b.c[1][0] = 1;
    printf("%lld\n",(a * (b ^ s)).c[0][0]);
    return 0;
}