#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int DP[1'000'001]{ 0, 0, 0, 0, 1, 2 };

int main() {
	fastio;
	for (int i = 6; i <= 1'000'000; i++) DP[i] = DP[i + 1 >> 1] + 2;
	int n; cin >> n;
	cout << DP[n] << '\n';
}