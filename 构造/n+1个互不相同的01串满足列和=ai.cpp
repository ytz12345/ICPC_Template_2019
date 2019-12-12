/*
给定长度为n的数组a，满足1<=ai<=n
构造n+1个长度为n且互不相同的01串
使第i列的元素和=ai
*/
int n, a[N], b[N], c[N][N];
int main() {
	cin >> n;
	for (int i = 0; i < n; i ++) 
		cin >> a[i], b[i] = i;
	sort (b, b + n, [&](int x, int y){return a[x] > a[y];});
	for (int i = 0; i < n; i ++)
		for (int j = 0; j < a[b[i]]; j ++)
			c[(i + j) %  (n + 1)][b[i]] = 1;
	printf("%d\n", n + 1);
	for (int i = 0; i <= n; i ++, puts(""))
		for (int j = 0; j < n; j ++)
			printf("%d", c[i][j]);
	return 0;
}