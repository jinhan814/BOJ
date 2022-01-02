#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int main() {
	fastio;
	int n, m, cnt = 0; cin >> n >> m;
	vector<int> check(n), v(m);
	for (int i = 0; i < m; i++) cin >> v[i];
	for (int i = 0; i < m; i++) {
		// check 1.
		int flag = 0;
		for (int j = 0; j < n; j++) if (check[j] == v[i]) flag = 1;
		if (flag) continue;

		// check 2.
		int pos = -1;
		for (int j = 0; j < n; j++) if (!check[j]) pos = j;
		if (pos != -1) { check[pos] = v[i]; continue; }

		// check 3.
		for (int j = 0, mx = i; j < n; j++) {
			int t = i + 1;
			for (; t < m && check[j] != v[t]; t++);
			if (mx < t) pos = j, mx = t;
		}
		check[pos] = v[i], cnt++;
	}
	cout << cnt << '\n';
}