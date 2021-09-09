#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

using pii = pair<int, int>;

int main() {
	fastio;
	int N; cin >> N;
	while (N--) {
		int n, cnt{}; cin >> n;
		vector<string> v(n), visited(n, string(n, 0));
		for (int i = 0; i < n; i++) cin >> v[i];
		queue<pii> Q;
		for (int i = 0; i < n; i++) for (int j = 0; j < n; j++)
			if (v[i][j] == 'w') Q.push({ i, j }), visited[i][j] = 1;
		while (Q.size()) {
			auto [x, y] = Q.front(); Q.pop();
			if (v[x][y] == '-') cnt++;
			for (int k = 0; k < 8; k++) {
				int nx = x + "10001222"[k] - '1';
				int ny = y + "22100012"[k] - '1';
				if (nx < 0 || nx >= n || ny < 0 || ny >= n) continue;
				if (v[nx][ny] == 'b' || visited[nx][ny]) continue;
				Q.push({ nx, ny }), visited[nx][ny] = 1;
			}
		}
		cout << cnt << '\n';
	}
}