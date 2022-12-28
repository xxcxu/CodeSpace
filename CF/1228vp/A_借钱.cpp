#include <iostream>
#include <cstdio>
#define int long long
static const int N = 55;
int n, a[N];
void solve() {
    scanf("%lld", &n); int prod = 1;
    for (int i = 1; i <= n; ++i) scanf("%lld", a + i);
    for (int i = 1; i <= n; ++i) prod *= a[i];
    printf("%lld\n", ((n - 1) + prod) * 2022);
}
signed main() {
    int t; scanf("%lld", &t);
    while (t--) solve();
    return 0;
}