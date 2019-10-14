void kmp(int n, char *a, int m, char *b) {
    //长度为m的b中找a,下标从0开始,得到的是匹配成功的末尾位置
    static int nxt[N], i, j;
    for (nxt[0] = j = -1, i = 1; i < n; nxt[i ++] = j) {
        while (~j && a[j + 1] != a[i]) j = nxt[j];
        if (a[j + 1] == a[i]) j ++;
    }
    for (j = -1, i = 0; i < m; i ++) {
        while (~j && a[j + 1] != b[i]) j = nxt[j];
        if (a[j + 1] == b[i]) j ++;
        if (j == n - 1) {
            printf("%d ", i);
            j = nxt[j];
        }
    }
}