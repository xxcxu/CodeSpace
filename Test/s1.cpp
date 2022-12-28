#include<bits/stdc++.h>
using namespace std;
#define ll long long
inline ll read() {
	ll s = 0, w = 1;
	char ch = getchar();
	while (ch < '0' || ch > '9'){if (ch == '-') w = -1; ch = getchar();}
	while (ch >= '0' && ch <= '9'){s = (s << 3) + (s << 1) + (ch ^ 48); ch = getchar();}
	return s * w;
}
const int N = 310;
const ll INF = 1e18;
int n;
ll c[N][N], a[N];
bool check(int l, int r) {
	ll mx = -INF, mn = INF;
	for (int i = l; i <= r; i++) mx = max(mx, a[i]), mn = min(mn, a[i]);
	return mx - mn == c[l][r];
}
int main() {
	n = read();
	for (int i = 1; i <= n; i++)
		for (int j = i; j <= n; j++)
			c[i][j] = c[j][i] = read();
	a[1] = 0; a[2] = c[1][2];
	for (int i = 3; i <= n; i++) {
		a[i] = a[i - 1] + c[i - 1][i];
		bool f = 1;
		for (int j = i - 2; j >= 1; j--) f &= check(j, i);
		if (!f) a[i] -= c[i - 1][i] << 1;
	}
	for (int i = 1; i <= n; i++) printf("%lld ", a[i]);
	return 0;
}	