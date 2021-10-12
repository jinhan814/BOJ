#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

#define int int64_t

int32_t main() {
	fastio;
	int n; cin >> n;
	vector<int> v, DP(n + 1, -1);
	for (int i = 1, t = 0; ; i++) {
		t += i * (i + 1) >> 1;
		if (t > n) break;
		v.push_back(t);
	}

	auto DFS = [&](int cur, auto&& DFS) ->int {
		if (cur == 0) return 0;
		int& ret = DP[cur];
		if (ret != -1) return ret; ret = 1e9;
		for (auto& i : v) {
			if (cur < i) break;
			ret = min(ret, DFS(cur - i, DFS) + 1);
		}
		return ret;
	};
	cout << DFS(n, DFS) << '\n';
}