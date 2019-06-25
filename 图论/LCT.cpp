const int N = 3e5 + 5;
int n, m;
int fa[N], ch[N][2], rev[N], val[N], sum[N];
int sta[N], top;
bool isroot(int x) {
    return ch[fa[x]][0] != x && ch[fa[x]][1] != x;
}
void reverse(int x) {
    if (!x) return;
    swap(ch[x][0], ch[x][1]);
    rev[x] ^= 1;
}
void pushdown(int x) {
    if (!rev[x]) return;
    reverse(ch[x][0]);
    reverse(ch[x][1]);
    rev[x] = 0;
}
void pushup(int x) {
    sum[x] = sum[ch[x][0]] ^ sum[ch[x][1]] ^ val[x];
}
void rot(int x) {
    int y = fa[x], z = fa[y], d = ch[y][1] == x, c = ch[x][!d];
    fa[x] = z; if (!isroot(y)) ch[z][ch[z][1] == y] = x;
    ch[y][d] = c; if (c) fa[c] = y;
    fa[y] = x, ch[x][!d] = y;
    pushup(y), pushup(x);
}
void splay(int x) {
    int u = x, top = 0, y, z;
    while (!isroot(u)) sta[++ top] = u, u = fa[u];
    sta[++ top] = u;
    while (top) pushdown(sta[top --]);
    while (!isroot(x)) {
        y = fa[x], z = fa[y];
        if (!isroot(y)) {
            if ((ch[z][0] == y) ^ (ch[y][0] == x)) rot(x);
            else rot(y);
        }
        rot(x);
    }
}
void access(int x) {//把x到根的路径拎出来
    for (int y = 0; x != 0; y = x, x = fa[x]) {
        splay(x), ch[x][1] = y, pushup(x);
    }
}
void makeroot(int x) {//令x成为这棵树的根
    access(x), splay(x), reverse(x);
}
int findroot(int x) {//找根
    access(x), splay(x);
    while (ch[x][0]) pushdown(x), x = ch[x][0];
    splay(x);//把根转到顶保证复杂度
    return x;
}
void split(int x, int y) {//拉出x-y的路径
    makeroot(x);
    access(y), splay(y);
    //y存了这条路径的信息
}
void link(int x, int y) {
    makeroot(x);
    if (findroot(y) != x) fa[x] = y;
}
void cut(int x, int y) {
    makeroot(x);
    if (findroot(y) == x && fa[y] == x && ch[x][1] == y) {
        fa[y] = ch[x][1] = 0;
        pushup(x);
    }
}
int main() {
    ios::sync_with_stdio(false);
    cin >> n >> m;
    for (int i = 1; i <= n; i ++)
        cin >> val[i];
    for (int op, x, y; m --; ) {
        cin >> op >> x >> y;
        switch(op) {
            case 0:split(x, y);printf("%d\n", sum[y]);break;
            case 1:link(x, y);break;
            case 2:cut(x, y);break;
            case 3:splay(x);val[x] = y;pushup(x);break;
            //单点更新完记得pushup
        }
    }
}