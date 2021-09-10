#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

using vi = vector<int>;
using vvi = vector<vi>;

int main() {
	fastio;
	int n, m, cnt{}; cin >> n >> m;
	vvi adj(n), rev(n);
	while (m--) {
		int a, b; cin >> a >> b; --a, --b;
		adj[a].push_back(b);
		rev[b].push_back(a);
	}

	auto GetDP = [&](const vvi& adj) -> vi {
		vi ret(n);
		for (int i = 0; i < n; i++) {
			vi visited(n);
			auto DFS = [&](int cur, auto&& DFS) -> int {
				int ret = visited[cur] = 1;
				for (const auto& nxt : adj[cur])
					if (!visited[nxt]) ret += DFS(nxt, DFS);
				return ret;
			};
			ret[i] = DFS(i, DFS);
		}
		return ret;
	};
	auto DP1 = GetDP(adj), DP2 = GetDP(rev);

	for (int i = 0; i < n; i++)
		if (max(DP1[i], DP2[i]) > n + 1 >> 1) cnt++;
	cout << cnt << '\n';
}