#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

constexpr int INF = 1e9 + 7;
using tii = tuple<int, int, int>;

struct UnionFind {
	vector<int> par;
	UnionFind(int n) : par(n, -1) {}
	int Find(int x) { return par[x] < 0 ? x : par[x] = Find(par[x]); }
	void Union(int a, int b) {
		a = Find(a), b = Find(b);
		if (a ^ b) par[a] += par[b], par[b] = a;
	}
	int Cnt(int x) { return -par[Find(x)]; }
};

int Dijkstra(const vector<string>& v, UnionFind& UF) {
	const int n = v.size();
	priority_queue<tii, vector<tii>, greater<>> PQ;
	vector<vector<int>> dist(n, vector<int>(n, INF));
	for (int x = 1; x < n; x++) PQ.push({ dist[x][0] = UF.Cnt(x * n + 0), x, 0 });
	for (int y = 1; y < n - 1; y++) PQ.push({ dist[n - 1][y] = UF.Cnt((n - 1) * n + y), n - 1, y });
	while (PQ.size()) {
		auto [cdist, x, y] = PQ.top(); PQ.pop();
		if (dist[x][y] != cdist) continue;
		if (x == 0 || y == n - 1) return cdist;
		for (int d = 0; d < 8; d++) {
			const int nx = x + "10001222"[d] - '1';
			const int ny = y + "22100012"[d] - '1';
			if (nx < 0 || nx >= n || ny < 0 || ny >= n) continue;
			if (v[nx][ny] == '.') continue;
			const int cost = UF.Find(x * n + y) != UF.Find(nx * n + ny) ? UF.Cnt(nx * n + ny) : 0;
			if (dist[nx][ny] > cdist + cost) PQ.push({ dist[nx][ny] = cdist + cost, nx, ny });
		}
	}
}

int main() {
	fastio;
	int n; cin >> n;
	vector<string> v(n);
	UnionFind UF(n * n);
	for (int i = 0; i < n; i++) cin >> v[i];
	for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) for (int d = 0; d < 4; d++) {
		const int nx = i + "1012"[d] - '1';
		const int ny = j + "2101"[d] - '1';
		if (nx < 0 || nx >= n || ny < 0 || ny >= n) continue;
		if (v[i][j] == v[nx][ny]) UF.Union(i * n + j, nx * n + ny);
	}
	cout << Dijkstra(v, UF) << '\n';
}