#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

struct Info {
    int x, y, idx;
    bool operator< (const Info& i) const {
        return x < i.x || x == i.x && y < i.y;
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
    for (int i = 0, j = 0; i < n; i = j) {
        int t = v[i].y;
        while (j < n && v[j].x <= t) UF.Union(v[i].idx, v[j].idx), t = max(t, v[j++].y);
    }
    for (int i = 0, j = 0; i < n; i = j) {
        int t = w[i].y;
        while (j < n && w[j].x <= t) UF.Union(w[i].idx, w[j].idx), t = max(t, w[j++].y);
    }
    while (q--) {
        int a, b; cin >> a >> b; --a, --b;
        cout << (UF.Find(a) == UF.Find(b)) << '\n';
    }
}