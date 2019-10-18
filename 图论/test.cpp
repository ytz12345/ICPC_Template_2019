#include <queue>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

typedef pair<int, int> piir;

const int N = 5e4 + 5;
const int M = 1e6 + 5 + N;
const int inf = 1e9 + 7;

int n, m1, m2, dis[N], vis[N], cnt[N];

int tot, head[N];

struct edge{
    int to, next, len;
    edge():to(0), len(0), next(0) {}
    edge(int x, int y, int z):to(x), next(y), len(z) {}
}e[M];

queue <int> q;

char str[N];

void add(int u, int v, int w) {
    e[++ tot] = edge(v, head[u], w), head[u] = tot;
}

int main() {
    while (~scanf("%d %d %d", &n, &m1, &m2)) {
        tot = 0;
        for (int i = 0; i <= n; i ++) {
            head[i] = 0;
            cnt[i] = 0;
            dis[i] = inf;
        }
        for (int u, v, w; m1 --; ) {
            scanf("%d %d %d", &u, &v, &w);
            add(u, v, w);
        }
        for (int u, v, w; m2 --; ) {
            scanf("%d %d %d", &u, &v, &w);
            add(v, u, -w);
        }
        for (int i = 1; i < n; i ++)
            add(i + 1, i, 0);
        int flag = 1;
        q.push(1), dis[1] = 0;
        while (!q.empty()) {
            int now = q.front(); q.pop(); 
            vis[now] = 0; cnt[now] ++;
            if (cnt[now] > n) {
                while (!q.empty()) q.pop();
                flag = 0; break;
            }
            for (int i = head[now]; i; i = e[i].next) {
                if (dis[e[i].to] > dis[now] + e[i].len) {
                    dis[e[i].to] = dis[now] + e[i].len;
                    if (!vis[e[i].to]) {
                        vis[e[i].to] = 1;
                        q.push(e[i].to);
                    }
                }
            }
        }
        if (flag) printf("%d\n", dis[n] == inf ? -2 : dis[n]);
        else puts("-1");
    }
}