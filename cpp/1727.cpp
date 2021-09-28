#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

constexpr int INF = 1e9 + 7;

int main() {
	fastio;
	int n, m, cache[1000][1000]; cin >> n >> m;
	vector<int> v(n), w(m);
	for (auto& i : v) cin >> i;
	for (auto& i : w) cin >> i;
	if (n > m) swap(n, m), swap(v, w);

	sort(v.begin(), v.end());
	sort(w.begin(), w.end());

	memset(cache, -1, sizeof cache);
	auto DFS = [&](int i, int j, auto&& DFS) -> int {
		if (i == n) return 0;
		int& ret = cache[i][j];
		if (ret != -1) return ret; ret = INF;
		for (int k = j; k < m; k++) {
			ret = min(ret, abs(v[i] - w[k]) + DFS(i + 1, k + 1, DFS));
		}
		return ret;
	};
	cout << DFS(0, 0, DFS) << '\n';
}