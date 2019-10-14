/*无用边定义:对于边(u,v)如果存在从u到v不经过该边的另一条路径，则称该边无用
 *时间复杂度:O(n^3) */
bool f[N][N];//i是否可达j
vector <int> e[N];
int main() {
    rep(i, 1, n)
        for (int j : e[i]) {
            rep (k, 1, n)
                if (i != k && j != k && f[i][k] && f[k][j])
                    no_use_edge;
        }
}
