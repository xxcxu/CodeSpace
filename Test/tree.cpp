#include <bits/stdc++.h>
#define eb emplace_back
static constexpr int N = 8e4 + 5, P = 1e9 + 7;
int n, ans, a[N], b[N];
int sumab[N], suma[N], sumb[N], cnt[N];
int inc(int x, int y) {return (x + y) % P;}
int dec(int x, int y) {return (x + P - y) % P;}
int mul(int x, int y) {return 1LL * x * y % P;}
void TreeDp(int x, int fa) {
    sumab[x] = mul(a[x], b[x]), cnt[x] = 1;
    suma[x] = a[x], sumb[x] = b[x];
    for (int y : e[x]) if (y != fa) {
        TreeDp(y, x);
        int res = inc(cnt[y], 1);
        sumab[x] = inc(inc(inc(mul(sumab[x], res), mul(sumab[y], cnt[x])), mul(suma[x], sumb[y])), mul(sumb[x], suma[y]));
        suma[x] = inc(mul(suma[x], res), mul(suma[y], cnt[x]));
        sumb[x] = inc(mul(sumb[x], res), mul(sumb[y], cnt[x]));
        cnt[x] = mul(cnt[x], res);
    }
    ans = inc(ans, mul(sumab[x], cnt[x]));
    return void();
}
signed main() {
    freopen("tree.in", "r", stdin);
    freopen("tree.out", "w", stdout);
    scanf("%d", &n);
    for (int i = 1; i < n; ++i) {
        static int u, v;
        scanf("%d%d", &u, &v);
        e[u].eb(v); e[v].eb(u);
    }
    for (int i = 1; i <= n; ++i) scanf("%d", a + i);
    for (int i = 1; i <= n; ++i) scanf("%d", b + i);
    TreeDp(1, 0);
    printf("%d\n", ans);
    return 0;
}