#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

struct Edge { int a, b, cost; };

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

int n, m, t1, t2, cnt, v[100'001];
vector<Edge> E;
UnionFind UF(100'001);

int main() {
	fastio;
	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		cin >> v[i];
		if (v[i] == i) {
			if (t2) UF.Union(t2, i);
			t2 = i;
		}
		else t1 = i, cnt++;
	}
	if (!cnt) return !(cout << -1 << '\n');

	while (m--) {
		int a, b, c; cin >> a >> b >> c;
		E.push_back({ a, b, c });
	}

	sort(E.begin(), E.end(), [](const Edge& a, const Edge& b) {
		return a.cost > b.cost;
	});

	for (auto& [a, b, cost] : E) {
		UF.Union(a, b);
		if ((!t2 || UF.Find(t1) != UF.Find(t2)) && UF.Cnt(t1) == cnt || UF.Cnt(t1) == n) {
			cout << cost << '\n';
			break;
		}
	}
}