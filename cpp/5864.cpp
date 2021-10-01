#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

constexpr int INF = 1e9 + 7;

int main() {
	fastio;
	int n, a, b; cin >> n >> a >> b;
	vector<int> v(n);
	for (int i = 0; i < n; i++) cin >> v[i];
	sort(v.begin(), v.end());
	v.erase(unique(v.begin(), v.end()), v.end());
	n = v.size();

	vector<int> DP(n, -1);
	auto DFS = [&](int cur, auto&& DFS) -> int {
		if (cur == n) return 0;
		int& ret = DP[cur];
		if (ret != -1) return ret; ret = INF;
		for (int nxt = cur; nxt < n; nxt++)
			ret = min(ret, DFS(nxt + 1, DFS) + 2 * a + (v[nxt] - v[cur]) * b);
		return ret;
	};

	const int ans = DFS(0, DFS);
	if (ans & 1) cout << ans / 2 << ".5" << '\n';
	else cout << ans / 2 << '\n';
}