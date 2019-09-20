/*对于一个dag，假设每个联通块中都只有一个点出度为0
 *那么对于一个联通块，假设这个出度为0的点为s
 *可以处理出这个块中所有点到s的必经点
 *rt为新建的虚根，把所有联通块整合在一棵树里
 */
int fa[N][19];
vector <int> e[N], f[N], E[N];
int du[N], dep[N];
int lca(int x,int y){
    if (dep[x] < dep[y]) swap(x, y);// dep[x] > dep[y]
    for(int j = 18; j >= 0; j --) 
        if (dep[fa[x][j]] >= dep[y])
            x = fa[x][j];
    if(x == y) return x;
    for (int j = 18; j >= 0; j --)
            if (fa[x][j] != fa[y][j])
                x = fa[x][j], y = fa[y][j];
    return fa[x][0];
}
void topo(){
    static int q[N * 2], l, r;l = 1, r = 0;  
    for (int i = 1; i <= n; i ++)
        if (du[i] == 0) {
            q[++ r] = i;
            E[rt].push_back(i);//支配树的边
            fa[i][0] = rt;
            dep[i] = 1;
        }
     while (l <= r) {
         int u = q[l ++];
         for (int v : e[u]) {
             du[v] --;
             if (du[v] == 0) {
                 int las = -1;
                 for (int w : f[v]) {
                     if (las == -1) las = w;
                     else las = lca(las, w);
                 }
                 E[las].push_back(v);
                 fa[v][0] = las;
                 dep[v] = dep[las] + 1;
                 for (int j = 1; j <= 18; j ++) 
                     fa[v][j] = fa[fa[v][j - 1]][j - 1];
                 q[++ r] = v;
             }
         }
     }
}
int main() {
    int cas, q;
    for (scanf("%d", &cas); cas --; ) {
        scanf("%d %d", &n, &m);
        rt = n + 1;
        for (int i = 0; i <= rt; i ++) {
            e[i].clear();f[i].clear();
            E[i].clear();du[i] = dep[i] = 0;
            for (int j = 0; j <= 18; j ++)
                fa[i][j] = 0;
        }
        for (int u, v, i = 1; i <= m; i ++) {
            scanf("%d %d", &u, &v);
            e[v].push_back(u);//反向边
            f[u].push_back(v);//正向边
            du[u] ++;
        }
        topo();
    }
    return 0;
}