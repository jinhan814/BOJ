#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

using i64 = long long;

int n, v[1 << 18], t[1 << 18];
int dfs_order[1 << 18], dep[1 << 18];

void DFS(int cur) {
	static int dfs_cnt = 0;
	dep[cur] = dep[cur >> 1] + 1;
	if (2 * cur <= n) DFS(2 * cur);
	dfs_order[cur] = dfs_cnt++;
	if (2 * cur + 1 <= n) DFS(2 * cur + 1);
}

i64 Sol(int l, int r) {
	i64 ret = -1e9, mx = -1e9;
	for (int i = 0; i < n; i++) {
		if (dep[t[i]] < l || r < dep[t[i]]) continue;
		const i64 val = v[t[i]];
		ret = max({ ret, mx + val, val });
		mx = max(mx + val, val);
	}
	return ret;
}

int main() {
	fastio;
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> v[i];
	DFS(1); iota(t, t + n, 1);
	sort(t, t + n, [&](const int a, const int b) { return dfs_order[a] < dfs_order[b]; });
	i64 mx = -1e9;
	for (int i = 1; i <= 18; i++) for (int j = i; j <= 18; j++) mx = max(mx, Sol(i, j));
	cout << mx << '\n';
}