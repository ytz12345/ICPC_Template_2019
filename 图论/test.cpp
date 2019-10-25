#include <set>
#include <queue>
#include <cmath>
#include <stack>
#include <cstdio>
#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

typedef long long ll;
typedef pair<int, int> piir;

const int N = 20010;
const int M = 1e5;
const ll inf = 1e18;

int m, k, vis[N], cnt[N];

ll dis[N];

int tot, head[N];

set <int> s;

int a[N];

struct edge{
    int to, next;
    ll len;
    edge():to(0), len(0), next(0) {}
    edge(int x, int y, ll z):to(x), next(y), len(z) {}
}e[M];

deque <int> q;

vector<int> ans;

void add(int u, int v, ll w) {
    //printf("%d %d %lld\n", u, v, w);
    e[++ tot] = edge(v, head[u], w), head[u] = tot;
}

int spfa(int st) {
    q.push_back(st), dis[st] = 0;
    while (!q.empty()) {
        int now = q.front(); q.pop_front(); 
        vis[now] = 0; cnt[now] ++;
        if (cnt[now] > a[0]) {
            while (!q.empty()) q.pop_front();
            return -1;
        }
        for (int i = head[now]; i; i = e[i].next) {
            if (dis[e[i].to] > dis[now] + e[i].len) {
                dis[e[i].to] = dis[now] + e[i].len;
                if (!vis[e[i].to]) {
                    vis[e[i].to] = 1;
                    if (q.empty() || dis[e[i].to] < dis[q.front()]) q.push_front(e[i].to);
                    else q.push_back(e[i].to);
                }
            }
        }
    }
    return 1;
}

int main() {
    memset (dis, 0x3f, sizeof dis);
    while(~scanf("%d %d", &m, &k)) {
        for (int l, r; k --; ) {
            scanf("%d %d", &l, &r);
            if (l > r) swap(l, r);
            l += 10002, r += 10002;
            add(r, l - 1, -min(r - l + 1, m));
            s.insert(r), s.insert(l - 1);
        }
        a[0] = 0;
        for (set<int>::iterator it = s.begin(); it != s.end(); it ++) 
            a[++ a[0]] = *it;
        for (int i = 1; i < a[0]; i ++)
            add(a[i], a[i + 1], a[i + 1] - a[i]), add(a[i + 1], a[i], 0);
        
        spfa(a[a[0]]); 
        
        /*printf("%d\n", a[0]);
        for (int i = 1; i <= a[0]; i ++)
            printf("%d %d %lld\n", i, a[i] - 10002, dis[a[i]]);
        */
        
        for (int i = 1; i < a[0]; i ++)
            for (int j = a[i + 1] - 10002, p = dis[a[i + 1]] - dis[a[i]]; p > 0; p --)
                ans.push_back(j --);
        printf("%d\n", int(ans.size()));
        sort (ans.begin(), ans.end());
        for (int i = 0; i < ans.size(); i ++)
            printf("%d%c", ans[i], i + 1 == ans.size() ? '\n' : '\n');
        tot = 0, s.clear(); ans.clear();
        for (int i = 1; i <= a[0]; i ++) {
            head[a[i]] = 0;
            cnt[a[i]] = 0;
            vis[a[i]] = 0;
            dis[a[i]] = inf;
        }
        return 0;
    }
    return 0;
}