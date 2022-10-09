#include <bits/stdc++.h>
constexpr int N = 1e6 + 5;
int n, p, q[N];
bool vis[N];
struct operat {int opt, x;} a[N];
void solve() {
    scanf("%d%d", &p, &n);
    for (int i = 1; i <= n; ++i) scanf("%d%d", &a[i].opt, &a[i].x);
    for (int i = 1; i <= n; ++i) q[i] = i;
    for (int i = 0; i < p; ++i) vis[i] = false;
    do {
        int w = 1;
        for (int i = 1; i <= n; ++i) {
            if (a[q[i]].opt) w = 1ll * w * a[q[i]].x % p;
            else w = a[q[i]].x;
        } vis[w] = true;
    } while (std::next_permutation(q + 1, q + n + 1));
    int ans = 0;
    for (int i = 0; i < p; ++i) if (!vis[i]) ++ ans;
    printf("%d\n", ans);
}
signed main() {
    freopen("zjiang.in", "r", stdin);
    freopen("zjiang.out", "w", stdout);
    int t; scanf("%d", &t);
    while (t--) solve();
    return 0;
}