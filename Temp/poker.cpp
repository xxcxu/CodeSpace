#include <bits/stdc++.h>
static constexpr int N = 1e2 + 5;
int T, Case, m, nn, ans, p[N], n[N], a[N];
auto Solve(int test_case = 0) -> void {
    printf("Case #%d: ", test_case);
    scanf("%d", &m); nn = ans = 0;
    for (int i = 1; i <= m; ++i) scanf("%d%d", p + i, n + i);
    for (int i = 1; i <= m; ++i)
        for (int j = 1; j <= n[i]; ++j) a[++ nn] = p[i];
    int sn = (1 << nn) - 1;
    for (int sta = 0; sta <= sn; ++sta) {
        int sum = 0, multi = 1;
        for (int i = 0; i < nn; ++i)
            if (sta >> i & 1) sum += a[i + 1];
            else multi *= a[i + 1];
        if (sum == multi) ans = std::max(ans, multi);
    }
    return printf("%d\n", ans), void();
}
auto main() -> decltype(0) {
    freopen("poker.in", "r", stdin);
    freopen("poker.out", "w", stdout);
    scanf("%d", &T);
    while (T--) Solve(++ Case);
    return 0;
}