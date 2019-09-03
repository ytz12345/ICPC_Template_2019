/*a存所有初始边,d[i][j]存i-j经过的所有中间点<k时的最短路径,pos存对应中间点*/
int a[N][N], d[N][N], pos[N][N], path[N];//O(N^3)
void getpath(int x,int y){
     if(pos[x][y]==-1) return ;
     getpath(x,pos[x][y]);
     path[++ path[0]] = pos[x][y];
     getpath(pos[x][y],y);
}
int main(){
    int ans = inf;//最短路径长度
    /*初始化a,d正无穷,pos为-1,然后读入所有边，邻接矩阵村边*/
    rep(k, 1, n) {
        rep(i, 1, k - 1) rep(j, i + 1, k - 1) 
            if (ans > d[i][j] + a[i][k] + a[k][j]) {
                ans = d[i][j] + a[i][k] + a[k][j];
                path[path[0] = 1] = i;
                getpath(i, j);
                path[++ path[0]] = j;
                path[++ path[0]] = k; 
            } 
        rep(i, 1, n) rep(j, 1, n)
            if (d[i][j] > d[i][k] + d[k][j]) {
                d[i][j] = d[i][k] + d[k][j];
                pos[i][j] = k;
            }
    }
}