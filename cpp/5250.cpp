#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

#define int int64_t
constexpr int INF = 0x3f3f3f3f3f3f3f3f;
using pii = pair<int, int>;

int n, m, st, en, k, v[2001], inv[2001];
int par[2001], dist1[2001], dist2[2001];
int dep[2001], lca[2001];
vector<pii> adj[2001];
vector<int> adj2[2001];

template<size_t sz>
struct SegTree {
	vector<int> tree, lazy;
	SegTree() : tree(sz << 1, INF), lazy(sz << 1, INF) {}
	void push(int node, int L, int R) {
		if (node < sz) for (const int nxt : { node << 1, node << 1 | 1 }) lazy[nxt] = min(lazy[nxt], lazy[node]);
		tree[node] = min(tree[node], lazy[node]), lazy[node] = INF;
	}
	void update(int l, int r, int val, int node = 1, int L = 1, int R = sz) {
		push(node, L, R);
		if (r < L || R < l) return;
		if (l <= L && R <= r) { lazy[node] = min(lazy[node], val), push(node, L, R); return; }
		int mid = L + R >> 1;
		update(l, r, val, node << 1, L, mid);
		update(l, r, val, node << 1 | 1, mid + 1, R);
		tree[node] = min(tree[node << 1], tree[node << 1 | 1]);
	}
	int query(int l, int r, int node = 1, int L = 1, int R = sz) {
		push(node, L, R);
		if (r < L || R < l) return INF;
		if (l <= L && R <= r) return tree[node];
		int mid = L + R >> 1;
		return min(query(l, r, node << 1, L, mid), query(l, r, node << 1 | 1, mid + 1, R));
	}
};

void Dijkstra(int dist[], int st) {
	memset(dist + 1, 0x3f, n << 3);
	priority_queue<pii, vector<pii>, greater<pii>> PQ;
	PQ.push({ dist[st] = 0, st });
	while (PQ.size()) {
		auto [cdist, cur] = PQ.top(); PQ.pop();
		if (dist[cur] != cdist) continue;
		for (const auto& [nxt, cost] : adj[cur]) {
			if (dist[nxt] > cdist + cost) {
				par[nxt] = cur;
				PQ.push({ dist[nxt] = cdist + cost, nxt });
			}
		}
	}
}

void DFS(int cur, int prv, int t) {
    if (inv[cur]) t = cur; lca[cur] = t;
	dep[cur] = dep[prv] + 1;
	for (const auto& nxt : adj2[cur]) {
		if (nxt == prv) continue;
		DFS(nxt, cur, t);
	}
}

int32_t main() {
    fastio;
    cin >> n >> m >> st >> en;
	for (int i = 0; i < m; i++) {
        int a, b, c; cin >> a >> b >> c;
		adj[a].push_back({ b, c });
		adj[b].push_back({ a, c });
	}
	cin >> k;
	for (int i = 1; i <= k; i++) cin >> v[i], inv[v[i]] = i;

	Dijkstra(dist2, en); Dijkstra(dist1, st);
	for (int i = 2; i <= k; i++) par[v[i]] = v[i - 1];
	par[st] = st;

	for (int i = 1; i <= n; i++) adj2[par[i]].push_back(i);
	DFS(st, 0, st);

	SegTree<1 << 12> ST;
	for (int i = 1; i <= n; i++) for (const auto& [j, cost] : adj[i]) {
		if (par[i] == j || par[j] == i) continue;
		const int t1 = inv[lca[i]];
		const int t2 = inv[lca[j]];
		ST.update(t1, t2 - 1, dist1[i] + cost + dist2[j]);
	}
	for (int i = 1; i < k; i++) {
		const int ans = ST.query(i, i);
		cout << (ans == INF ? -1 : ans) << '\n';
	}
}