#include <iostream>
#include <cstdio>
#include <vector>

#define ll long long
#define vi std::vector<int>
#define vl std::vector<ll>
#define vvi std::vector<std::vector<int> >
#define vvl std::vector<std::vector<ll> >

int n, m;

bool check(int x, vvi a) {
    vvl s(n + 1, vl(m + 1, 0));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            if (a[i][j] >= x) a[i][j] = 1;
            else a[i][j] = 0;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            s[i + 1][j + 1] = s[i][j + 1] + s[i + 1][j] - s[i][j] + a[i][j];
    for (int i = x; i <= n; ++i)
        for (int j = x; j <= m; ++j) {
            ll sum = s[i][j] - s[i - x][j] - s[i][j - x] + s[i - x][j - x];
            if (sum == 1LL * x * x) return true;
        }
    return false;
}

void solve() {
    scanf("%d%d", &n, &m);
    vvi a(n, vi(m, 0)); 
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            scanf("%d", &a[i][j]);
    int l = 0, r = std::min(n, m), ans;
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (check(mid, a)) ans = mid, l = mid + 1;
        else r = mid - 1;
    }
    printf("%d\n", ans);
    return void();
}

int main() {
    int t; scanf("%d", &t);
    while (t--) solve();
    return 0;
}