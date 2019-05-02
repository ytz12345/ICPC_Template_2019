/*RT,给定若干包含问号的字符串，修改为有序字符串的情况总数*/
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int Mod = 1e9 + 7;

int n, m;

char s[60][30];

int len[60];

int dp[2][60][60][30];

int main() {
	ios::sync_with_stdio(false);
	cin >> n;
	for (int i = 0; i < n; i ++) {
		cin >> s[i], len[i] = strlen(s[i]);
		m = max(m, len[i]);
		for (int j = 0; j < len[i]; j ++)
			if (s[i][j] == '?') s[i][j] = 27;
			else s[i][j] -= 'a' - 1;
	}
	for (int i = 0; i < n; i ++) {
		for (int j = len[i]; j < m; j ++)
			s[i][j] = 0;
	}
	int t1, t2; 
	for (int i = m - 1; i >= 0; i --) {
		for (int l = n - 1; l >= 0; l --) {
			for (int r = l; r < n; r ++) {
				for (int ch = 26; ch >= 0; ch --) {
					int &ans = dp[i & 1][l][r][ch];
					ans = ch == 26 ? 0 : dp[i & 1][l][r][ch + 1];
					for (int k = l; k <= r; k ++) {
						if (s[k][i] == 27 && !ch) break;
						if (s[k][i] != 27 && s[k][i] != ch) break;
						if (i == m - 1) t1 = l == k;
						else t1 = dp[!(i & 1)][l][k][0];
						if (k == r) t2 = 1;
						else if (ch == 26) t2 = 0;
						else t2 = dp[i & 1][k + 1][r][ch + 1];
						ans += 1ll * t1 * t2 % Mod;
						if (ans >= Mod)	ans -= Mod;
					}
				}
			}
		}
	}
	cout << (dp[0][0][n - 1][0] % Mod + Mod) % Mod << '\n';
	return 0;
}