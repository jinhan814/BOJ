#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

#define OOB(x, y) (x < 0 || x >= n || y < 0 || y >= n)
using pii = pair<int, int>;

int n, m, ans;
vector<pii> adj[100][100];
bitset<100> check[100], visited[100];

int main() {
	fastio;
	cin >> n >> m;
	while (m--) {
		int a, b, c, d; cin >> a >> b >> c >> d; --a, --b, --c, --d;
		adj[a][b].push_back({ c, d });
	}

	queue<pii> Q;
	Q.push({ 0, 0 }); visited[0][0] = 1; check[0][0] = 1;
	while (Q.size()) {
		// visit and flip
		auto [x, y] = Q.front(); Q.pop();
		for (const auto& [nx, ny] : adj[x][y]) {
			if (!check[nx][ny]) {
				check[nx][ny] = 1;
				bool flag = 0;
				for (int k = 0; k < 4; k++) {
					int nnx = nx + "1012"[k] - '1';
					int nny = ny + "2101"[k] - '1';
					if (!OOB(nnx, nny) && visited[nnx][nny]) flag = 1;
				}
				if (flag) Q.push({ nx, ny }), visited[nx][ny] = 1;
			}
		}
		for (int k = 0; k < 4; k++) {
			int nx = x + "1012"[k] - '1';
			int ny = y + "2101"[k] - '1';
			if (OOB(nx, ny) || visited[nx][ny] || !check[nx][ny]) continue;
			Q.push({ nx, ny }), visited[nx][ny] = 1;
		}
	}

	for (int i = 0; i < n; i++) ans += check[i].count();
	cout << ans << '\n';
}