#include <bits/stdc++.h>
static constexpr int N = 4e5 + 5;
int n, p[N];
class people {public: int c, a, p;} a[N];
auto main() -> decltype(0) {
    freopen("queue.in", "r", stdin);
    freopen("queue.out", "w", stdout);
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) scanf("%d%d", &a[i].c, &a[i].a);
    for (int i = 1; i <= n; ++i) {
        int id = a[i].c, pos = i;
        for (int j = i - 1; j >= std::max(i - a[i].a, 1); --j) {
            if (a[p[j]].c == id) pos = j;
            if (j > 1 && i - j <= a[i].a && a[p[j - 1]].c == id) pos = j;
        }
        a[i].p = pos;
        for (int j = 1; j < i; ++j) if (a[j].p >= pos) ++ a[j].p;
        for (int j = 1; j <= i; ++j) p[a[j].p] = j;
    }
    for (int i = 1; i <= n; ++i) printf("%d%c", p[i], " \n"[i == n]);
    return 0;
}