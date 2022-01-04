#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

struct Info {
    int a, b, idx;
    bool operator< (const Info& i) const {
        return b < i.b || b == i.b && a < i.a;
    }
};

struct UnionFind { // -1 ver.
    vector<int> par;
    UnionFind(int n) : par(n, -1) {}
    int Find(int x) { return par[x] < 0 ? x : par[x] = Find(par[x]); }
    void Union(int a, int b) {
        a = Find(a), b = Find(b);
        if (a ^ b) par[a] += par[b], par[b] = a;
    }
    int Cnt(int x) { return -par[Find(x)]; }
};

int main() {
	fastio;
	int n, q; cin >> n >> q;
    vector<Info> v(n), w(n); UnionFind UF(n);
	for (int i = 0; i < n; i++) {
        auto& [x1, x2, i1] = v[i];
        auto& [y1, y2, i2] = w[i];
        cin >> x1 >> y1 >> x2 >> y2, i1 = i2 = i;
        if (x1 > x2) swap(x1, x2);
        if (y1 > y2) swap(y1, y2);
	}
    sort(v.begin(), v.end()), sort(w.begin(), w.end());
    for (int i = 1; i < n; i++) {
        if (v[i].a <= v[i - 1].b) UF.Union(v[i - 1].idx, v[i].idx);
        if (w[i].a <= w[i - 1].b) UF.Union(w[i - 1].idx, w[i].idx);
    }
    while (q--) {
        int a, b; cin >> a >> b; --a, --b;
        cout << (UF.Find(a) == UF.Find(b)) << '\n';
    }
}