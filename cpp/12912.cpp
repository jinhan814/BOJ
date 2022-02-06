#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

using i64 = long long;
using pii = pair<int, i64>;
using tii = tuple<int, int, int>;

i64 n, mx;
vector<pii> adj[2000];
vector<tii> E;

i64 GetDiameter(int a, int b) {
	bitset<2000> visited; visited[b] = 1;
	auto DFS = [&](int cur, auto&& DFS) -> pii {
		pii ret{ cur, 0 }; visited[cur] = 1;
		for (const auto& [nxt, cost] : adj[cur]) {
			if (visited[nxt]) continue;
			auto [res, dist] = DFS(nxt, DFS);
			if (ret.second < dist + cost) ret = { res, dist + cost };
		}
		return ret;
	};
	auto res = DFS(a, DFS).first;
	visited.reset(), visited[b] = 1;
	return DFS(res, DFS).second;
}

int main() {
	fastio;
	cin >> n;
	for (int i = 1; i < n; i++) {
		int a, b, c; cin >> a >> b >> c;
		adj[a].push_back({ b, c });
		adj[b].push_back({ a, c });
		E.push_back({ a, b, c });
	}
	for (const auto& [a, b, c] : E) {
		auto d1 = GetDiameter(a, b);
		auto d2 = GetDiameter(b, a);
		mx = max(mx, d1 + c + d2);
	}
	cout << mx << '\n';
}