/*旋转卡壳:
 *1.最小面积矩形覆盖/最小周长矩形覆盖,做法相同
 *2.找凸包上距离最远两个点,可以找距离某条边最远的点，然后用两个端点到这个点的距离更新答案即可

 *圆的反演:
 *OA*OA'=R^2, O为反演中心，R为反演半径，A为原图形的点，A'为反形上的对应点
 *过反演中心的圆的反形是一条不过反演中心的直线，反之亦然
 *不过反演中心的圆反形也为不过反演中心的圆，且反演中心为两个圆的位似中心
 *推论:反演中心不在两圆上，则两圆相对关系不变，在两个圆上就平行线
 *    在一个圆上就一个圆一条线。原来两圆相切就是相切的圆和直线
 */
const double eps = 1e-8;
const double pi = acos(-1.0);
//atan2(y,x)反正切，返回(-pi, pi]
int sgn(double x) {return fabs(x) < eps ? 0 : (x < 0 ? -1 : 1);}//判断数字符号
struct point {
    double x, y;
    point():x(0), y(0) {}
    point(double x, double y):x(x), y(y) {}
    bool operator < (const point &a) const {return sgn(y - a.y) == 0 ? x < a.x : y < a.y;}
    point operator + (const point &a) const {return point(x + a.x, y + a.y);}
    point operator - (const point &a) const {return point(x - a.x, y - a.y);}
    point operator * (const double &a) const {return point(x * a, y * a);}
    point operator / (const double &a) const {return point(x / a, y / a);}
};
struct line:public vector<point> {
	line(){}
	line(point a, point b) {push_back(a), push_back(b);}
};
double sqr(double x) {return x * x;}
point vec(point a){return a / abs(a);}//向量a对应的单位向量
point vec(const line &a) {return a[1] - a[0];}//直线化为向量
double det(point a, point b) {return a.x * b.y - a.y * b.x;}//叉积
double dot(point a, point b) {return a.x * b.x + a.y * b.y;}//点积
double dot(point a) {return dot(a, a);}
double abs(point a) {return sqrt(dot(a));}//向量长度
point vertical(point a) {return point(a.y, -a.x);}//与向量a垂直的向量
point vertical(point a, point b) {return vertical(a - b);}//与ab向量垂直的向量
point rotate(point u, double a) {
    return point(u.x * cos(a) - u.y * sin(a), u.y * cos(a) + u.x * sin(a));
}//坐标逆时针旋转a度
point convertPoint(point u, point v, point c) {
	return point(det(c, v) / det(u, v), det(c, u) / det(v, u));  
}//uv不平行时，存在a*u+b*v=c,返回(a,b)
int cross(point s, point a, point b) {
	point u = a - s, v = b - s; double res = det(u, v);
	if (res > 0) return 1;//在线段左方
	if (res < 0) return -1;//在线段右方
	if (dot(u, v) <= 0) return 0;//在线段上
	if (abs(u) > abs(v)) return 2;//在a到b延长线上
	return -2;//在b到a的延长线上
}//判断点s与线段ab的位置关系
bool isInterSS(const line &u, const line &v) {
	if (sgn(det(vec(u), vec(v))) == 0) return 0;//平行
	if (sgn(cross(u[0], u[1], v[0]) * cross(u[0], u[1], v[1]) <= 0) && 
		sgn(cross(v[0], v[1], u[0]) * cross(v[0], v[1], u[1]) <= 0))
		return 1;//相交
	return 0;
}//判断线段交
point interLL(const line &u, const line &v) {
	double a = det(vec(u), vec(v));
	double b = det(vec(u), u[1] - v[0]);
	if (sgn(a) == 0) return v[0];
	return v[0] + vec(v) * b / a;
}//求直线交点
point crossSP(const line &v, const point &u) {
    return interLL(v, line(u, u + vertical(v[0], v[1])));
}//过ｕ向直线ｖ做垂线返回垂足
struct convexHull {
	vector<point> p; int n;
	convexHull():n(0) {p.clear();}
	convexHull(vector<point> &q):n(0) {
		int m = q.size(), cnt = 0; sort (q.begin(), q.end());
		for (int i = 1; i < m; i ++)
			if (sgn(q[i].x - q[cnt].x) != 0 || sgn(q[i].y - q[cnt].y) != 0)
				q[++ cnt] = q[i];
		q.resize(m = cnt + 1), p.resize(m + 1);
		for (int i = 1; i < m; i ++) if (q[i] < q[0]) swap(q[i], q[0]);
		sort (q.begin() + 1, q.begin() + m, [&](point a, point b){
			double t = det((a - q[0]), (b - q[0]));
			if (sgn(t) == 0) return sgn(abs(q[0] - a) - abs(q[0] - b)) < 0;
			return t > 0;
		});//以p[0]为原点的极角排序
		p[n = 1] = q[0];
		for (int i = 1; i < m; i ++) {
			while (n > 1 && det((p[n] - p[n - 1]), (q[i] - p[n])) < eps) n --;
			p[++ n] = q[i];
		}
		p[0] = p[n], p.resize(n + 1);
	}//得到n个点的凸包,且p[0]=p[n]
	double getArea() const{//如果求周长需要特判n=2
		double res = 0;
		for (int i = 2; i < n; i ++)
			res += abs(det(p[i] - p[0], p[i - 1] - p[0]));
		return res / 2;
	}
	void getRec() const {//最小矩形覆盖
		double ans = 1e20, L, R, D, H;
		int l = 1, r = 1, t = 1;
		point rc[4];
		for (int i = 0; i < n; i ++) {//旋转卡壳
			D = abs(p[i] - p[i + 1]);//以q[i]和q[i+1]所在直线为底边
			while (sgn(det((p[i + 1] - p[i]), (p[t + 1] - p[i])) - 
				det((p[i + 1] - p[i]), (p[t] - p[i]))) > -1) t = (t + 1) % n;
			while (sgn(dot((p[i + 1] - p[i]), (p[r + 1] - p[i])) - dot((p[i + 1] 
				- p[i]), (p[r] - p[i]))) > -1) r = (r + 1) % n;
			if (i == 0) l = r;
			while (sgn(dot((p[i + 1] - p[i]), (p[l + 1] - p[i])) - dot((p[i + 1] 
				- p[i]), (p[l] - p[i]))) <  1) l = (l + 1) % n;
			L = fabs(dot((p[i + 1] - p[i]), (p[l] - p[i])) / D);//直线向左延伸长度
			R = fabs(dot((p[i + 1] - p[i]), (p[r] - p[i])) / D);//向右延伸长度
			H = fabs(det((p[i + 1] - p[i]), (p[t] - p[i])) / D);//t为与底边垂直距离最大的点
			double tmp = (R + L) * H;
			if (tmp < ans) {
				ans = tmp;
				rc[0] = p[i] + (p[i + 1] - p[i]) * (R / D);//右下
				rc[1] = rc[0] + vec(vertical(p[i], p[i + 1])) * H;//右上
				rc[2] = rc[1] - (rc[0] - p[i]) * ((R + L) 
					/ abs(p[i] - rc[0]));//左上
				rc[3] = rc[2] - (rc[1] - rc[0]); 
			}
		}//具体小数点位数看题目要求哦	
		printf("%.5f\n", ans); int fir = 0;
		for (int i = 0; i < 4; i ++) {
			if (rc[i] < rc[fir]) fir = i;
			if (sgn(rc[i].x) == 0) rc[i].x = 0;
			if (sgn(rc[i].y) == 0) rc[i].y = 0;
		}//逆时针输出，且第一个是y坐标最小的点
		for (int i = 0; i < 4; i ++)
			printf("%.5f %.5f\n", rc[(fir + i) % 4].x, rc[(fir + i) % 4].y);
	}
};
bool isInConvexHull(point p, const convexHull &h) {//点是否在凸包内或凸包上
	double s = h.getArea();
	for (int i = 0; i < h.n; i ++)
		s -= abs(det(p - h.p[i + 1], p - h.p[i])) / 2;
	return sgn(s) == 0;
}//要求n>2,线段上就判断叉积为0且坐标在范围里面即可
point getCC(point a, point b, point c) {//三点确定外接圆的圆心,Center of Circle
	point l1 = (a + b) / 2, l2 = (a + c) / 2;
	return interLL(line(l1, l1 + vertical(a, b)), line(l2, l2 + vertical(a, c)));
}
struct circle {
	point o; double r;
	circle():o(), r(0) {}
	circle(point o, double r):o(o), r(r) {}
	circle(double x, double y, double r):o(x, y), r(r) {}
	circle(int n, vector<point> &p):o(), r(0) {//最小圆覆盖O(n)
		random_shuffle(p.begin(), p.end());
		for (int i = 0; i < n; i ++)
			if (dot(p[i] - o, p[i] - o) > r) {
				o = p[i], r = 0;
				for (int j = 0; j < i; j ++)
					if (dot(p[j] - o, p[j] - o) > r) {
						o = (p[i] + p[j]) / 2, r = dot(p[j] - o, p[j] - o);
						for (int k = 0; k < j; k ++)
							if (dot(p[k] - o, p[k] - o) > r)
								o = getCC(p[i], p[j], p[k]), r = dot(p[k] - o, p[k] - o);
					}
			}
		r = sqrt(r);
	}
};
void circleInter(const circle &u, const circle &v, vector<point> &vp) {
    point d = u.c - v.c; double r1 = u.r, r2 = v.r; vp.clear();
    if (sgn(r1 + r2 - abs(d)) >= 0 && sgn(abs(r1 - r2) - abs(d)) <= 0 && sgn(abs(d)) != 0) {
        point mid = d / abs(d) * (dot(d) + r2 * r2 - r1 * r1) / (2 * r2 * abs(d)) * r2 + v.c;
        point p = vec(vertical(d)) * sqrt(sqr(r1) - dot(u.c - mid)); 
        vp.push_back(mid + p);
        if (sgn(r1 + r2 - abs(d)) == 0 || sgn(abs(r1 - r2) - abs(d)) == 0) return;
        vp.push_back(mid - p);
    }
}//求两个圆的交点，并且放到vp里。交点精度不高，大概也就1e-6。eps太小会导致判错。