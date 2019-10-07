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

const LL inf=1LL<<60;
const int N=100100;
const int NN=8001000;
struct Tree{
    pair<LL,int> fir,sec;
    LL mk;
};
Tree tree[NN];
//edge
struct E{
    int x1,x2;
    LL v;
};
E e[N];
//top fa
struct Top{
    int st,ed,rt,fr;
    Top(){}
    Top(int a,int b,int c,int d){
        rt=a;fr=b;st=c;ed=d;
    }
};
vector<Top> top[N];

pair<LL,int> p[N];
int lson[NN],rson[NN];
int total,ptot,rt[N],sz[N],msz[N],siz[N],vis[N],root;
int n,m;
vector< pair<int,LL> > v[N];

void dfs_size(int x,int fa)
{
    sz[x]=1;
    for(auto now:v[x]) {
        if (vis[now.fir] || now.fir==fa) continue;
        dfs_size(now.fir,x);
        sz[x]+=sz[now.fir];
    }
}

void dfs_find(int x,int fa,int y)
{
    msz[x]=y-sz[x];
    for(auto now:v[x]) {
        if (vis[now.fir] || now.fir==fa) continue;
        msz[x]=max(msz[x],sz[now.fir]);
        dfs_find(now.fir,x,y);
    }
    if (msz[root]>msz[x]) root=x;
}

void dfs_len(int x,int rt,int fr,int fa,LL len)
{
    int st;
//    printf(" %d",x);
    p[st=++total]=mp(len,fr);
    for(auto now:v[x]) {
        if (vis[now.fir] || fa==now.fir) continue;
        dfs_len(now.fir,rt,fr,x,len+now.sec);
    }
    top[x].pb(Top(rt,fr,st,total));
}

int newpoint()
{
    ++ptot;
    if (ptot>NN) while (1){};
    tree[ptot].fir=mp(-inf,n+1);
    tree[ptot].sec=mp(-inf,n+2);
    tree[ptot].mk=0;
    lson[ptot]=rson[ptot]=0;
    return ptot;
}

void pushdown(int x)
{
    if (tree[x].mk) {
        tree[lson[x]].fir.fir+=tree[x].mk;
        tree[lson[x]].sec.fir+=tree[x].mk;
        tree[rson[x]].fir.fir+=tree[x].mk;
        tree[rson[x]].sec.fir+=tree[x].mk;
        tree[lson[x]].mk+=tree[x].mk;
        tree[rson[x]].mk+=tree[x].mk;
        tree[x].mk=0;
    }
}
void update(Tree &x,Tree &ls,Tree &rs)
{
    if (ls.fir.sec==rs.fir.sec) {
        x.fir=mp(max(ls.fir.fir,rs.fir.fir),ls.fir.sec);
        if (ls.sec.fir>rs.sec.fir) x.sec=ls.sec;
        else x.sec=rs.sec;
    }
    else
    if (ls.fir.fir>rs.fir.fir) {
        x.fir=ls.fir;
        if (ls.sec.fir>rs.fir.fir) x.sec=ls.sec;
        else x.sec=rs.fir;
    }
    else {
        x.fir=rs.fir;
        if (rs.sec.fir>ls.fir.fir) x.sec=rs.sec;
        else x.sec=ls.fir;
    }
}

void build(int &x,int l,int r)
{
    x=newpoint();
    if (l==r) {
        tree[x].fir=p[l];
        return;
    }
    int mid=(l+r)>>1;
    build(lson[x],l,mid);
    build(rson[x],mid+1,r);
    update(tree[x],tree[lson[x]],tree[rson[x]]);
}

LL askx(int x,int l,int r,int y)
{
    if (l==r) return tree[x].fir.fir;
    pushdown(x);
    int mid=(l+r)>>1;
    if (y<=mid) return askx(lson[x],l,mid,y);
    return askx(rson[x],mid+1,r,y);
}

void change(int x,int l,int r,int ll,int rr,LL y)
{
    if (ll<=l && r<=rr) {
        tree[x].mk+=y;
        tree[x].fir.fir+=y;
        tree[x].sec.fir+=y;
        return;
    }
    pushdown(x);
    int mid=(l+r)>>1;
    if (ll<=mid) change(lson[x],l,mid,ll,rr,y);
    if (rr>mid) change(rson[x],mid+1,r,ll,rr,y);
    update(tree[x],tree[lson[x]],tree[rson[x]]);
}

void calc(int x)
{
    vis[x]=1;
//    printf("Array %d:",x);
    p[total=1]=mp(0,x);
    for(auto now:v[x]) {
        if (vis[now.fir]) continue;
        dfs_len(now.fir,x,now.fir,0,now.sec);
    }
//    puts("");
    build(rt[x],1,siz[x]=total);
    top[x].pb(Top(x,x,1,total));
    for(auto now:v[x]) {
        if (vis[now.fir]) continue;
        dfs_size(now.fir,0);
        root=0;
        dfs_find(now.fir,0,sz[now.fir]);
        calc(now.fir);
    }
}

char s[3];

void solve()
{
    msz[0]=1<<30;
    ptot=total=0;
    scanf("%d",&n);
    int j,k;
    LL l,ans;
    rep(i,1,n-1) {
        scanf("%d %d %lld",&j,&k,&l);
        v[j].pb(mp(k,l));
        v[k].pb(mp(j,l));
        e[i].x1=j;e[i].x2=k;e[i].v=l;
    }
    dfs_size(1,0);
    root=0;
    dfs_find(1,0,n);
    calc(root);
    int i;
    scanf("%d",&m);
    while(m--) {
        scanf("%s",s);
        if (s[0]=='Q') {
            scanf("%d",&j);
            ans=0;
            for(auto now:top[j]) {
//                printf("%d %d %lld %d %lld %d\n",now.rt,now.fr,
//                    tree[rt[now.rt]].fir.fir,tree[rt[now.rt]].fir.sec,
//                    tree[rt[now.rt]].sec.fir,tree[rt[now.rt]].sec.sec);
                LL dep=askx(rt[now.rt],1,siz[now.rt],now.st);
                if (tree[rt[now.rt]].fir.sec==now.fr)
                    ans=max(ans,tree[rt[now.rt]].sec.fir+dep);
                else ans=max(ans,tree[rt[now.rt]].fir.fir+dep);
            }
            printf("%lld\n",ans);
        }
        else {
            scanf("%d %lld",&i,&l);
            j=e[i].x1,k=e[i].x2;
            if (siz[j]<siz[k]) swap(j,k);
//            puts("Case 2");
            for(auto &now:top[k]) {
//                printf("%d %d %lld %d %lld %d\n",siz[now.rt],now.rt,
//                    tree[rt[now.rt]].fir.fir,tree[rt[now.rt]].fir.sec,
//                    tree[rt[now.rt]].sec.fir,tree[rt[now.rt]].sec.sec);
                if (siz[now.rt]<siz[j]) continue;
                change(rt[now.rt],1,siz[now.rt],now.st,now.ed,l-e[i].v);
            }
            e[i].v=l;
        }
    }
}

int main()
{
    solve();
    return 0;
}