#include <iostream>
#include <cstdio>
#define int long long
static const int N = 1e6 + 5;
int n, m, ans;
int dp[N];
void solve() {
    scanf("%lld%lld", &n, &m);
    for (int i = n; i >= 1; --i) {
        dp[i] = (n / i) * ((n / i) - 1) / 2;
        for (int j = 2 * i; j <= n; j += i) dp[i] -= dp[j];
    }
    ans = 0;
    for (int i = n - 1; i >= 1; --i) {
        if (m < i) continue;
        int j = std::min(m, dp[i + 1]) / i;
        m -= j * i, ans += j * (i + 1);
        if (m == 0) break;
    }
    printf("%lld\n", m ? - 1 : ans);
    return void();
}

signed main() {
    int t; scanf("%lld", &t);
    while (t--) solve();
    return 0;
}