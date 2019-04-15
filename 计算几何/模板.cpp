#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const double eps = 1e-8;

const double pi = acos(-1.0);

struct point {
    double x, y;

    point():x(0), y(0) {}
    point(double x_, double y_):x(x_), y(y_) {}

    point operator + (const point &a) const {return point(x + a.x, y + a.y);}
    point operator - (const point &a) const {return point(x - a.x, y - a.y);}
};

double det(point a, point b) {return a.x * b.y - a.y * b.x;}//叉积
double dot(point a, point b) {return a.x * b.x + a.y * b.y;}//点积
int sgn(double x) {return fabs(x) < eps ? 0 : (x < 0 ? -1 : 1);}

point rotate(point u, double a) {
    return point(u.x * cos(a) - u.y * sin(a), u.y * cos(a) + u.x * sin(a));
}//坐标逆时针旋转a度

point convertPoint(point u, point v, point c) {
     
}

int main() {
    ios::sync_with_stdio(false);
    
    return 0;
}