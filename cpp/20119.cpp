#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int main() {
	fastio;
	int n, m; cin >> n >> m;
	vector<vector<int>> v(m), w(n + 1);
	for (int i = 0; i < m; i++) {
		int sz; cin >> sz; v[i].resize(sz + 1);
		for (int j = 0; j <= sz; j++) cin >> v[i][j];
		for (int j = 0; j < sz; j++) w[v[i][j]].push_back(i);
	}

	int k; cin >> k;
	queue<int> Q; vector<int> res, visited(n + 1), cnt(m);
	for (int t; k-- && cin >> t;) Q.push(t), visited[t] = 1;
	while (Q.size()) {
		auto cur = Q.front(); Q.pop(); res.push_back(cur);
		for (const auto& i : w[cur]) {
			const auto nxt = v[i].back();
			if (++cnt[i] == v[i].size() - 1 && !visited[nxt]) Q.push(nxt), visited[nxt] = 1;
		}
	}

	sort(res.begin(), res.end());
	cout << res.size() << '\n';
	for (auto& i : res) cout << i << ' '; cout << '\n';
}