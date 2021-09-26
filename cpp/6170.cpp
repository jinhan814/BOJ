#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int main() {
	fastio;
	int DP[46][2]; DP[1][0] = DP[1][1] = 1;
	for (int i = 2; i <= 46; i++) {
		DP[i][0] = DP[i - 1][0] + DP[i - 1][1];
		DP[i][1] = DP[i - 1][0];
	}

	int N; cin >> N;
	for (int c = 1; c <= N; c++) {
		int n; cin >> n;
		cout << "Scenario #" << c << ":\n";
		cout << DP[n][0] + DP[n][1] << "\n\n";
	}
}