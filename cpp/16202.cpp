#include<bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

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

int n, m, k, check[10001];
vector<tuple<int, int, int>> E;

int MST() {
	int ret = 0, cnt = 0, st = -1; UnionFind UF(n + 1);
	for (const auto& [i, a, b] : E) {
		if (check[i] || UF.Find(a) == UF.Find(b)) continue;
		if (st == -1) st = i;
		UF.Union(a, b), ret += i, cnt++;
	}
	if (cnt < n - 1) return 0;
	return check[st] = 1, ret;
}

int main() {
	fastio;
	cin >> n >> m >> k;
	for (int i = 1; i <= m; i++) {
		int a, b; cin >> a >> b;
		E.push_back({ i, a, b });
	}
	sort(E.begin(), E.end());
	for (int i = 1; i <= k; i++) cout << MST() << ' ';
	cout << '\n';
}