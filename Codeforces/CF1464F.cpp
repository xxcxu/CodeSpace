#include<bits/stdc++.h>
#define eb emplace_back
using pii = std::pair<int, int>;
static constexpr int N = 2e5 + 5, inf = 1e9;
int n, q, cnt;
int dep[N], l[N], r[N], qu[N];
int anc[N][25];
std::vector<int> e[N];
std::multiset<pii> s;
class path{public: int x, y;};
int lca(int x, int y) {
	if (dep[x] < dep[y]) std::swap(x, y);
	for (int i = 20; ~i; --i)
		if (dep[anc[x][i]] >= dep[y])
			x = anc[x][i];
	if (x == y) return x;
	for (int i = 20; ~i; --i)
		if (anc[x][i] != anc[y][i])
			x = anc[x][i], y = anc[y][i];
	return anc[x][0];
}
int dis(int x, int y) {
	if (x < 0 || y < 0) return -inf;
	return dep[x] + dep[y] - 2 * dep[lca(x, y)];
}
path operator + (path a, path b) {
	int x = -1, y = -1, d = -inf;
	auto check = [&](int a, int b) -> void {
		int dd = dis(a, b);
		if (dd > d) d = dd, x = a, y = b;
	};
	check(a.x, a.y); check(b.x, b.y);
	check(a.x, b.x); check(a.x, b.y);
	check(a.y, b.x); check(a.y, b.y);
	return (path){x, y};
}
void dfs(int x, int pre) {
	static int time_stamp = 0;
	l[x] = ++ time_stamp;
	qu[time_stamp] = x;
	dep[x] = dep[pre] + 1;
	anc[x][0] = pre;
	for (int i = 1; i <= 20; ++i) anc[x][i] = anc[anc[x][i - 1]][i - 1];
	for (auto &y : e[x]) {
		if (y == pre) continue;
		dfs(y, x);
	}
	r[x] = time_stamp;
}
class TreeArray {
	#define lowbit(x) ((x)&(-x))
	private: int s[N];
	public: void add(int x, int v) {for (; x <= n; x += lowbit(x)) s[x] += v;}
	public: int query(int x) {int ans = 0; for (; x; x -= lowbit(x)) ans += s[x]; return ans;}
	public: int query(int l, int r) {return query(r) - query(l - 1);}
} tree1;
class SegmentTree {
	#define ls (rt << 1)
	#define rs (rt << 1 | 1)
	private: int sum[N];
	private: path tr[N << 2];
	public: void pushup(int rt) {tr[rt] = tr[ls] + tr[rs];}
	public: void build(int rt, int l, int r) {
		tr[rt] = (path){-1, -1};
		if (l == r) return;
		int mid = (l + r) >> 1;
		build(ls, l, mid); build(rs, mid + 1, r); 
	}
	public: void update(int rt, int l, int r, int x, int opt) {
		if (l == r) {
			if (opt == 1) tr[x] = (path){qu[l], qu[l]};
			else tr[x] = (path){-1, -1};
			return; 
		} 
		int mid = (l + r) >> 1;
		x <= mid ? (update(ls, l, mid, x, opt), 0) : (update(rs, mid + 1, r, x, opt), 0);
		pushup(rt);
	}
	public: path query(int rt, int l, int r, int L, int R) {
		if (l == r) return tr[rt];
		int mid = (l + r) >> 1;
		path ans = (path){-1, -1};
		if (L <= mid) ans = ans + query(ls, l, mid, L, R);
		else ans = ans + query(rs, mid + 1, r, L, R);
		return ans;
	}
	public: void add(int x) {if (!sum[x]) update(1, 1, n, l[x], 1); ++ sum[x];}
	public: void del(int x) {if (sum[x] == 1) update(1, 1, n, l[x], -1); -- sum[x];}
} tree2;
int jump(int x, int d) {
	if (dep[x] <= d) return 1;
	for (int i = 20; ~i; --i)
		if ((1 << i) <= d) d -= (1 << i), x = anc[x][i];
	return x;
}
int ask(int d) {
	int x = jump(s.rbegin() -> second, d);
	int u = jump(x, d);
	if (tree1.query(l[u], r[u]) != cnt) return false;
	path p = tree2.query(1, 1, n, l[u], r[u]);
	printf("%d %d\n", p.x, p.y);
	if (dis(x, p.x) <= d && dis(x, p.y) <= d) return true;
	return false;
}
signed main() {
	scanf("%d%d", &n, &q);
	for (int i = 1, u, v; i < n; ++i) {
		scanf("%d%d", &u, &v);
		e[u].eb(v); e[v].eb(u);
	}
	dfs(1, 0); tree2.build(1, 1, n);
	for (int i = 1; i <= q; ++i) {
		static int opt;
		scanf("%d", &opt);
		if (opt == 1) {
			static int u, v;
			scanf("%d%d", &u, &v);
			int L = lca(u, v);
			tree1.add(l[u], 1);
			tree1.add(l[v], 1);
			tree1.add(l[L], -1);
			tree2.add(L);
			++ cnt;
			s.emplace(dep[L], L);
		}
		if (opt == 2) {
			static int u, v;
			scanf("%d%d", &u, &v);
			int L = lca(u, v);
			tree1.add(l[u], -1);
			tree1.add(l[v], -1);
			tree1.add(l[L], 1);
			tree2.del(L);
			-- cnt;
			s.erase(s.find(pii(dep[L], L)));
		}
		if (opt == 3) {
			static int d;
			scanf("%d", &d);
			puts(ask(d) ? "Yes" : "No");
		}
	} return 0;
}