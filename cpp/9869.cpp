#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

using pii = pair<int, int>;

struct UnionFind {
    vector<int> par;
    UnionFind(int n) : par(n) { iota(par.begin(), par.end(), 0); }
    int Find(int x) { return x == par[x] ? x : par[x] = Find(par[x]); }
    void Union(int a, int b) { a = Find(a), b = Find(b); if (a > b) swap(a, b); par[b] = a; }
};

int main() {
    fastio;
    int n, ans = 0; cin >> n;
    vector<pii> v(n);
    for (int i = 0; i < n; i++) cin >> v[i].first >> v[i].second;
    sort(v.rbegin(), v.rend());

    UnionFind UF(10'001);
    for (auto& [a, b] : v) {
        int t = UF.Find(b);
        if (t) ans += b, UF.Union(t, t - 1);
    }
    cout << ans << '\n';
}