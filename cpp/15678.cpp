#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int n, m, v[100'001];
int64_t ans = -1e18, DP[100'001];
deque<pair<int64_t, int>> DQ;

int main() {
	fastio;
	cin >> n >> m;
	for (int i = 1; i <= n; i++) cin >> v[i];
	for (int i = n; i >= 1; i--) {
		while (DQ.size() && DQ[0].second > i + m) DQ.pop_front();
		DP[i] = v[i] + (DQ.size() ? DQ[0].first : 0);
		while (DQ.size() && DQ.back().first < DP[i]) DQ.pop_back();
		if (DP[i] > 0) DQ.push_back({ DP[i], i });
	}
	for (int i = 1; i <= n; i++) ans = max(ans, DP[i]);
	cout << ans << '\n';
}