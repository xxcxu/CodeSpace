#include <bits/stdc++.h>
#define int long long
static constexpr int N = 2e5 + 5;
int n, k, ans, a[N], b[N];
char s[N][32];
std::map<int, int> map;
signed main() {
    freopen("music.in", "r", stdin);
    freopen("music.out", "w", stdout);
    scanf("%lld%lld", &n, &k);
    for (int i = 1; i <= n; ++i) scanf("%s", s[i] + 1);
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= k; ++j)
            a[i] |= (1ll << j - 1) * (s[i][j] == 'A' ? 0 : 1);
    for (int i = 1; i <= n; ++i) b[i] = b[i - 1] xor a[i];
    for (int i = 1; i <= n; ++i) map[b[i]] = i;
    for (int i = 1; i <= n; ++i) {
        int R1 = (1ll << k) - 1, R2 = 0;
        ans = std::max(ans, map[R1 ^ b[i - 1]] - i + 1);
        ans = std::max(ans, map[R2 ^ b[i - 1]] - i + 1);
    } return printf("%lld\n", ans), 0;  
}