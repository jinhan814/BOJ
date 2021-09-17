#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int n, dist[200'001], cdist[200'001];
vector<int> adj[200'001];

bool Check(int mid) {
	queue<int> Q; memset(cdist + 1, -1, n << 2);
	for (int i = 1; i <= n; i++) {
		if (dist[i] >= mid) cdist[i] = 0, Q.push(i);
	}
	while (Q.size()) {
		auto cur = Q.front(); Q.pop();
		for (const auto& nxt : adj[cur]) {
			if (!~cdist[nxt]) cdist[nxt] = cdist[cur] + 1, Q.push(nxt);
		}
	}
	for (int i = 1; i <= n; i++) {
		if (!dist[i] && cdist[i] < mid) return 0;
		if (dist[i] && cdist[i] >= mid) return 0;
	}
	return 1;
}

int main() {
	fastio;
	cin >> n;
	queue<int> Q; memset(dist + 1, -1, n << 2);
	for (int i = 1; i <= n; i++) {
		char c; cin >> c;
		if (~c & 1) dist[i] = 0, Q.push(i);
	}
	for (int i = 1; i < n; i++) {
		int a, b; cin >> a >> b;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}

	while (Q.size()) {
		auto cur = Q.front(); Q.pop();
		for (const auto& nxt : adj[cur]) {
			if (!~dist[nxt]) dist[nxt] = dist[cur] + 1, Q.push(nxt);
		}
	}

	int lo = 1, hi = n + 1;
	while (lo + 1 < hi) {
		int mid = lo + hi >> 1;
		if (Check(mid)) lo = mid;
		else hi = mid;
	}
	cout << lo << '\n';
}