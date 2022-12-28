#include <iostream>
#include <cstdio>
#include <vector>
#define int long long
#define L 3.9
#define TimePast() (double)clock()/CLOCKS_PER_SEC
#define eb emplace_back
using PII = std::pair<int, int>;
static constexpr int N = 1e5 + 5;
int n, rt, max, ans, dep1[N], dep2[N], dep3[N]; bool vis[N]; std::vector<PII> e1[N], e2[N], e3[N];
void dfs1(int x, int fa) {for (auto [y, z] : e1[x]) if (y != fa) dep1[y] = dep1[x] + z, dfs1(y, x);}
void dfs2(int x, int fa) {for (auto [y, z] : e2[x]) if (y != fa) dep2[y] = dep2[x] + z, dfs2(y, x);}
void dfs3(int x, int fa) {for (auto [y, z] : e3[x]) if (y != fa) dep3[y] = dep3[x] + z, dfs3(y, x);}
signed main() {
    scanf("%lld", &n);
    for (int i = 1; i < n; ++i) {
        static int u, v, w;
        scanf("%lld%lld%lld", &u, &v, &w);
        e1[u].eb(v, w); e1[v].eb(u, w);
    }
    for (int i = 1; i < n; ++i) {
        static int u, v, w;
        scanf("%lld%lld%lld", &u, &v, &w);
        e2[u].eb(v, w); e2[v].eb(u, w);
    }
    for (int i = 1; i < n; ++i) {
        static int u, v, w;
        scanf("%lld%lld%lld", &u, &v, &w);
        e3[u].eb(v, w); e3[v].eb(u, w);
    }
    while (TimePast() < L) {
        while (vis[rt] && TimePast() < L) rt = rand() % n + 1;
        vis[rt] = true;
        dep1[rt] = dep2[rt] = dep3[rt] = 0;
        dfs1(rt, 0); dfs2(rt, 0); dfs3(rt, 0);
        max = 0;
        for (int i = 1; i <= n; ++i)
            if (dep1[i] + dep2[i] + dep3[i] > max)
                max = dep1[i] + dep2[i] + dep3[i], rt = i;
        ans = std::max(ans, max);
    }
    return printf("%lld\n", ans), 0;
}