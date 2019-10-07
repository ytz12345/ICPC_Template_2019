#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
typedef long long LL;
const int N=100005;
vector<int>vec[N];
int n,m,num,deep[N],adj[N],e,l[N],r[N];
struct edge{int zhong,next;}s[N<<1];
inline void add(int qi,int zhong){s[++e].zhong=zhong;s[e].next=adj[qi];adj[qi]=e;}
struct data{int qi,zhong;}ro[N];
inline bool mt(const data &a,const data &b){return (a.qi==b.qi)?a.zhong<b.zhong:a.qi<b.qi;}
struct node
{
    node *ch[2];int cnt;
    void* operator new (size_t,node *a,node *b,int c)  
    {  
        static node mempool[N*38],*C=mempool;  
        C->ch[0]=a,C->ch[1]=b,C->cnt=c;  
        return C++;  
    }  
    node* insert(int l,int r,int pos,int val)
    {
        if(l==r)return new (NULL,NULL,this->cnt+val)node;
        int mi=(l+r)>>1;
        if(pos<=mi) return new (ch[0]->insert(l,mi,pos,val),ch[1],this->cnt+val)node;
        else return new (ch[0],ch[1]->insert(mi+1,r,pos,val),this->cnt+val)node;
    }
}*root[N];
int query(node *a,node *b,node *c,node *d,int le,int ri,int L,int R)
{
    if(L<=le&&ri<=R)return a->cnt+b->cnt-c->cnt-d->cnt;
    int ret=0,mi=(le+ri)>>1;
    if(L<=mi)ret+=query(a->ch[0],b->ch[0],c->ch[0],d->ch[0],le,mi,L,R);
    if(mi<R)ret+=query(a->ch[1],b->ch[1],c->ch[1],d->ch[1],mi+1,ri,L,R);
    return ret;
}

int f[N][18],bin[25];
inline int LCA(int a,int b)
{
    if(deep[a]<deep[b])swap(a,b);
    int cha=deep[a]-deep[b];
    for(int j=17;~j;j--)
        if(cha&bin[j])a=f[a][j];
    if(a==b)return a;
    for(int j=17;~j;j--)
        if(f[a][j]!=f[b][j])a=f[a][j],b=f[b][j];
    return f[a][0];
}

void dfs1(int rt,int fa)
{
    l[rt]=++num;deep[rt]=deep[fa]+1;
    for(int i=adj[rt];i;i=s[i].next)
        if(s[i].zhong!=fa)f[s[i].zhong][0]=rt,dfs1(s[i].zhong,rt);
    r[rt]=++num;
}  
void dfs2(int rt,int fa)
{
    root[rt]=root[fa];
    for(int i=0,len=vec[rt].size();i<len;i++)
    {
        root[rt]=root[rt]->insert(1,n<<1,l[vec[rt][i]],1);
        root[rt]=root[rt]->insert(1,n<<1,r[vec[rt][i]],-1);
    }
    for(int i=adj[rt];i;i=s[i].next)
        if(s[i].zhong!=fa)dfs2(s[i].zhong,rt);
}
LL Z,M;
LL gcd(LL a,LL b){return (b==0)?a:gcd(b,a%b);}

int main()
{
    scanf("%d%d",&n,&m);int a,b;
    for(int i=1;i<n;i++)scanf("%d%d",&a,&b),add(a,b),add(b,a);
    for(int i=1;i<=m;i++)
        scanf("%d%d",&ro[i].qi,&ro[i].zhong),vec[ro[i].qi].push_back(ro[i].zhong);
    root[0]=new (NULL,NULL,0) node;
    root[0]->ch[0]=root[0]->ch[1]=root[0];
    dfs1(1,0);dfs2(1,0);
    bin[0]=1;for(int i=1;i<=20;i++)bin[i]=bin[i-1]<<1;
    for(int j=1;j<=17;j++)
        for(int i=1;i<=n;i++)
            f[i][j]=f[f[i][j-1]][j-1];
    for(int i=1;i<=m;i++)
    {
        int lca=LCA(ro[i].qi,ro[i].zhong),t=f[lca][0];
        a=ro[i].qi,b=ro[i].zhong;
        Z+=query(root[a],root[b],root[lca],root[t],1,n<<1,l[lca],l[a]);
        Z+=query(root[a],root[b],root[lca],root[t],1,n<<1,l[lca],l[b]);
        Z-=query(root[a],root[b],root[lca],root[t],1,n<<1,l[lca],l[lca]);
        Z--;
    }
    M=(LL)m*(m-1)>>1;LL tmp=gcd(Z,M);
    printf("%lld/%lld",Z/tmp,M/tmp);
}