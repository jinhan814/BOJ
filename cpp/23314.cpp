#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

#define int int64_t

struct BCC { // vertex-disjoint BCC
	int n, m, dfs_cnt, color_cnt, art_point_cnt;
	vector<int> dfs_order, low, check, edge_color, visited;
	vector<vector<pair<int, int>>> adj;

	BCC(int n, int m) :
		n(n), m(m), adj(n + 1), visited(n + 1),
		dfs_order(n + 1), low(n + 1),
		check(n + 1), edge_color(m),
		dfs_cnt(0), color_cnt(0), art_point_cnt(0) {}

	void AddEdge(int a, int b, int idx) {
		adj[a].push_back({ b, idx });
		adj[b].push_back({ a, idx });
	}

	int DFS(int cur, bool IsRoot = 0) {
		int& ret = low[cur] = dfs_order[cur] = ++dfs_cnt, cnt = 0;
		for (const auto& [nxt, idx] : adj[cur]) {
			if (!dfs_order[nxt]) {
				const int t = DFS(nxt);
				if (t >= dfs_order[cur] && !IsRoot && !check[cur])
					check[cur] = ++art_point_cnt;
				ret = min(ret, t), cnt++;
			}
			else ret = min(ret, dfs_order[nxt]);
		}
		if (IsRoot) check[cur] = cnt > 1 ? ++art_point_cnt : 0;
		return ret;
	}

	void Color(int cur, int p_idx, int p = 0) {
		if (p) {
			edge_color[p_idx] = p;
			visited[cur] = 1;
		}
		for (const auto& [nxt, idx] : adj[cur]) {
			if (nxt == cur || visited[nxt]) {
				if (!edge_color[idx]) edge_color[idx] = p;
			}
			else if (low[nxt] >= dfs_order[cur]) {
				edge_color[idx] = ++color_cnt;
				visited[cur] = 1;
				Color(nxt, idx, color_cnt);
			}
			else Color(nxt, idx, p);
		}
	}

	void Init(bool flag = 0) { // suppose that graph is connected, no multi-edge, V >= 2
		DFS(1, 1); Color(1, 0);

		if (flag) {
			cout << "color :" << '\n';
			for (int i = 0; i < m; i++) cout << edge_color[i] << ' ';
			cout << '\n';
		}
	}
};

int32_t main() {
    fastio;
    int n, m, q; cin >> n >> m >> q;
	vector<tuple<int, int, int>> E(m);
	for (auto& [a, b, c] : E) {
		cin >> a >> b >> c;
		if (a > b) swap(a, b);
	}
	sort(E.begin(), E.end());

    BCC B(n, m);
	for (int i = 0; i < m; i++) {
		const auto& [a, b, c] = E[i];
		B.AddEdge(a, b, i);
	}
    B.Init();

	vector<multiset<int>> S(m + 1);
	vector<int> Sum(m + 1);
	for (int i = 0; i < m; i++) {
		S[B.edge_color[i]].insert(get<2>(E[i]));
		Sum[B.edge_color[i]] += get<2>(E[i]);
	}

	int res = 0;
	auto F = [&](int i) -> int {
		const int t = *prev(S[i].end());
		if (S[i].size() > 1 && t > 0) return Sum[i] - t;
		return Sum[i];
	};
	for (int i = 1; i <= m; i++) if (S[i].size()) res += F(i);
	cout << res << '\n';

	while (q--) {
		int a, b, c; cin >> a >> b >> c;
		if (a > b) swap(a, b);
		const int idx = lower_bound(E.begin(), E.end(), tuple<int, int, int>{ a, b, -1e9 }) - E.begin();
		const int color = B.edge_color[idx];
		res -= F(color);
		S[color].erase(S[color].find(get<2>(E[idx]))); Sum[color] -= get<2>(E[idx]);
		S[color].insert(c); Sum[color] += c; E[idx] = { a, b, c };
		cout << (res += F(color)) << '\n';
	}
}