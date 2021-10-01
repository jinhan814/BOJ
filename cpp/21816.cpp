#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

constexpr int MOD = 1e9 + 7;
using pii = pair<int, int>;

int n, pos, cnt[64'001], DP[64'001][41];
pii v[41];
vector<int> adj[64'001];

inline void Add(int& a, int b) { if ((a += b) >= MOD) a -= MOD; }

inline int GetIdx(int a, int b, int c) {
	if (a > b) swap(a, b);
	if (a > c) swap(a, c);
	if (b > c) swap(b, c);
	return (a * n + b) * n + c;
}

inline int CCW(const pii& a, const pii& b, const pii& c) {
	const int ret = (b.first - a.first) * (c.second - b.second) - (b.second - a.second) * (c.first - b.first);
	return ret ? ret > 0 ? 1 : -1 : 0;
}

inline bool IsInside(int i, int j, int k, int cur) {
	const int ccw = CCW(v[i], v[j], v[k]);
	if (CCW(v[cur], v[i], v[j]) != ccw) return 0;
	if (CCW(v[cur], v[j], v[k]) != ccw) return 0;
	if (CCW(v[cur], v[k], v[i]) != ccw) return 0;
	return 1;
}

int main() {
	fastio;
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> v[i].first >> v[i].second;

	for (int i = 1; i <= n; i++) for (int j = i + 1; j <= n; j++) for (int k = j + 1; k <= n; k++) {
		const int idx = GetIdx(i, j, k);
		cnt[idx] = 3; DP[idx][3] = 6;
		for (int cur = 1; cur <= n; cur++) {
			if (cur == i || cur == j || cur == k) continue;
			if (IsInside(i, j, k, cur)) cnt[idx]++;
			else adj[idx].push_back(cur);
		}
		if (cnt[idx] == n) pos = idx;
	}

	if (!pos) return !(cout << 0 << '\n');

	for (int t = 4; t <= n; t++) {
		for (int i = 1; i <= n; i++) for (int j = i + 1; j <= n; j++) for (int k = j + 1; k <= n; k++) {
			const int idx = GetIdx(i, j, k);
			if (!DP[idx][t - 1]) continue;
			if (cnt[idx] >= t) {
				const int delta = 1LL * DP[idx][t - 1] * (cnt[idx] - t + 1) % MOD;
				Add(DP[idx][t], delta);
			}
			for (const auto& nxt : adj[idx]) {
				if (IsInside(nxt, i, j, k)) Add(DP[GetIdx(nxt, i, j)][t], DP[idx][t - 1]);
				else if (IsInside(nxt, i, k, j)) Add(DP[GetIdx(nxt, i, k)][t], DP[idx][t - 1]);
				else if (IsInside(nxt, j, k, i)) Add(DP[GetIdx(nxt, j, k)][t], DP[idx][t - 1]);
			}
		}
	}
	cout << DP[pos][n] << '\n';
}