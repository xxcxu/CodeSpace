#include <iostream>
#include <cstdio>
static const int P = 1000000007, inv2 = 500000004;
int inc(int x, int y) {return (x + y) % P;}
int dec(int x, int y) {return (x + P - y) % P;}
int mul(int x, int y) {return 1LL * x * y % P;}
int qpow(int x, int y, int P) {
    int ans = 1;
    for (; y; y >>= 1, x = 1ll * x * x % P)
        if (y & 1) ans = 1ll * ans * x % P;
    return ans % P;
}
void solve() {
    int n; scanf("%d", &n);
    int ans = 0;
    ans = inc(ans, mul(mul(mul(n, n + 1), inc(mul(2, n), 1)), qpow(6, P - 2, P)));
    ans = mul(ans, 2); ans = inc(ans, mul(mul(n, n + 1), inv2));
    ans = dec(ans, mul(n, n + 1));
    printf("%d\n", mul(ans, 2022));
    return void();
}
signed main() {
    int t; scanf("%d", &t);
    while (t--) solve();
    return 0;
}