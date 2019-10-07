#include<cstring>
#include<algorithm>
#include<cmath>
#include<cstdio>
#include<map>
#include<vector>
#include<unordered_map>
using namespace std;
 
#define rep(i,l,r) for(int i=l;i<=r;i++)
#define dow(i,l,r) for(int i=r;i>=l;i--)
#define mp make_pair
#define pb push_back
#define fir first
#define sec second
typedef long long LL;
 
 
const LL inf=1LL<<62;
const int N=120100;
 
struct Tree{
    // 0,1,2,01,12,012
    // 0    -> 记录 lp0
    // 1    -> 不需要记
    // 2    -> 记录 rp0
    // 3:01   -> 记录 lp1
    // 4:12   -> 记录 rp1
    // 5:012  -> 记录 lp2,rp2;
    LL v[6];
    LL mk;
    int lp[3],rp[3];
};
Tree tree[N*8];
struct E{
    int x1,x2;
    LL v;
};
E e[N];
LL val[N];
int p[N*2],total,st[N],ed[N],f[N][17],dep[N];
int n,m;
vector< pair<int,LL> > v[N];
 
void dfs(int x,int fa,LL deep)
{
    p[st[x]=++total]=x;
    for(auto now:v[x]) {
        if (now.fir==fa) continue;
        val[now.fir]=deep+now.sec;
        dep[now.fir]=dep[x]+1;
        f[now.fir][0]=x;
        dfs(now.fir,x,val[now.fir]);
        p[++total]=x;
    }
    ed[x]=total;
}
 
void prermq()
{
    rep(i,1,16)
        rep(j,1,n)
            f[j][i]=f[f[j][i-1]][i-1];
}
 
int lca(int x,int y)
{
 //   printf("%d %d %d %d\n",x,y,dep[x],dep[y]);
    if (dep[x]>dep[y]) swap(x,y);
    dow(i,0,16) {
  //      printf("\t%d %d\n",y,f[y][i]);
        if (dep[x]<=dep[f[y][i]]) y=f[y][i];
    }
    if (x==y) return x;
 //   printf("%d %d\n",x,y);
    dow(i,0,16)
        if (f[x][i]!=f[y][i]) x=f[x][i],y=f[y][i];
    return f[x][0];
}
 
inline void addmore(Tree &x,LL y)
{
    x.v[0]+=y;x.v[2]+=y;
    x.v[1]-=y;x.v[3]-=y;x.v[4]-=y;
    x.mk+=y;
}
 
void pushdown(int x)
{
    if (tree[x].mk) {
        addmore(tree[x<<1],tree[x].mk);
        addmore(tree[x<<1|1],tree[x].mk);
        tree[x].mk=0;
    }
}
 
void update(int x)
{
    Tree &lson=tree[x<<1],&rson=tree[x<<1|1];
    //0
    if (lson.v[0]>=rson.v[0]) {
        tree[x].v[0]=lson.v[0];
        tree[x].lp[0]=lson.lp[0];
    }
    else {
        tree[x].v[0]=rson.v[0];
        tree[x].lp[0]=rson.lp[0];
    }
    //1
    if (lson.v[1]>=rson.v[1])
        tree[x].v[1]=lson.v[1];
    else {
        tree[x].v[1]=rson.v[1];
    }
    //2
    if (lson.v[2]>=rson.v[2]) {
        tree[x].v[2]=lson.v[2];
        tree[x].rp[0]=lson.rp[0];
    }
    else {
        tree[x].v[2]=rson.v[2];
        tree[x].rp[0]=rson.rp[0];
    }
    //3:01
    if (lson.v[3]>=rson.v[3]) {
        tree[x].v[3]=lson.v[3];
        tree[x].lp[1]=lson.lp[1];
    }
    else {
        tree[x].v[3]=rson.v[3];
        tree[x].lp[1]=rson.lp[1];
    }
    //4:12
    if (lson.v[4]>=rson.v[4]) {
        tree[x].v[4]=lson.v[4];
        tree[x].rp[1]=lson.rp[1];
    }
    else {
        tree[x].v[4]=rson.v[4];
        tree[x].rp[1]=rson.rp[1];
    }
    //5:012
    if (lson.v[5]>=rson.v[5]) {
        tree[x].v[5]=lson.v[5];
        tree[x].lp[2]=lson.lp[2];
        tree[x].rp[2]=lson.rp[2];
    }
    else {
        tree[x].v[5]=rson.v[5];
        tree[x].lp[2]=rson.lp[2];
        tree[x].rp[2]=rson.rp[2];
    }
    //----------
    //考虑合并
    //3:01=0+1
    if (tree[x].v[3]<lson.v[0]+rson.v[1]*2) {
        tree[x].v[3]=lson.v[0]+rson.v[1]*2;
        tree[x].lp[1]=lson.lp[0];
    }
    //4:12=1+2
    if (tree[x].v[4]<lson.v[1]*2+rson.v[2]) {
        tree[x].v[4]=lson.v[1]*2+rson.v[2];
        tree[x].rp[1]=rson.rp[0];
    }
    //5:012=01+2,0+12
    if (tree[x].v[5]<lson.v[3]+rson.v[2]) {
        tree[x].v[5]=lson.v[3]+rson.v[2];
        tree[x].lp[2]=lson.lp[1];
        tree[x].rp[2]=rson.rp[0];
    }
    if (tree[x].v[5]<lson.v[0]+rson.v[4]) {
        tree[x].v[5]=lson.v[0]+rson.v[4];
        tree[x].lp[2]=lson.lp[0];
        tree[x].rp[2]=rson.rp[1];
    }
}
 
