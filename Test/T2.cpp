#include <bits/stdc++.h>
using namespace std;
inline int read() {
	int x = 0, f = 1; char c = getchar();
	while (c < '0' || c > '9') {if (c == '-') f = -f; c = getchar();}
	while (c >= '0' && c <= '9') {x = (x << 3) + (x << 1) + (c ^ 48); c = getchar();}
	return x * f;
}
const int N = 1e5 + 5, M = 5e6 + 5;
int n;
int chk[M], a[N];
vector <int> prime, t[4];
inline void xxs(int m) {
	t[1].push_back(1);
	for (int i = 2; i <= m; i++) {
		if (!chk[i]) {
			prime.push_back(i);
			t[i % 4].push_back(i);
		}
		for (int p : prime) {
			if (p * i > m) break;
			chk[i * p] = 1;
			if (i % p == 0) break;
		}
	}
}
inline int calc(int x) {
	if (!chk[x]) return 1;
	if (x % 2 == 0) return x / 2;
	int w = *(--upper_bound(t[x % 4].begin(), t[x % 4].end(), x));
	return (x - w >> 1) + 1;
}
inline void Solve() {
	n = read(); int A = 1e9, B = 1e9;
	for (int i = 1; i <= n; i++) a[i] = read();
	for (int i = 1; i <= n; i++) {
		if (a[i] % 4 == 0) B = min(B, a[i] >> 1);
		else A = min(A, calc(a[i]));
	}
	bool ans = A <= B;
	for (int i = 1; i <= n; i++) {
		if (a[i] % 4 == 0) {if ((a[i] >> 1) == B) break;}
		else if (calc(a[i]) == B + 1) {ans = true; break;}
	}
	puts(ans ? "Farmer John" : "Farmer Nhoj");
}
int main() {
//	freopen(".in", "r", stdin);
//	freopen(".out", "w", stdout);
	xxs(5e6); int _ = read();
	while (_--) Solve();
	return 0;
}
