/*解决问题:LCT维护图的连通性
 *实例:维护每个时刻当前图是否为二分图
 *解决方法:对于环,去掉最早消失的边即可
 *对于当前存在的所有边，用on=0/1记录是否在树上
 *对于不在树上的边,gg[i]代表第i条边加到树上是否会形成奇环
 *然后cnt记录gg[i]=1的边树即可,cnt=0当前图即为二分图
 */
namespace LCT {
    int fa[N], ch[N][2], rev[N], val[N], sum[N], minv[N];
    //val[i]为每个点消失的时间,sum[i]记录i为根的splay子树多少条边
    //minv[i]记录i为根的子树里,最早消失的是哪条边,边在权上所以边变点
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
        minv[x] = x; sum[x] = (x > n) + sum[ch[x][0]] + sum[ch[x][1]];
        if (ch[x][0] && val[minv[ch[x][0]]] < val[minv[x]]) minv[x] = minv[ch[x][0]];
        if (ch[x][1] && val[minv[ch[x][1]]] < val[minv[x]]) minv[x] = minv[ch[x][1]];
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
        access(y), splay(y);//y存了这条路径的信息
    }
    void link(int x, int y) {
        //printf("link %d %d\n", x, y);
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
    /*
    usage:
        拉取x-y这条链的信息:        split(x, y), printf("%d\n", sum[y]);
        单点修改(单点更新完pushup): splay(x), val[x] = y, pushup(x);
    */
}