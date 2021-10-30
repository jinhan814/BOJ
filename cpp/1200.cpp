#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int n, m, a, b, mn = 1e9;
int pSum[20][20], v[20];

bool Check(const int mid) {
	int cnt = 0;
	for (int i = 1, k = i; i <= n; i = k, cnt++) {
		for (bool flag = 1; k <= n; k++) {
			for (int j = 1; j <= b; j++) {
				const int sum = pSum[k][v[j]] - pSum[k][v[j - 1]] - pSum[i - 1][v[j]] + pSum[i - 1][v[j - 1]];
				if (sum > mid) flag = 0;
			}
			if (!flag) break;
		}
		if (k == i) return 0;
	}
	return cnt <= a;
}

int F() {
	int lo = -1, hi = 1e9;
	while (lo + 1 < hi) {
		int mid = lo + hi >> 1;
		if (!Check(mid)) lo = mid;
		else hi = mid;
	}
	return hi;
}

void DFS(int dep, int cur) {
	if (dep == b) { mn = min(mn, F()); return; }
	if (cur > m || m - cur + 1 < b - dep) return;
	if (dep == b - 1) {
		v[dep + 1] = m;
		DFS(dep + 1, m + 1);
	}
	else for (int i = cur; i <= m; i++) {
		v[dep + 1] = i;
		DFS(dep + 1, i + 1);
	}
}

int main() {
	fastio;
	cin >> n >> m >> a >> b; ++a, ++b;
	for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) {
		cin >> pSum[i][j];
		pSum[i][j] += pSum[i][j - 1];
	}
	for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) {
		pSum[i][j] += pSum[i - 1][j];
	}
	DFS(0, 1); cout << mn << '\n';
}