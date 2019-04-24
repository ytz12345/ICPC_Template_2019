#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const double eps = 1e-8;

const double pi = acos(-1.0);

struct point {
    double x, y;

    point():x(0), y(0) {}
    point(double x, double y):x(x), y(y) {}

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
double abs(point a) {return sqrt(sqr(a.x) + sqr(a.y));}//向量长度
point vec(point a){return a / abs(a);}//向量a对应的单位向量
point vec(const line &a) {return a[1] - a[0];}//直线化为向量
double det(point a, point b) {return a.x * b.y - a.y * b.x;}//叉积
double dot(point a, point b) {return a.x * b.x + a.y * b.y;}//点积
int sgn(double x) {return fabs(x) < eps ? 0 : (x < 0 ? -1 : 1);}//判断数字符号

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

int main() {
    ios::sync_with_stdio(false);
    
    return 0;
}