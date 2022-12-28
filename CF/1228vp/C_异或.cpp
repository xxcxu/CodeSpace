#include <iostream>
#include <cstdio>
#define ll long long
static const int N = 4e5 + 5;
int n, now, a[N], cnt[N]; ll tot, ans;
void solve() {
    scanf("%d", &n); tot = 0; now = 0;
    for (int i = 1; i <= n; ++i) scanf("%d", a + i);
    for (int i = 0; i <= 2 * n; ++i) cnt[i] = 0;
    ++ cnt[now];
    for (int i = 1; i <= n; ++i) {
        now ^= a[i];
        for (int i = 0; i * i < 2 * n; ++i)
            if ((now ^ (i * i)) < 2 * n)
                tot += cnt[now ^ (i * i)];
        ++ cnt[now];
    }
    ans = 1LL * n * (n + 1) / 2 - tot;
    printf("%lld\n", ans);
    return void();
}
signed main() {
    int t; scanf("%d", &t);
    while (t--) solve();
    return 0;
}