void build(int x,int l,int r)
{
    if (l==r) {
    //    tree[x].mk=0;
//        tree[x].v[0]=tree[x].v[2]=val[p[l]];
//        tree[x].v[1]=-val[p[l]];
//        tree[x].v[3]=tree[x].v[4]=tree[x].v[5]=-inf;
        tree[x].mk=-val[p[l]];
        addmore(tree[x],val[p[l]]);
 
        tree[x].lp[0]=tree[x].lp[1]=tree[x].lp[2]=
            tree[x].rp[0]=tree[x].rp[1]=tree[x].rp[2]=p[l];
        return;
    }
    int mid=(l+r)>>1;
    build(x<<1,l,mid);
    build(x<<1|1,mid+1,r);
    update(x);
}
 
void change(int x,int l,int r,int ll,int rr,LL y)
{
    if (ll<=l && r<=rr) {
        addmore(tree[x],y);
        return;
    }
    pushdown(x);
    int mid=(l+r)>>1;
    if (ll<=mid) change(x<<1,l,mid,ll,rr,y);
    if (rr>mid) change(x<<1|1,mid+1,r,ll,rr,y);
    update(x);
}
 
LL askx(int x,int l,int r,int y)
{
    if (l==r) return tree[x].v[0];
    pushdown(x);
    int mid=(l+r)>>1;
    if (y<=mid) return askx(x<<1,l,mid,y);
    return askx(x<<1|1,mid+1,r,y);
}
 
LL calcpoint(int x,int y)
{
    int u=lca(x,y);
  //  printf("%d %d %d %lld %lld %lld\n",x,y,u,askx(1,1,total,st[x]),
  //         askx(1,1,total,st[y]),-2LL*askx(1,1,total,st[u]));
    return askx(1,1,total,st[x])+askx(1,1,total,st[y])
            -2LL*askx(1,1,total,st[u]);
}

 
char s[3];
 
void solve()
{
    scanf("%d",&n);
    int j,k;
    LL l;
    rep(i,1,n-1) {
        scanf("%d %d %lld",&j,&k,&l);
        v[j].pb(mp(k,l));
        v[k].pb(mp(j,l));
        e[i].x1=j;e[i].x2=k;e[i].v=l;
    }
    dep[1]=1;
    dep[0]=0;
    dfs(1,0,0);
   // rep(i,1,total) printf("%d ",p[i]);puts("");
    prermq();
    build(1,1,total);
   // pput(1,1,total);
    //rep(i,0,2) printf("%d ",tree[1].lp[i]);puts("");
    //rep(i,0,2) printf("%d ",tree[1].rp[i]);puts("");
    int i;
    scanf("%d",&m);
    while(m--) {
        scanf("%s",s);
        if (s[0]=='Q') {
            scanf("%d",&j);
            printf("%lld\n",max(calcpoint(tree[1].lp[2],j),
                                calcpoint(tree[1].rp[2],j)));
        }
        else {
            scanf("%d %lld",&i,&l);
            j=e[i].x1,k=e[i].x2;
            if (f[j][0]==k) swap(j,k);
            change(1,1,total,st[k],ed[k],l-e[i].v);
            e[i].v=l;
        }
    }
}
 
int main()
{
    solve();
    return 0;
}