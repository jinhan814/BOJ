#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

template<typename T, size_t n, size_t m>
constexpr array<array<T, m + 1>, n + 1> Partition() { // P(1, 1) ~ P(n, m)
	array<array<T, m + 1>, n + 1> DP{};
	for (int i = 1; i <= n; i++) for (int j = 1; j <= min<int>(i, m); j++) {
		if (j == 1 || j == i) DP[i][j] = 1;
		else DP[i][j] = DP[i - 1][j - 1] + DP[i - j][j];
	}
	return DP;
}

constexpr auto DB = Partition<int, 220, 10>();

// kth Increasing Sequence s.t. len = n, sum = m
void Sol(const int n, const int m, int k, vector<int>& res, const int bias = 0) {
	if (n == 1) { res.push_back(bias + m); return; }
	for (int i = 1; ; i++) {
		if (k > DB[m - n * i + n - 1][n - 1]) { k -= DB[m - n * i + n - 1][n - 1]; continue; }
		res.push_back(bias + i);
		Sol(n - 1, m - n * i + n - 1, k, res, bias + i - 1);
		return;
	}
}

int main() {
	fastio;
	int n, m, k; cin >> n >> m >> k;
	vector<int> res; Sol(n, m, k, res);
	for (auto& i : res) cout << i << ' '; cout << '\n';
}