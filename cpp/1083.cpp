#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int n, m, v[50];

int main() {
	fastio;
	cin >> n;
	for (int i = 0; i < n; i++) cin >> v[i];
	cin >> m;

	for (int pos = 0; pos < n && m; pos++) {
		int nxt = -1;
		for (int i = 1; i <= m && pos + i < n; i++)
			if (nxt == -1 || v[nxt] < v[pos + i]) nxt = pos + i;
		if (nxt == -1 || v[pos] >= v[nxt]) continue;
		rotate(v + pos, v + nxt, v + nxt + 1);
		m -= nxt - pos;
	}

	for (int i = 0; i < n; i++) cout << v[i] << ' '; cout << '\n';
}