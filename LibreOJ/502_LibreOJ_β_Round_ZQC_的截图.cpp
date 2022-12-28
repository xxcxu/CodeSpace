#include <iostream>
#include <cstdio>
#include <map>
#include <unordered_map>
#include <random>

#define int long long

std::mt19937 gen(time(0));

static const int N = 2000005;
int n, m, f[N], val[N];
std::unordered_map<int, int> mp;

int XOR(int x, int y) {
    static int a[50], b[50];
    int n = 0, m = 0, ans = 0;
    for (int i = 0; i < 50; ++i) a[i] = b[i] = 0;
    while (x) a[++ n] = x % 3, x /= 3;
    while (y) b[++ m] = y % 3, y /= 3;
    for (int i = std::max(n, m); i >= 1; --i) ans = ans * 3 + (a[i] + b[i]) % 3;
    return ans; 
}

signed main() {
    scanf("%lld%lld", &n, &m);
    for (int i = 1; i <= n; ++i) val[i] = abs(1ll * abs((int)gen()) << 31 | abs((int)gen())) / 9;
    for (int i = 1; i <= n; ++i) mp[val[i]] = i, mp[XOR(val[i], val[i])] = i;
    for (int i = 1; i <= m; ++i) {
        static int x, fa, lastans;
        scanf("%lld%lld", &x, &fa);
        x ^= lastans, fa ^= lastans;
        f[i] = XOR(f[fa], val[x]);
        if (!f[i]) lastans = -1;
        else if (!mp.count(f[i])) lastans = -2;
        else lastans = mp[f[i]];
        printf("%lld\n", lastans);
    } return 0;
}