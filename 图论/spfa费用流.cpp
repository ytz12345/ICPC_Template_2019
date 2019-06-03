const int N = 600, M = 800000, inf = 0x3f3f3f3f;
int s, t, ans, len, maxflow;
int T, n, m, K, W;
int head[N], incf[N], path[N], pre[N], vis[N], d[N];
struct edge{int to, next, cap, cost;}e[M];
struct video {int s, t, w, op; }a[N];
void add(int u, int v, int w, int c) {
	e[++ len] = (edge){v, head[u], w, c}, head[u] = len;
	e[++ len] = (edge){u, head[v], 0, -c}, head[v] = len;
}
bool spfa() {
	deque <int> q;
	q.push_back(s), incf[s] = inf;
	for (int i = 1; i <= t; i ++) d[i] = inf;
	d[s] = 0;
	while (!q.empty()) {
		int x = q.front();
		q.pop_front(), vis[x] = 0;
		for (int i = head[x]; i; i = e[i].next) {
			if (e[i].cap && d[e[i].to] > d[x] + e[i].cost) {
				d[e[i].to] = d[x] + e[i].cost;
				pre[e[i].to] = x, path[e[i].to] = i;
				incf[e[i].to] = min(incf[x], e[i].cap);
				if (!vis[e[i].to]) {
					vis[e[i].to] = 1;
					if (q.empty() || d[e[i].to] < d[q.front()]) q.push_front(e[i].to);
					else q.push_back(e[i].to);
				}
			}
		}
	}
	maxflow += incf[t];
	if (d[t] == inf) return 0;
	for (int i = t; i != s; i = pre[i]) {
		e[path[i]].cap -= incf[t];
		e[path[i] ^ 1].cap += incf[t];
	}
	return ans += incf[t] * d[t], 1;
}
int main() {
	/*build graph*/
	while(spfa());
}
