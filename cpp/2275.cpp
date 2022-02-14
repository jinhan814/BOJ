#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int n, root, H;
int dist[10'001], mx[10'001];
vector<pair<int, int>> adj[10'001];

int DFS(int cur) {
	mx[cur] = dist[cur];
	for (const auto& [nxt, cost] : adj[cur]) {
		dist[nxt] = dist[cur] + cost;
		mx[cur] = max(mx[cur], DFS(nxt));
	}
	return mx[cur];
}

int Sol(int cur, int delta) {
	int ret = 0;
	for (const auto& [nxt, cost] : adj[cur]) {
		if (mx[nxt] - delta <= H) continue;
		if (mx[nxt] - delta - cost <= H) ret += mx[nxt] - delta - H;
		else ret += Sol(nxt, delta + cost) + cost;
	}
	return ret;
}

int main() {
	fastio;
	cin >> n >> H;
	for (int i = 1; i <= n; i++) {
		int a, b; cin >> a >> b;
		if (a == 0) root = i;
		else adj[a].push_back({ i, b });
	}
	DFS(root);
	cout << Sol(root, 0) << '\n';
}