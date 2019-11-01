/*HK算法，最坏O(n^(1/2)*m)*/
int n1, n2, m;
vector<int> e[N];
int mx[N], my[N];
queue<int> q;
int dx[N], dy[N];
bool vis[N];
bool find(int u) {
    for (int i : e[u]) {
        if (!vis[i] && dy[i] == dx[u] + 1) {
            vis[i] = true;
            if (!my[i] || find(my[i])) 
                return mx[u] = i, my[i] = u, 1;
        }
    }
    return 0;
}
int matching() {
    memset(mx, 0, sizeof mx);
    memset(my, 0, sizeof my);
    int ans = 0;
    while (1) {
        bool flag = 0;
        while (!q.empty()) q.pop();
        memset(dx, 0, sizeof dx);
        memset(dy, 0, sizeof dy);
        for (int i = 1; i <= n1; i ++)
            if (!mx[i]) q.push(i);
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int i : e[u]) if (!dy[i]) {
                dy[i] = dx[u] + 1;
                if (my[i]) {
                    dx[my[i]] = dy[i] + 1;
                    q.push(my[i]);
                }
                else flag = true;
            }
        }
        if(!flag) break;
        memset(vis, 0, sizeof vis);
        for (int i = 1; i <= n1; i ++)
            if(!mx[i] && find(i)) 
                ans ++;
    }
    return ans;
}
int main() {
    scanf("%d %d %d", &n1, &n2, &m);
    for (int u, v, i = 1; i <= m; i ++) {
        scanf("%d %d", &u, &v);
        e[u].push_back(v);
    }
    printf("%d\n", matching());
    for (int i = 1; i <= n1; i ++)//mx[i]表示和左边i匹配的右边人
        printf("%d%c", mx[i], i == n1 ? '\n' : ' ');
}