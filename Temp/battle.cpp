// 设 f[i][j][0/1] 为当前进行了i轮，我的左边有j人被打败，这轮我打/不打 我目前获胜的概率
#include <bits/stdc++.h>
static constexpr int N = 5e2 + 5;
int n, K, a[N], l[N], r[N], p[N];
double ans;
auto erase(int x) -> void {
    r[l[x]] = r[x];
    l[r[x]] = l[x];
}
auto main() -> decltype(0) {
    freopen("battle.in", "r", stdin);
    freopen("battle.out", "w", stdout);
    scanf("%d%d", &n, &K);
    for (int i = 1; i <= n; ++i) scanf("%d", a + i);
    for (int i = 1; i <= n; ++i) p[i] = i;
    do { 
        if (p[n] != K) continue;
        double res = 1.0;
        for (int i = 1; i <= n; ++i) l[i] = i - 1, r[i] = i + 1;
        for (int i = 1; i < n; ++i) {
            double f1 = 0, f2 = 0;
            if (l[p[i]] > 0) f1 = 1.0 * a[l[p[i]]] / (a[l[p[i]]] + a[p[i]]) / (n - i);
            if (r[p[i]] < n + 1) f2 = 1.0 * a[r[p[i]]] / (a[r[p[i]]] + a[p[i]]) / (n - i);
            res *= f1 + f2;
            erase(p[i]);
        }
        ans += res;
    } while(std::next_permutation(p + 1, p + n + 1));
    return printf("%.17lf\n", ans), 0;
}