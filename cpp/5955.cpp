#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

constexpr int INF = 0x3f3f3f3f;
using pii = pair<int, int>;

int n, m, st, en, dist[301];
int Type[301], Bias[301], A[301], B[301];
vector<pii> adj[301];

bool GetType(int i, int t) {
	if (t < Bias[i]) return Type[i];
	t = (t - Bias[i]) % (A[i] + B[i]);
	if (Type[i]) return t >= A[i];
	else return t < B[i];
}

int GetCost(int a, int b, int t) { // C(a->b, t)
	for (int i = 0; i <= 500; i++)
		if (GetType(a, t + i) == GetType(b, t + i)) return i;
	return -1;
}

int Dijkstra() {
	memset(dist, 0x3f, sizeof dist);
	priority_queue<pii, vector<pii>, greater<>> PQ;
	PQ.push({ dist[st] = 0, st });
	while (PQ.size()) {
		const auto [cdist, cur] = PQ.top(); PQ.pop();
		if (dist[cur] != cdist) continue;
		for (const auto& [nxt, cost] : adj[cur]) {
			const int t = GetCost(cur, nxt, cdist);
			if (t == -1) continue;
			const auto ncost = cdist + cost + t;
			if (dist[nxt] > ncost) PQ.push({ dist[nxt] = ncost, nxt });
		}
	}
	return dist[en] == INF ? 0 : dist[en];
}

int main() {
	fastio;
	cin >> st >> en >> n >> m;
	for (int i = 1; i <= n; i++) {
		char c; cin >> c >> Bias[i];
		Type[i] = c == 'P';
		cin >> A[i] >> B[i];
	}
	for (int i = 1; i <= m; i++) {
		int a, b, c; cin >> a >> b >> c;
		adj[a].push_back({ b, c });
		adj[b].push_back({ a, c });
	}
	cout << Dijkstra() << '\n';
}