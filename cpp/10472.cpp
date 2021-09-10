#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int dist[1 << 9];

int main() {
	fastio;
	queue<int> Q;
	Q.push(0), dist[0] = 1;
	while (Q.size()) {
		int cur = Q.front(); Q.pop();
		for (int i = 0; i < 9; i++) {
			int nxt = cur ^ 1 << i;
			for (int k = 0; k < 4; k++) {
				int nx = i / 3 + "1012"[k] - '1';
				int ny = i % 3 + "2101"[k] - '1';
				if (nx < 0 || nx >= 3 || ny < 0 || ny >= 3) continue;
				nxt ^= 1 << nx * 3 + ny;
			}
			if (!dist[nxt]) Q.push(nxt), dist[nxt] = dist[cur] + 1;
		}
	}

	int N; cin >> N;
	while (N--) {
		int t = 0;
		for (int i = 0; i < 3; i++) {
			string s; cin >> s;
			for (int j = 0; j < 3; j++)
				if (s[j] == '*') t |= 1 << i * 3 + j;
		}
		cout << dist[t] - 1 << '\n';
	}
}