#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

constexpr int INF = 1e9 + 7;
int n, k, v[100], DP[100][10'001];

int Sol(int i, int j) { // [0, i]번 동전으로 j원을 만드는데 필요한 동전 개수
	if (i < 0) return j ? INF : 0;
	if (j < 0) return INF;
	int& ret = DP[i][j];
	if (ret != -1) return ret; ret = Sol(i - 1, j);
	if (j - v[i] >= 0) ret = min(ret, Sol(i, j - v[i]) + 1);
	return ret;
}

int main() {
	fastio;
	memset(DP, -1, sizeof DP);
	cin >> n >> k;
	for (int i = 0; i < n; i++) cin >> v[i];
	auto res = Sol(n - 1, k);
	cout << (res != INF ? res : -1) << '\n';
}