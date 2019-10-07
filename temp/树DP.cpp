#include<cstdio>
#include<cmath>
#include<cstring>
#include<vector>
#include<iostream>
using namespace std;

#define rep(i,l,r) for(int i=l;i<=r;i++)
#define dow(i,l,r) for(int i=r;i>=l;i--)
#define rep0(i,r) for(int i=0;i<r;i++)

int const N=200200;
typedef long long ll;

int n;
int f[N],l[N],ef[N][2],el[N][2],dpf[N],dpl[N],ans[N];
vector<int> v[N];

#define vsz(x) (int)(v[x].size())
#define fi first
#define se second
#define mp make_pair
#define pb push_back

void dfs_bottom_up(int x,int fa=0) 
{
    //f[i],l[i],ef[i][0-1],el[i][0-1],dpf[i],dpl[i];
    f[x]=l[x]=1;
    ef[x][0]=ef[x][1]=el[x][0]=el[x][1]=0;
    if (!vsz(x)) return;
    for(auto son:v[x]) {
        if (son==fa) continue;
        dfs_bottom_up(son,x);
        f[x]=max(l[son]+l[x],max(f[x],f[son]));
        l[x]=max(l[x],l[son]+1);
    }
    
    int m1=1,m2=1;
    rep(i,0,vsz(x)-1) {
        int son=v[x][i]; 
        if (son==fa) continue;
        ef[son][0]=m1;
        el[son][0]=m2;
        m1=max(m1,max(f[son],m2+l[son]));
        m2=max(m2,l[son]+1);
     //   cout<<nson<<" "<<f1[nson][0]<<" "<<f1[nson][1]<<endl;
    }
    m1=1,m2=1;
    dow(i,0,vsz(x)-1) {
        int son=v[x][i];
        if (son==fa) continue;
        ef[son][1]=m1;
        el[son][1]=m2;
        m1=max(m1,max(f[son],m2+l[son]));
        m2=max(m2,l[son]+1);
    //    cout<<nson<<" "<<f2[nson][0]<<" "<<f2[nson][1]<<endl;
    }

    rep(i,0,vsz(x)-1) {
        int son=v[x][i];
        if (son==fa) continue;
        ef[son][0]=max(el[son][0]+el[son][1]-1,max(ef[son][0],ef[son][1]));
        el[son][0]=max(el[son][0],el[son][1]);
    }
}

void dfs_top_down(int x,int fa=0) {
    if (fa) {
        dpf[x] = max(dpl[fa]+el[x][0],max(dpf[fa],ef[x][0]));
        dpl[x] = max(dpl[fa]+1,el[x][0]);
    }
    for(auto son:v[x]) {
        if (son==fa) continue;
        dfs_top_down(son,x);
    }
} 

void solve()
{
    scanf("%d",&n);
    rep(i,1,n-1) {
        int j,k;
        scanf("%d %d",&j,&k);
        v[j].pb(k);
        v[k].pb(j);
    }
    rep(i,1,n) ans[i]=0;
    dfs_bottom_up(1);
    dfs_top_down(1);
    rep(i,1,n) {
        int j=f[i],k=dpf[i];
        if (j<k) swap(j,k);
        ans[j]=max(ans[j],k);
    }
    dow(i,2,n) ans[i-1]=max(ans[i-1],ans[i]);
    ll sum=0;
    rep(i,1,n) ans[i]=min(ans[i],i);
    rep(i,1,n)
        sum+=2ll*ans[i]-(ans[i]==i);
//    rep(i,1,n) printf("%d ",ans[i]);
    printf("%lld\n",sum); 
    rep(i,1,n) v[i].clear(); 
}

int main()
{
    int t;
    scanf("%d",&t);
    while (t--) solve();    
    return 0;
}