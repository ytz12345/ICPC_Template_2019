/*最小表示:a[0...n-1],a[1...n-1,0],a[2...n-1,0,1]
 *n个序列中字典序最小的表示，即为该序列的最小表示
 *该函数返回的是某个最小表示起始位置的下标
 */
int minrep(int n) {
    int i = 0, j = 1, k = 0, t;
    while (i < n && j < n && k < n) 
        if (t = a[(i + k) % n] - a[(j + k) % n]) {
            if (t > 0) i += k + 1;
            else       j += k + 1;
            if (i == j) j ++;
            k = 0;
        }   
        else 
            k ++;
    return i < j ? i : j;
}
