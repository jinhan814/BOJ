#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int n, v[20][20];
double DP[1 << 20];

double Sol(int dep, int state) {
	if (!dep--) return 1;
	double& ret = DP[state];
	if (!isnan(ret)) return ret; ret = 0;
	for (int i = 0; i < n; i++) {
		if (~state & 1 << i) continue;
		ret = max(ret, Sol(dep, state ^ 1 << i) * v[dep][i] / 100);
	}
	return ret;
}

int main() {
	fastio;
	memset(DP, -1, sizeof DP);
	cin >> n;
	for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) cin >> v[i][j];
	cout << fixed << setprecision(20) << 100 * Sol(n, (1 << n) - 1) << '\n';
}