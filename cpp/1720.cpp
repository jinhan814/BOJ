#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

template<size_t sz>
constexpr array<int, sz> Sol() {
	array<int, sz> DP{ 1, 1 };
	for (int i = 2; i < sz; i++) DP[i] = DP[i - 1] + 2 * DP[i - 2];
	for (int i = sz - 1; ~i; i--) {
		auto t = DP[i / 2 + (~i & 1)];
		DP[i] -= (DP[i] - t) / 2;
	}
	return DP;
}

constexpr auto DP = Sol<31>();

int main() {
	fastio;
	int n; cin >> n;
	cout << DP[n] << '\n';
}