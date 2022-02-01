#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

constexpr int INF = 0x3f3f3f3f;

int n, sz[5001];
int DP1[5001][5001], DP2[5001][5001];
int mn[5001], mx[5001];
vector<int> adj[5001];

void DFS(int cur, int prv = -1) {
	sz[cur] = 1;
	for (const auto& nxt : adj[cur]) {
		if (nxt == prv) continue;
		DFS(nxt, cur);
		for (int i = sz[cur]; i; i--) for (int j = sz[nxt]; j; j--) {
			DP1[cur][i + j] = min(DP1[cur][i + j], DP1[cur][i] + DP1[nxt][j]);
			DP2[cur][i + j] = max(DP2[cur][i + j], DP2[cur][i] + DP2[nxt][j]);
		}
		sz[cur] += sz[nxt];
	}
	for (int i = 1; i <= sz[cur]; i++) {
		mn[i] = min(mn[i], DP1[cur][i]);
		mx[i] = max(mx[i], DP2[cur][i]);
	}
}

int main() {
	fastio;
	// 1. input
	memset(DP1, 0x3f, sizeof DP1), memset(mn, 0x3f, sizeof mn);
	int m; cin >> n >> m;
	for (int i = 1; i <= n; i++) DP1[i][1] = 0;
	for (int t; m-- && cin >> t;) DP1[t][1] = DP2[t][1] = 1;
	for (int i = 1; i < n; i++) {
		int a, b; cin >> a >> b;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}

	// 2. DP
	DFS(1);

	// 3. output
	int q, res = 0; cin >> q;
	for (int a, b; q-- && cin >> a >> b;)
		if (mn[a] <= b && b <= mx[a]) res++;
	cout << res << '\n';
}