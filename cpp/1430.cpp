#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

using pii = pair<int, int>;
int n, m, k, dist[101];
vector<pii> v;
vector<int> adj[101];

int GetDist(const pii& a, const pii& b) {
	return (a.first - b.first) * (a.first - b.first)
		 + (a.second - b.second) * (a.second - b.second);
}

int main() {
	fastio;
	cin >> n >> m >> k;
	v.resize(n + 1);
	for (auto& [a, b] : v) cin >> a >> b;

	for (int i = 0; i <= n; i++) for (int j = 0; j <= n; j++) {
		if (i == j) continue;
		if (GetDist(v[i], v[j]) <= m * m) adj[i].push_back(j);
	}

	queue<int> Q;
	Q.push(0), dist[0] = 1;
	while (Q.size()) {
		auto cur = Q.front(); Q.pop();
		for (const auto& nxt : adj[cur]) {
			if (dist[nxt]) continue;
			Q.push(nxt), dist[nxt] = dist[cur] + 1;
		}
	}

	double ans = 0;
	for (int i = 1; i <= n; i++)
        if (dist[i]) ans += k / pow(2, dist[i] - 2);
	cout << fixed << setprecision(2) << ans << '\n';
}