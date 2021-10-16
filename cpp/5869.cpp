#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

const int MOD = 2012;

int main() {
	fastio;
	string s; cin >> s;
	const int n = s.size();

	vector<int> pSum(n);
	for (int i = 0; i < n; i++) pSum[i] = s[i] == '(' ? 1 : -1;
	for (int i = 1; i < n; i++) pSum[i] += pSum[i - 1];

	vector<vector<int>> DP(n, vector<int>(n + 2 >> 1, -1));
	auto DFS = [&](int i, int a_cnt, auto&& DFS) -> int {
		if (i == n) return !a_cnt;
		const int b_cnt = (i ? pSum[i - 1] : 0) - a_cnt;
		int& ret = DP[i][a_cnt];
		if (ret != -1) return ret; ret = 0;
		if (s[i] == '(') ret += DFS(i + 1, a_cnt, DFS) + DFS(i + 1, a_cnt + 1, DFS);
		else {
			if (a_cnt) ret += DFS(i + 1, a_cnt - 1, DFS);
			if (b_cnt) ret += DFS(i + 1, a_cnt, DFS);
		}
		return ret %= MOD;
	};
	cout << DFS(0, 0, DFS) << '\n';
}