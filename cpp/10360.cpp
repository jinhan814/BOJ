#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

constexpr int INF = 1e9 + 7;

int main() {
	fastio;
	int N; cin >> N;
	for (int c = 1; c <= N; c++) {
		int n, m; cin >> n >> m;
		vector<vector<pair<int, int>>> adj(n);
		vector<vector<int>> rev(n);
		while (m--) {
			int a, b, c; cin >> a >> b >> c;
			adj[a].push_back({ b, c });
			rev[b].push_back(a);
		}

		vector<int> dist(n, INF), check(n); dist[0] = 0;
		for (int cnt = 0; cnt <= n; cnt++) {
			bool flag = 0;
			for (int i = 0; i < n; i++) if (dist[i] != INF) for (const auto& [j, cost] : adj[i]) {
				if (dist[j] > dist[i] + cost) {
					dist[j] = dist[i] + cost, flag = 1;
					if (cnt == n) check[j] = 1;
				}
			}
			if (!flag) break;
		}

		vector<bool> visited(n); visited[0] = 1;
		queue<int> Q; Q.push(0);
		while (Q.size()) {
			auto cur = Q.front(); Q.pop();
			for (const auto& nxt : rev[cur])
				if (!visited[nxt]) Q.push(nxt), visited[nxt] = 1;
		}

		bool flag = 0;
		for (int i = 0; i < n; i++) if (visited[i] && check[i]) flag = 1;
		cout << "Case #" << c << ": " << (flag ? "possible" : "not possible") << '\n';
	}
}