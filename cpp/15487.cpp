#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

constexpr int INF = 1e9 + 7;

int main() {
	fastio;
	int n, DP[4]{ -INF, -INF, -INF, -INF }; cin >> n;
	while (n--) {
		int t; cin >> t;
		DP[3] = max(DP[3], DP[2] + t);
		DP[2] = max(DP[2], DP[1] - t);
		DP[1] = max(DP[1], DP[0] + t);
		DP[0] = max(DP[0], -t);
	}
	cout << DP[3] << '\n';
}