#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

using u64 = unsigned long long;
constexpr bool AddOverflow(const u64& a, const u64& b) { return (a >> 1) + (b >> 1) >> 63 & 1; }
constexpr bool MulOverflow(const u64& a, const u64& b) { return b && a > u64(-1) / b; }

int n, sz[5001], over[5001];
u64 k, DP[5001][5001];
vector<int> adj[5001];

void DFS(int cur, int prv) {
	sz[cur] = DP[cur][0] = DP[cur][1] = 1;
	for (const auto& nxt : adj[cur]) {
		if (nxt == prv) continue;
		DFS(nxt, cur);
		for (int i = sz[cur]; i; i--) for (int j = sz[nxt]; j; j--) {
			const auto& val_1 = DP[cur][i];
			const auto& val_2 = DP[nxt][j];
			if (MulOverflow(val_1, val_2) ||
				AddOverflow(DP[cur][i + j], val_1 * val_2)) over[i + j] = 1;
			DP[cur][i + j] += val_1 * val_2;
		}
		sz[cur] += sz[nxt];
	}
}

int Sol() {
	u64 acc = 0;
	for (int i = 1; i <= n; i++) {
		if (over[i]) return i;
		for (int j = 1; j <= n; j++) {
			if (AddOverflow(acc, DP[j][i]) ||
				(acc += DP[j][i]) >= k) return i;
		}
	}
	return -1;
}

int main() {
	fastio;
	cin >> n >> k;
	for (int i = 1; i < n; i++) {
		int a, b; cin >> a >> b;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	DFS(1, -1);
	cout << Sol() << '\n';
}