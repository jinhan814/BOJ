#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

using ll = long long;

constexpr ll INF = ll(1e18) + 7;

// reference : https://github.com/justiceHui/icpc-teamnote
vector<int> DominatorTree(const vector<vector<int>>& g, int src) { // 0-based
	const int n = g.size();
	vector<vector<int>> rg(n), buf(n);
	vector<int> r(n), val(n), idom(n, -1), sdom(n, -1), par(n), u(n), o;
	iota(r.begin(), r.end(), 0), iota(val.begin(), val.end(), 0);
	for (int i = 0; i < n; i++) for (auto j : g[i]) rg[j].push_back(i);
	auto Find = [&](int v, auto&& Find) -> int {
		if (v == r[v]) return v;
		int ret = Find(r[v], Find);
		if (sdom[val[v]] > sdom[val[r[v]]]) val[v] = val[r[v]];
		return r[v] = ret;
	};
	auto DFS = [&](int v, auto&& DFS) -> void {
		sdom[v] = o.size(); o.push_back(v);
		for (auto i : g[v]) if (sdom[i] == -1) par[i] = v, DFS(i, DFS);
	};
	DFS(src, DFS), reverse(o.begin(), o.end());
	for (auto& i : o) {
		if (sdom[i] == -1) continue;
		for (auto j : rg[i]) {
			if (sdom[j] == -1) continue;
			int x = val[Find(j, Find), j];
			if (sdom[i] > sdom[x]) sdom[i] = sdom[x];
		}
		buf[o[o.size() - sdom[i] - 1]].push_back(i);
		for (auto j : buf[par[i]]) u[j] = val[Find(j, Find), j];
		buf[par[i]].clear();
		r[i] = par[i];
	}
	idom[src] = src, reverse(o.begin(), o.end());
	for (auto i : o) { // WARNING : if different, takes idom
		if (i != src) idom[i] = sdom[i] == sdom[u[i]] ? sdom[i] : idom[u[i]];
	}
	for (auto i : o) if (i != src) idom[i] = o[idom[i]];
	return idom; // unreachable -> ret[i] = -1
}

struct Edge { int a, b, cost; };

template<typename G>
vector<ll> Dijkstra(const G& adj, const int n, const int st) {
	vector<ll> dist(n, INF);
	priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<>> PQ;
	PQ.push({ dist[st] = 0, st });
	while (PQ.size()) {
		auto [cdist, cur] = PQ.top(); PQ.pop();
		if (dist[cur] != cdist) continue;
		for (const auto& [nxt, cost] : adj[cur]) {
			if (dist[nxt] > cdist + cost)
				PQ.push({ dist[nxt] = cdist + cost, nxt });
		}
	}
	return dist;
}

int main() {
	fastio;
	int n, m; cin >> n >> m;
	vector<vector<pair<int, int>>> adj(n);
	vector<Edge> E(m);
	for (auto& [a, b, cost] : E) {
		cin >> a >> b >> cost; --a, --b;
		adj[a].push_back({ b, cost });
		adj[b].push_back({ a, cost });
	}

	auto dist = Dijkstra(adj, n, 0);
	vector<vector<int>> dag(n);
	for (auto& [a, b, cost] : E) {
		if (dist[a] > dist[b]) swap(a, b);
		if (dist[a] + cost == dist[b]) dag[a].push_back(b);
	}

	auto idom = DominatorTree(dag, 0);
	vector<vector<int>> DT(n);
	for (int i = 1; i < n; i++) DT[idom[i]].push_back(i);
	vector<int> sz(n, 1);
	auto DFS = [&](int cur, auto&& DFS) -> int {
		for (const auto& nxt : DT[cur]) sz[cur] += DFS(nxt, DFS);
		return sz[cur];
	};
	DFS(0, DFS);
	for (const auto& [a, b, cost] : E) {
		if (idom[b] != a) cout << 0 << '\n';
		else cout << sz[b] << '\n';
	}
}