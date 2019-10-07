/*最小(面积)矩形覆盖,保留六位小数,逆时针输出四个顶点坐标
 *最小周长矩形的做法是相同的
 *单纯用旋转卡壳找凸包上距离最远两个点的话
 *可以找距离某条边最远的点，然后用两个端点到这个点的距离更新答案即可
 */
namespace minRectCover {
	const double eps = 1e-8;
	struct point{
		double x, y;
		point(){}
		point(double x, double y):x(x), y(y){}
		bool operator < (const point &a) const {
			return fabs(y - a.y) < eps ? x < a.x : y < a.y;}
		point operator - (const point &a) const {
			return point(x - a.x, y - a.y);}
		point operator + (const point &a) const {
			return point(x + a.x, y + a.y);}
		point operator / (const double &a) const {
			return point(x / a, y / a);}
		point operator * (const double &a) const {
			return point(x * a, y * a);}
		double operator / (const point &a) const { // .
			return x * a.x + y * a.y;}
		double operator * (const point &a) const { // X
			return x * a.y - y * a.x;}
	}p[N], q[N], rc[4];
	double sqr(double x) {return x * x;}
	double abs(point a) {return sqrt(a / a);}
	int sgn(double x) {return fabs(x) < eps ? 0 : (x < 0 ? -1 : 1);}
	point vertical(point a, point b) {//与ab向量垂直的向量
		return point(a.y - b.y, -a.x + b.x);}
	point vec(point a){return a / abs(a);}
	void convexhull(int n, point *hull, int &top) {//top得到凸包上总点数
		for (int i = 1; i < n; i ++)
			if (p[i] < p[0])
				swap(p[i], p[0]);
		sort (p + 1, p + n, [&](point a, point b){
			double t = (a - p[0]) * (b - p[0]);
			if (fabs(t) < eps) return sgn(abs(p[0] - a) - abs(p[0] - b)) < 0;
			return t > 0;
		});
		int cnt = 0;//去重
		for (int i = 1; i < n; i ++)
			if (sgn(p[i].x - p[cnt].x) != 0 || sgn(p[i].y - p[cnt].y) != 0)
				p[++ cnt] = p[i];
		n = cnt + 1;
		hull[top = 1] = p[0];
		for (int i = 1; i < n; i ++) {
			while (top > 1 && (hull[top] - hull[top - 1]) 
			* (p[i] - hull[top]) < eps) top --;
			hull[++ top] = p[i];
		}
		hull[0] = hull[top];
	}//如果要计算周长需要特判 n==2
	void main() {
		int n;
		scanf("%d", &n);
		for (int i = 0; i < n; i ++)
			scanf("%lf %lf", &p[i].x, &p[i].y);
		convexhull(n, q, n);
		double ans = 1e20;
		int l = 1, r = 1, t = 1;
		double L, R, D, H;
		for (int i = 0; i < n; i ++) {//旋转卡壳
			D = abs(q[i] - q[i + 1]);//以q[i]和q[i+1]所在直线为底边
			while (sgn((q[i + 1] - q[i]) * (q[t + 1] - q[i]) - 
				(q[i + 1] - q[i]) * (q[t] - q[i])) > -1) t = (t + 1) % n;
			while (sgn((q[i + 1] - q[i]) / (q[r + 1] - q[i]) - (q[i + 1] 
				- q[i]) / (q[r] - q[i])) > -1) r = (r + 1) % n;
			if (i == 0) l = r;
			while (sgn((q[i + 1] - q[i]) / (q[l + 1] - q[i]) - (q[i + 1] 
				- q[i]) / (q[l] - q[i])) <  1) l = (l + 1) % n;
			L = fabs((q[i + 1] - q[i]) / (q[l] - q[i]) / D);//直线向左延伸长度
			R = fabs((q[i + 1] - q[i]) / (q[r] - q[i]) / D);//向右延伸长度
			H = fabs((q[i + 1] - q[i]) * (q[t] - q[i]) / D);//t为与底边垂直距离最大的点
			double tmp = (R + L) * H;
			if (tmp < ans) {
				ans = tmp;
				rc[0] = q[i] + (q[i + 1] - q[i]) * (R / D);//右下
				rc[1] = rc[0] + vec(vertical(q[i], q[i + 1])) * H;//右上
				rc[2] = rc[1] - (rc[0] - q[i]) * ((R + L) 
					/ abs(q[i] - rc[0]));//左上
				rc[3] = rc[2] - (rc[1] - rc[0]); 
			}
		}	
		printf("%.6f\n", ans);
		int fir = 0;
		for (int i = 1; i < 4; i ++)
			if (rc[i] < rc[fir])
				fir = i;
		for (int i = 0; i < 4; i ++)
			printf("%.6f %.6f\n", rc[(fir + i) % 4].x, rc[(fir + i) % 4].y);
	}
} 
