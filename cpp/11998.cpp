#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int n, m, A, B, dist[1 << 14];

int BFS() {
	int ret = 1e9; memset(dist, -1, sizeof dist);
	queue<int> Q; Q.push(0); dist[0] = 0;
	while (Q.size()) {
		auto cur = Q.front(); Q.pop();
		const int a = cur & 127, b = cur >> 7 & 127;
		if (dist[cur] <= n) ret = min(ret, abs(m - a - b));
		else break;
		for (const auto [na, nb] : vector<pair<int, int>>{
			{ A, b }, { a, B }, { 0, b }, { a, 0 },
			{ a - min(a, B - b), b + min(a, B - b) },
			{ a + min(b, A - a), b - min(b, A - a) } }) {
			const int nxt = na | nb << 7;
			if (!~dist[nxt]) dist[nxt] = dist[cur] + 1, Q.push(nxt);
		}
	}
	return ret;
}

int main() {
	fastio;
	cin >> A >> B >> n >> m;
	cout << BFS() << '\n';
}