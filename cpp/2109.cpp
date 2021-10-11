#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

struct UnionFind { // -1 ver.
    vector<int> par;
    UnionFind(int n) : par(n, -1) {}
    int Find(int x) { return par[x] < 0 ? x : par[x] = Find(par[x]); }
    void Union(int a, int b) {
        a = Find(a), b = Find(b);
        if (a > b) swap(a, b);
        if (a ^ b) par[a] += par[b], par[b] = a;
    }
    int Cnt(int x) { return -par[Find(x)]; }
};

int main() {
	fastio;
	int n, ans = 0; cin >> n;
	vector<pair<int, int>> v(n);
	for (auto& [a, b] : v) cin >> a >> b;
	sort(v.rbegin(), v.rend());

    UnionFind UF(10'001);
    for (const auto& [val, t] : v) {
        const int pos = UF.Find(t);
        if (pos == 0) continue;
        ans += val, UF.Union(pos - 1, pos);
    }
    cout << ans << '\n';
}