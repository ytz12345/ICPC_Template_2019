struct node {
	double ang; int in;
	bool operator < (const node &a) const {
		 return sgn(ang - a.ang) == 0 ? in > a.in : sgn(ang - a.ang) < 0;}
}a[N * N];
void maxCircleCover(int n, vector<point> &p) {//单位圆覆盖O(n^2logn)
	int ans = 0;
	for (int i = 0; i < n; i ++) {
		int c = 0, cnt = 0;
		for (int j = 0; j < n; j ++) {
			if (abs(p[i] - p[j]) > 2.0) continue;
			double ang1 = atan2(p[j].y - p[i].y, p[j].x - p[i].x);
			double ang2 = acos(abs(p[i] - p[j]) / 2);
			a[c ++] = (node){ang1 - ang2, 1};
			a[c ++] = (node){ang1 + ang2, -1};
		}
		sort (a, a + c);
		for (int j = 0; j < c; j ++)
			cnt += a[j].in, ans = max(ans, cnt);
	}
	printf("%d\n", ans);
}