#include <bits/stdc++.h>
using ll = long long;
static constexpr int N = 1e5 + 5, M1 = 1e2 + 5, M2 = 1e4 + 5, M3 = 1e6 + 5;
int n, a[N];
int suf2[M1], suf4[M2], suf6[M3]; 
int max[3][5], id[3][5];
ll ans;
auto Calc(int lim, int *suf, int *max, int *id) -> void {
    auto Update = [&](int a, int b) -> void {max[a] = max[b]; id[a] = id[b];};
    auto Solve = [&](int x, int p) -> bool {
        for (int i = x + 1; i < 5; ++i)
            if (id[i] % 100 == p) {
                for (int j = 1; j <= i; ++j) Update(j, j - 1);
                return false;
            }
        return true;
    };
    bool f1, f2, f3, f4;
    for (int i = 0; i < lim; ++i) {
        f1 = (i % 100 != id[0] % 100);
        f2 = (i % 100 != id[1] % 100);
        f3 = (i % 100 != id[2] % 100);
        f4 = (i % 100 != id[3] % 100);
        if (suf[i] > max[0]) {
            if (Solve(0, i % 100)) {
                Update(4, 3); Update(3, 2);
                Update(2, 1); Update(1, 0);
            }
            max[0] = suf[i]; id[0] = i;
        } else if (suf[i] > max[1] && f1) {
            if (Solve(1, i % 100)) {
                Update(4, 3); Update(3, 2);
                Update(2, 1);
            }
            max[1] = suf[i]; id[1] = i;
        } else if (suf[i] > max[2] && f1 && f2) {
            if (Solve(2, i % 100)) {Update(4, 3); Update(3, 2);}
            max[2] = suf[i]; id[2] = i;
        } else if (suf[i] > max[3] && f1 && f2 && f3) {
            if (Solve(3, i % 100)) Update(4, 3);
            max[3] = suf[i]; id[3] = i;
        } else if (suf[i] > max[4] && f1 && f2 && f3 && f4) {
            max[4] = suf[i]; id[4] = i;
        }
    } return void();
}
auto main() -> decltype(0) {
    freopen("lottery.in", "r", stdin);
    freopen("lottery.out", "w", stdout);
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) scanf("%d", a + i);
    for (int i = 1; i <= n; ++i) {
        ++ suf2[a[i] % 100];
        ++ suf4[a[i] % 10000];
        ++ suf6[a[i]];
    }
    Calc(100, suf2, max[0], id[0]);
    Calc(10000, suf4, max[1], id[1]);
    Calc(1000000, suf6, max[2], id[2]);
    for (int x = 0; x < 5; ++x)
        for (int y = 0; y < 5; ++y)
            for (int z1 = 0; z1 < 5; ++z1)
                for (int z2 = z1 + 1; z2 < 5; ++z2)
                    for (int z3 = z2 + 1; z3 < 5; ++ z3) {
                        int fx = id[2][x] % 100, fy = id[1][y] % 100, fz1 = id[0][z1], fz2 = id[0][z2], fz3 = id[0][z3];
                        if (fx && ((fx == fy && fy) || (fx == fz1 && fz1) || (fx == fz2 && fz2) || (fx == fz3 && fz3))) continue;
                        if (fy && ((fy == fz1 && fz1) || (fy == fz2 && fz2) || (fy == fz3 && fz3))) continue;
                        long long ret = 0;
                        ret += suf6[id[2][x]] * 300000ll; ret += suf4[id[1][y]] * 4000ll;
                        ret += suf2[id[0][z1]] * 500ll; ret += suf2[id[0][z2]] * 500ll;
                        ret += suf2[id[0][z3]] * 500ll; ans = std::max(ret, ans);
                    }
    return printf("%lld\n", ans), 0;
}