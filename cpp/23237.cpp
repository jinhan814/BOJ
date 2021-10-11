#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int main() {
	fastio;
	for (int c = 1, n; cin >> n && n; c++) {
		vector<vector<int>> adj(n);
		for (int i = 1; i < n; i++) {
			int a, b; cin >> a >> b;
			adj[a].push_back(b);
			adj[b].push_back(a);
		}

		auto Sol = [&]() -> int {
			int ret = 0;
			for (int c = 1, pos; c < 1 << n; c++) {
				vector<int> check(n), visited(n); int cnt = 0, t = 0;
				for (int i = 0; i < n; i++) if (c & 1 << i) check[i] = 1, pos = i, t++;
				auto DFS = [&](int cur, auto&& DFS) -> void {
					cnt++; visited[cur] = 1;
					for (const auto& nxt : adj[cur])
						if (check[nxt] && !visited[nxt]) DFS(nxt, DFS);
				};
				DFS(pos, DFS);
				if (cnt == t) ret++;
				for (int i = 0; i < n; i++) if (c & 1 << i) check[i] = 0;
			}
			return ret;
		};

		cout << "Case " << c << ": " << Sol() << '\n';
	}
}