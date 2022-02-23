#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int main() {
	fastio;
	int n, m, mx = 0; cin >> n >> m;
	vector<int> dist(n + 1, -1); queue<int> Q;
	for (int t; m-- && cin >> t; Q.push(t), dist[t] = 0);
	while (Q.size()) {
		auto cur = Q.front(); Q.pop();
		mx = max(mx, dist[cur]);
		for (int i = 0; i < 20; i++) {
			const int nxt = cur ^ 1 << i;
			if (0 <= nxt && nxt <= n && dist[nxt] == -1) {
				Q.push(nxt), dist[nxt] = dist[cur] + 1;
			}
		}
	}
	cout << mx << '\n';
}