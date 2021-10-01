#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int main() {
	fastio;
	int n, ans = 0; cin >> n;
	vector<int> v(n), nxt(n), indegree(n), visited(n);
	for (int i = 0; i < n; i++) cin >> v[i];
	sort(v.begin(), v.end());

	if (n == 1) return !(cout << 1 << '\n');

	for (int i = 0; i < n; i++) {
		if (i == 0 || i != n - 1 && v[i] - v[i - 1] > v[i + 1] - v[i]) nxt[i] = i + 1, indegree[i + 1]++;
		else nxt[i] = i - 1, indegree[i - 1]++;
	}

	auto DFS = [&](int cur, auto&& DFS) -> void {
		visited[cur] = 1;
		if (!visited[nxt[cur]]) DFS(nxt[cur], DFS);
	};

	for (int i = 0; i < n; i++) if (!indegree[i]) ans++, DFS(i, DFS);
	for (int i = 0; i < n; i++) if (!visited[i]) ans++, DFS(i, DFS);
	cout << ans << '\n';
}