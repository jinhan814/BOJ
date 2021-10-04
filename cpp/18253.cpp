#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

using ll = long long;
constexpr ll INF = ll(1e18) + 7;
using tii = tuple<ll, int, int>;
struct Query { int x1, y1, x2, y2, idx; };

int n, m, v[5][100'000];
ll q, ans[100'000];
ll dist[5][100'000];

void Dijkstra(int l, int r, int sx, int sy) {
	for (int i = 0; i < n; i++) for (int j = l; j <= r; j++) dist[i][j] = INF;
	priority_queue<tii, vector<tii>, greater<>> PQ;
	PQ.push({ dist[sx][sy] = v[sx][sy], sx, sy });
	while (PQ.size()) {
		auto [cdist, x, y] = PQ.top(); PQ.pop();
		if (dist[x][y] != cdist) continue;
		for (int k = 0; k < 4; k++) {
			int nx = x + "1012"[k] - '1';
			int ny = y + "2101"[k] - '1';
			if (nx < 0 || nx >= n || ny < l || ny > r) continue;
			if (dist[nx][ny] > cdist + v[nx][ny]) PQ.push({ dist[nx][ny] = cdist + v[nx][ny], nx, ny });
		}
	}
}

void Sol(int l, int r, vector<Query> Q) {
	if (Q.empty()) return;
	if (r - l <= 1) {
		for (int i = 0; i < n; i++) for (int j = l; j <= r; j++) {
			Dijkstra(l, r, i, j);
			for (const auto& [x1, y1, x2, y2, idx] : Q)
				if (x1 == i && y1 == j) ans[idx] = min(ans[idx], dist[x2][y2]);
		}
	}
	else {
		int mid = l + r >> 1;
		for (int i = 0; i < n; i++) {
			Dijkstra(l, r, i, mid);
			for (const auto& [x1, y1, x2, y2, idx] : Q)
				ans[idx] = min(ans[idx], dist[x1][y1] + dist[x2][y2] - v[i][mid]);
		}
		vector<Query> L, R;
		for (const auto& i : Q) {
			if (i.y1 < mid && i.y2 < mid) L.push_back(i);
			if (i.y1 > mid && i.y2 > mid) R.push_back(i);
		}
		Sol(l, mid - 1, L); Sol(mid + 1, r, R);
	}
}

int main() {
	fastio;
	cin >> n >> m;
	for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) cin >> v[i][j];

	cin >> q; vector<Query> Q(q);
	for (int i = 0; i < q; i++) {
		auto& [x1, y1, x2, y2, idx] = Q[i]; idx = i;
		cin >> x1 >> y1 >> x2 >> y2; --x1, --y1, --x2, --y2;
	}

	for (int i = 0; i < q; i++) ans[i] = INF;
	Sol(0, m - 1, Q);
	for (int i = 0; i < q; i++) cout << ans[i] << '\n';
}