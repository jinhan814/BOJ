#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

using pii = pair<int, int>;
int n, sx, sy, ex, ey, dist[200][200];

int main() {
	fastio;
	cin >> n >> sx >> sy >> ex >> ey;
	queue<pii> Q; 
	Q.push({ sx, sy }), dist[sx][sy] = 1;
	while (Q.size()) {
		auto [x, y] = Q.front(); Q.pop();
		for (int k = 0; k < 6; k++) {
			int nx = x + "002244"[k] - '2';
			int ny = y + "130413"[k] - '2';
			if (nx < 0 || nx >= n || ny < 0 || ny >= n) continue;	
			if (!dist[nx][ny]) Q.push({ nx, ny }), dist[nx][ny] = dist[x][y] + 1;
		}
	}
	cout << dist[ex][ey] - 1 << '\n';
}