#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

using i64 = long long;
using pii = pair<i64, int>;

int n, en;
bitset<1000> check;
int adj[1000][1000];
i64 dist[1000];

void Dijkstra() {
	memset(dist, 0x3f, sizeof dist);
	priority_queue<pii, vector<pii>, greater<>> PQ;
	PQ.push({ dist[0] = 0, 0 });
	while (PQ.size()) {
		auto [cdist, cur] = PQ.top(); PQ.pop();
		if (dist[cur] != cdist) continue;
		for (int nxt = 0; nxt < n; nxt++) {
			if (!adj[cur][nxt]) continue;
			const i64 cost = (i64(check[cur] != check[nxt]) << 32) + adj[cur][nxt];
			if (dist[nxt] > cdist + cost) PQ.push({ dist[nxt] = cdist + cost, nxt });
		}
	}
}

int main() {
	fastio;
	cin >> n >> en;
	for (int i = 0; i < n; i++) {
		int t; cin >> t;
		if (t) check[i] = 1;
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
			cin >> adj[i][j];
	}
	Dijkstra();
	cout << (dist[en] >> 32) << ' ';
	cout << (dist[en] & (1LL << 32) - 1) << '\n';
}