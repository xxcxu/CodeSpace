

#include <bits/stdc++.h>
#define int long long
template<typename T>
void read(T &x) {
    x = 0; bool f = false; char ch = getchar();
    for (; !isdigit(ch); ch = getchar()) f ^= (ch == '-');
    for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ 48);
    x = f ? ~x + 1 : x;
}
template<typename T, typename ...Args>
void read(T &x, Args &...args) {read(x); read(args...);}
using pii = std::pair<int, int>;
const int N = 1e5 + 5;
int n, m, k, cnt, ans = LONG_LONG_MAX, pos[N], vis[N], head[N], dis[21][N];
struct Edge {int from, to, link, next;} e[N << 2];
void Add(int u, int v, int w) {e[++ cnt] = {u, v, w, head[u]}; head[u] = cnt;}
void Dijkstra(int *dis, int s) {
    std::priority_queue<pii, std::vector<pii>, std::greater<pii>> q;
    std::fill(dis + 1, dis + n + 1, 1e18);
    std::memset(vis, 0, sizeof vis); q.emplace(pii(dis[s] = 0, s));
    while (q.size()) {
        int x = q.top().second; q.pop();
        if (vis[x]) continue; vis[x] = true;
        for (int i = head[x]; i; i = e[i].next)
            if (dis[e[i].to] > dis[x] + e[i].link) 
				dis[e[i].to] = dis[x] + e[i].link, q.emplace(dis[e[i].to], e[i].to);
    } return void();
}

signed main() {
    read(n, m);
    for (int i = 1, u, v, w; i <= m; ++i) read(u, v, w), Add(u, v, w), Add(v, u, w);
    read(k); pos[0] = 1;
    for (int i = 1; i <= k; ++i) read(pos[i]);
    for (int i = 0; i <= k; ++i) Dijkstra(dis[i], pos[i]);
    std::vector<int> p;
	for (int i = 0; i <= k; ++i) p.emplace_back(i);
	for (int i = 1; i <= m * 2; i += 2) {
		int u = e[i].from, v = e[i].to;
		std::sort(p.begin(), p.end(), [&](int a, int b) {return dis[a][u] < dis[b][u];});
		int R = -1e18;
		for (int j = k; ~j; --j) {
			if (dis[p[j]][u] >= e[i].link + R) ans = std::min(ans, dis[p[j]][u] * 2);
			else if (R >= dis[p[j]][u] + e[i].link) ans = std::min(ans, R * 2);
			else ans = std::min(ans, dis[p[j]][u] + e[i].link + R);
			R = std::max(R, dis[p[j]][v]);
		} ans = std::min(ans, R * 2);
	} return printf("%lld\n", ans), 0; 
}

