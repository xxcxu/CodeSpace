#include <bits/stdc++.h>

template<typename T>
void read(T &x) {
    x = 0; bool f = false; char ch = getchar();
    for (; !isdigit(ch); ch = getchar()) f ^= (ch == '-');
    for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ 48);
    x = f ? ~x + 1 : x;
}


template<typename T, typename ...Args>
void read(T &x, Args &...args) {
    read(x); read(args...);
}

const int N = 5e5 + 5, mod = 1e9 + 7;

int n, m, cnt, ans;
int fa[N], last[N], tree[N];
struct edge {int fr, to, next, w; friend bool operator < (const edge a, const edge b) {return a.w < b.w;}}e[N << 1];

int find(int x) {return x == fa[x] ? x : fa[x] = find(fa[x]);}

void add(int x, int y, int z) {e[++ cnt] = (edge){x, y, last[x], z}; return void();}

int qpow(int x, int y, int mod) {
    int ans = 1;
    for (; y; y >>= 1, x = 1ll * x * x % mod)
        if (y & 1) ans = 1ll * ans * x % mod;
    return ans % mod;
}

void kruskal() {
    std::sort(e + 1, e + 2 * m + 1);
    for (int i = 1; i <= 2 * m; ++i) {
        int u = find(e[i].fr), v = find(e[i].to);
        if (u ^ v) {
            tree[i] = true;
            fa[u] = v;
            ans = (ans + qpow(2, e[i].w, mod)) % mod;
        }
    } return void();
}

signed main() {
    read(n, m);
    for (int i = 1, u, v; i <= m; ++i) {
        read(u, v);
        add(u, v, i);
        add(v, u, i);
    } kruskal();
    return 0;
}