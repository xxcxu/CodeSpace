#include <iostream>
#include <cstdio>
#include <set>
#define ep emplace
#define int long long
static constexpr int N = 100005;
int n, m, q;
int a[N], b[N];
std::multiset<int> s1, s2;
signed main() {
    freopen("bus.in", "r", stdin);
    freopen("bus.out", "w", stdout);
    scanf("%lld%lld%lld", &n, &m, &q);
    for (int i = 1; i <= n; ++i) scanf("%lld", a + i), s1.ep(a[i]);
    for (int i = 1; i <= m; ++i) scanf("%lld", b + i), s2.ep(b[i]);
    while (q--) {
        static int op;
        scanf("%lld", &op);
        if (op == 0) {
            static int x, c;
            scanf("%lld%lld", &x, &c);
            s1.erase(s1.find(a[x])); s1.ep(c);
            a[x] = c;
        } else if (op == 1) {
            static int x, c;
            scanf("%lld%lld", &x, &c);
            s2.erase(s2.find(b[x])); s2.ep(c);
            b[x] = c;
        } else {
            static int x, y, xx, yy;
            scanf("%lld%lld%lld%lld", &x, &y, &xx, &yy);
            int ans = 1e12;
            if (x == xx && y == yy) ans = 0;
            if (x == xx) ans = std::min(ans, a[x]);
            if (y == yy) ans = std::min(ans, b[y]);
            ans = std::min(ans, a[x] + b[yy]);
            ans = std::min(ans, b[y] + a[xx]);
            ans = std::min(ans, a[x] + a[xx] + *s2.begin());
            ans = std::min(ans, b[y] + b[yy] + *s1.begin());
            printf("%lld\n", ans);
        }
    }
    return 0;
}