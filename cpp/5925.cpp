#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

constexpr int INF = 1e9 + 7;
using pii = pair<int, int>;

int n, m, mn = INF, check[50][50], dist[50][50];
string board[50];
vector<pii> colors[3];

void GetColor() {
	memset(check, -1, sizeof check);
	for (int i = 0, color = 0; i < n; i++) for (int j = 0; j < m; j++) {
		if (board[i][j] == '.' || ~check[i][j]) continue;
		queue<pii> Q;
		Q.push({ i, j }), check[i][j] = color;
		while (Q.size()) {
			auto [x, y] = Q.front(); Q.pop();
			colors[color].push_back({ x, y });
			for (int k = 0; k < 4; k++) {
				int nx = x + "1012"[k] - '1';
				int ny = y + "2101"[k] - '1';
				if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
				if (board[nx][ny] == 'X' && check[nx][ny] == -1)
					Q.push({ nx, ny }), check[nx][ny] = color;
			}
		}
		color++;
	}
	for (int i = 0; i < 3; i++) sort(colors[i].begin(), colors[i].end());
}

void BFS(queue<pii>& Q) {
	while (Q.size()) {
		auto [x, y] = Q.front(); Q.pop();
		for (int k = 0; k < 4; k++) {
			int nx = x + "1012"[k] - '1';
			int ny = y + "2101"[k] - '1';
			if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
			if (dist[nx][ny] == -1) Q.push({ nx, ny }), dist[nx][ny] = dist[x][y] + 1;
		}
	}
}

int Sol1(int color) {
	queue<pii> Q; memset(dist, -1, sizeof dist);
	for (const auto& [x, y] : colors[color]) Q.push({ x, y }), dist[x][y] = 0;
	int mn[3] = { INF, INF, INF }; BFS(Q);
	for (int i = 0; i < 3; i++) for (const auto& [x, y] : colors[i]) mn[i] = min(mn[i], dist[x][y]);
	return reduce(mn, mn + 3) - 2;
}

int Sol2(int x, int y) {
	queue<pii> Q; memset(dist, -1, sizeof dist);
	Q.push({ x, y }), dist[x][y] = 0;
	int mn[3] = { INF, INF, INF }; BFS(Q);
	for (int i = 0; i < 3; i++) for (const auto& [x, y] : colors[i]) mn[i] = min(mn[i], dist[x][y]);
	return reduce(mn, mn + 3) - 2;
}

int main() {
	fastio;
	cin >> n >> m;
	for (int i = 0; i < n; i++) cin >> board[i]; GetColor();
	for (int i = 0; i < 3; i++) mn = min(mn, Sol1(i));
	for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) {
		if (board[i][j] == '.') mn = min(mn, Sol2(i, j));
	}
	cout << mn << '\n';
}