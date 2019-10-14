/*n/2个排列使得所有数对(i,j)且i<j都出现一次
 *n为奇数则首尾相连，偶数不连
 */
typedef vector<int> vi;
void get_even(int n, vi ans[]) {
    vi a(n);
    for (int i = 0; i < n; i ++)
        a[i] = i + 1;
    for (int i = 1; i <= n / 2; i ++) {
        ans[i].resize(n + 1);
        for (int j = 0; j < n / 2; j ++)
            ans[i][j * 2] = a[j], ans[i][j * 2 + 1] = a[n - 1 - j];
        int t = a[n - 1];
        for (int j = n - 1; j > 0; j --)
            a[j] = a[j - 1];
        a[0] = t;
    }
}
void get_odd(int n, vi ans[]) {
    get_even(n - 1, ans);
    for (int i = 1; i <= n / 2; i ++) {
        for (int j = n - 1; j > 0; j --)
            ans[i][j] = ans[i][j - 1] + 1;
        ans[i][0] = 1;
    }
}
int main() {
    vi ans[2019];
    int n; cin >> n;
    if (n & 1) get_odd(n, ans);
    else get_even(n, ans);  
    return 0;
}
