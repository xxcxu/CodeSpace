#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#define eb emplace_back
static constexpr int N = 1005;
int n, m, a[N], b[N], cnt[N];
int map[N], id[N];
std::vector<int> pos1[N], pos2[N], value;
void clear() {
    value.clear();
    for (int i = 1; i <= 1000; ++i) pos1[i].clear(), pos2[i].clear();
    std::memset(cnt, 0, sizeof cnt);
    std::memset(map, 0, sizeof map);
    return void();
}
void solve() {
    clear();
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i) scanf("%d", a + i);
    for (int i = 1; i <= n; ++i) scanf("%d", b + i);
    for (int i = 1; i <= n; ++i) {
        if (!cnt[a[i]]) value.eb(a[i]);
        ++ cnt[a[i]];
        pos1[a[i]].eb(i);
    }
    for (int i = 1; i <= n; ++i) {
        -- cnt[b[i]];
        pos2[b[i]].eb(i);
    }
    bool flag = true;
    for (int i = 1; i <= 1000; ++i) if (cnt[i]) flag = false;
    if (!flag) {
        for (int i = 1; i <= m; ++i) scanf("%*%*");
        return puts("NIE"), void();
    }
    for (int w : value)
        for (int i = 0; i < (int)pos1[w].size(); ++i)
            map[(int)pos1[w][i]] = (int)pos2[w][i];
    for (int i = 1; i <= n; ++i) id[i] = i;
    for (int i = 1; i <= m; ++i) {
        static int l, r;
        std::sort(id + l, id + r + 1, [&](int x, int y) {return map[x] < map[y];});
    }
    for (int i = 1; i <= n; ++i) flag &= a[id[i]] == b[i];
    return puts(flag ? "TAK" : "NIE"), void();
}
signed main() {
	freopen("ball.in", "r", stdin);
	freopen("ball.out", "w", stdout);
    int t; scanf("%d", &t);
    while (t--) solve();
    return 0;
}