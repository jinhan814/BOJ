#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int main() {
	fastio;
	int n, m; cin >> n >> m;
	vector<int> v(n), dist(n, -1), prv(n, -1);
	for (int i = 0; i < n; i++) {
		string s; cin >> s;
		for (int j = 0; j < m; j++)
			if (s[j] == '1') v[i] |= 1 << j;
	}
	int st, en; cin >> st >> en; --st, --en;

	queue<int> Q;
	Q.push(st), dist[st] = 0;
	while (Q.size()) {
		auto cur = Q.front(); Q.pop();
		for (int nxt = 0; nxt < n; nxt++)
			if (__builtin_popcount(v[cur] ^ v[nxt]) == 1 && !~dist[nxt])
				Q.push(nxt), dist[nxt] = dist[cur] + 1, prv[nxt] = cur;
	}

	if (~dist[en]) {
		vector<int> path;
		for (int i = en; i != st; i = prv[i]) path.push_back(i);
		path.push_back(st);
		for (int i = path.size(); i-- > 0;) cout << path[i] + 1 << ' ';
		cout << '\n';
	}
	else cout << -1 << '\n';
}