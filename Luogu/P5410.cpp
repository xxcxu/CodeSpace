#include <bits/stdc++.h>
using ll = long long;
static constexpr int N = 2e7 + 5;
int n, m; ll ans;
char str[N], substr[N];
class Exkmp {
    private: int n;
    private: char str[N];
    public: int z[N], p[N];
    public: Exkmp(): n(0) {}
    public: Exkmp(int nn, char *s): n(nn) {
        z[1] = nn;
        std::memcpy(str, s, sizeof s);
    }
    public: auto InitZ(char *s, int n) -> void {
        *this = Exkmp(n, s);
        for (int i = 2, l = 0, r = 0; i <= n; ++i) {
            if (i <= r) z[i] = std::min(z[i - l + 1], r - i + 1);
            while (i + z[i] <= n && s[i + z[i]] == s[z[i] + 1]) ++ z[i];
            if (i + z[i] - 1 > r) l = i, r = i + z[i] - 1;
        } return;
    }
    public: auto Match(char *t, int m) -> void {
        for (int i = 1, l = 0, r = 0; i <= n; ++i) {
            if (i <= r) p[i] = std::min(z[i - l + 1], r - i + 1);
            while (i + p[i] <= n && str[i + p[i]] == t[p[i] + 1]) ++ p[i];
            if (i + p[i] - 1 > r) l = i, r = i + p[i] - 1;
        } return;
    }
} LCP;
auto main() -> decltype(0) {
    scanf("%s%s", str + 1, substr + 1);
    n = strlen(str + 1), m = strlen(substr + 1);
    LCP.InitZ(substr, m); LCP.Match(str, n);
    for (int i = 1; i <= m; ++i) ans ^= (1ll * i * (LCP.z[i] + 1));
    printf("%lld\n", ans);
    ans = 0;
    for (int i = 1; i <= n; ++i) ans ^= (1ll * i * (LCP.p[i] + 1));
    printf("%lld\n", ans);
    return 0;
}