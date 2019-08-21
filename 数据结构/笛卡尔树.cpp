/*O(n)获得a数组的min笛卡尔树*/
void Tree() {
    for(int i = 1; i <= n; i ++) {
        while(top && a[s[top]] > a[i])
        ls[i] = s[top], top --;
        fa[i] = s[top]; fa[ls[i]] = i; 
        if(fa[i]) rs[fa[i]] = i;
        s[++ top] = i;
    }
}