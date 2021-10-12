#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int main() {
	fastio;
	int n, m, a, b, dist[100'001]{}; cin >> a >> b >> n >> m;
	queue<int> Q; Q.push(n); dist[n] = 1;
	while (Q.size()) {
		auto x = Q.front(); Q.pop();
		if (x == m) cout << dist[x] - 1 << '\n';
		for (int nx : { x - 1, x + 1, x - a, x + a, x - b, x + b, x * a, x * b }) {
			if (0 <= nx && nx <= 100'000 && !dist[nx])
				dist[nx] = dist[x] + 1, Q.push(nx);
		}
	}
}