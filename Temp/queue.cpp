#include <bits/stdc++.h>
static constexpr int N = 4e5 + 5;
int n;
class SegmentTree {
    #define ls (rt << 1)
    #define rs (rt << 1 | 1)
    private: class TreeNode {public: int val, l, r, lazy;} tr[N << 2];
    private: auto Pushup(int rt) -> void {tr[rt].val = std::max(tr[ls].val, tr[rs].val);}
    private: auto Pushtag(int rt, int v) -> void {tr[rt].lazy += v; tr[rt].val += v;}
    private: auto Pushdown(int rt) -> void {
        if (tr[rt].lazy) {
            Pushtag(ls, tr[rt].lazy);
            Pushtag(rs, tr[rt].lazy);
            tr[rt].lazy = 0;
        } return void();
    }
    public: auto Build(int rt, int l, int r) -> void {
        tr[rt].val = tr[rt].lazy = 0;
        tr[rt].l = l, tr[rt].r = r;
        if (l == r) return void(tr[rt].val = l);
        int mid = (l + r) >> 1;
        Build(ls, l, mid); Build(rs, mid + 1, r);
        return Pushup(rt);
    }
    public: auto Update(int rt, int l, int r) -> void {
        if (l <= tr[rt].l && tr[rt].r <= r) return Pushtag(rt, -1);
        Pushdown(rt);
        int mid = (tr[rt].l + tr[rt].r) >> 1;
        if (l <= mid) Update(ls, l, r);
        if (r > mid) Update(rs, l, r);
        return Pushup(rt);
    }
    public: auto Query(int rt, int v) -> int {
        if (tr[rt].l == tr[rt].r) return tr[rt].l;
        Pushdown(rt);
        int mid = (tr[rt].l + tr[rt].r) >> 1, ans = 0;
        if (tr[ls].val >= v) ans = Query(ls, v);
        else ans = Query(rs, v);
        Pushup(rt); return ans;
    }
    #undef ls
    #undef rs
} TT;
class SegmentTree2 {
    #define ls (rt << 1)
    #define rs (rt << 1 | 1)
    private: class TreeNode {public: int val, l, r;} tr[N << 2];
    private: auto Pushup(int rt) -> void {tr[rt].val = tr[ls].val + tr[rs].val;}
    public: auto Build(int rt, int l, int r) -> void {
        tr[rt].val = 0, tr[rt].l = l, tr[rt].r = r;
        if (l == r) return void(tr[rt].val = 0);
        int mid = (l + r) >> 1;
        Build(ls, l, mid); Build(rs, mid + 1, r);
        return Pushup(rt);
    }
    public: auto Insert(int rt, int x) -> void {
        if (tr[rt].l == tr[rt].r) return void(++ tr[rt].val);
        int mid = (tr[rt].l + tr[rt].r) >> 1;
        x <= mid ? (Insert(ls, x), 0) : (Insert(rs, x), 0);
        return Pushup(rt);
    }
    public: auto Query(int rt, int v) -> int {
        if (tr[rt].l == tr[rt].r) return tr[rt].l;
        int mid = (tr[rt].l + tr[rt].r) >> 1;
        if (tr[rs].val > v) return Query(rs, v);
        else return Query(ls, v - tr[rs].val);
    }
    public: auto Query(int rt, int l, int r) -> int {
        if (l <= tr[rt].l && tr[rt].r <= r) return tr[rt].val;
        int mid = (tr[rt].l + tr[rt].r) >> 1, ans = 0;
        if (l <= mid) ans += Query(ls, l, r);
        if (r > mid) ans += Query(rs, l, r);
        return ans;
    }
    #undef ls
    #undef rs
} T;

struct BLOCK
{
    vector<pii>vt;
    void add(int x,int y){vt.pb(mk(x,min((int)vt.size()+1,y)));}
    vector<int> query()
    {
        int n=vt.size();
        vector<int>p(n+1);
        reverse(vt.begin(),vt.end());
        TT.build(1,1,n);
        for(auto [x,y]:vt)
        {
            int pos=TT.ask(1,y);p[pos]=x;
            TT.add(1,pos,n);
        }
        for(int i=n;i>=1;i--)printf("%d ",p[i]);
        return p;
    }
}a[N];
int cnt;
vector<int>bel[N];
int solve(int c,int v)
{
    int num=T.ask(1,v);
    if(bel[c].empty()||bel[c].back()<num)return ++cnt;
    return *lower_bound(bel[c].begin(),bel[c].end(),num);
}
signed main()
{
    freopen("queue.in","r",stdin);
    freopen("queue.out","w",stdout);
    scanf("%d",&n);
    T.build(1,1,n);
    for(int i=1,c,v;i<=n;i++)
    {
        scanf("%d%d",&c,&v);
        int p=solve(c,v);
        if(bel[c].empty()||bel[c].back()<p)bel[c].pb(p);
        T.insert(1,p);
        // cout<<p<<endl;
        a[p].add(i,v-T.ask(1,p+1,cnt)+1);
    }
    for(int i=1;i<=cnt;i++)
    {
        a[i].query();
    }
    return 0;
}t