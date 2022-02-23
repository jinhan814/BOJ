#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int n, m, dep[100'001];
vector<int> adj[100'001];
bitset<100'001> visited;
vector<tuple<int, int, int>> res;

void DFS(int cur) {
	visited[cur] = 1;
	for (const auto& nxt : adj[cur]) if (!visited[nxt]) {
		dep[nxt] = dep[cur] + 1;
		DFS(nxt);
	}
}

bool Sol(int cur, int prv) {
	int cand = visited[cur] = 0;
	for (const auto& nxt : adj[cur]) {
		if (nxt == prv) continue;
		if (dep[nxt] < dep[cur] ||           // back edge
			visited[nxt] && Sol(nxt, cur)) { // tree edge
			if (cand) res.push_back({ cand, cur, nxt }), cand = 0;
			else cand = nxt;
		}
	}
	if (cand && prv != -1) {
		res.push_back({ cand, cur, prv });
		return 0;
	}
	return 1;
}

int main() {
	fastio;
	cin >> n >> m; res.reserve(m / 2);
	while (m--) {
		int a, b; cin >> a >> b;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	for (int i = 1; i <= n; i++) if (!dep[i]) {
		dep[i] = 1, DFS(i), Sol(i, -1);
	}
	cout << res.size() << '\n';
	for (const auto& [a, b, c] : res) {
		cout << a << ' ' << b << ' ' << c << '\n';
	}
}