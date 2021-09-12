#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

using pii = pair<int, int>;
using Board = array<bitset<5>, 5>;

struct Converter {
	int operator() (Board state) {
		int ret = 0;
		for (int i = 0; i < 5; i++) for (int j = 0; j < 5; j++)
			if (state[i][j]) ret |= 1 << i * 5 + j;
		return ret;
	}
	Board operator() (int n) {
		Board ret;
		for (int i = 0; i < 5; i++) for (int j = 0; j < 5; j++)
			if (n & 1 << i * 5 + j) ret[i][j] = 1;
		return ret;
	}
} Conv;

bool IsConnected(int state) {
	int cnt = __builtin_popcount(state);
	Board b = Conv(state), visited;

	auto DFS = [&](int x, int y, auto&& DFS) -> int {
		int ret = 1; visited[x][y] = 1;
		for (int k = 0; k < 4; k++) {
			int nx = x + "1012"[k] - '1';
			int ny = y + "2101"[k] - '1';
			if (nx < 0 || nx >= 5 || ny < 0 || ny >= 5) continue;
			if (!b[nx][ny] || visited[nx][ny]) continue;
			ret += DFS(nx, ny, DFS);
		}
		return ret;
	};

	for (int i = 0; i < 5; i++) for (int j = 0; j < 5; j++)
		if (b[i][j]) return DFS(i, j, DFS) == cnt;
}

int main() {
	fastio;
	Board state;
	for (int i = 0; i < 5; i++) {
		string s; cin >> s;
		for (int j = 0; j < 5; j++) if (s[j] == '*') state[i][j] = 1;
	} 
	queue<pii> Q; bitset<1 << 25> visited;
	Q.push({ Conv(state), 0 }), visited[Conv(state)] = 1;
	while (Q.size()) {
		auto [state, dist] = Q.front(); Q.pop();
		if (IsConnected(state)) return !(cout << dist << '\n');
		auto b = Conv(state);
		for (int i = 0; i < 5; i++) for (int j = 0; j < 5; j++) {
			if (!b[i][j]) continue;
			for (int k = 0; k < 4; k++) {
				int nx = i + "1012"[k] - '1';
				int ny = j + "2101"[k] - '1';
				if (nx < 0 || nx >= 5 || ny < 0 || ny >= 5 || b[nx][ny]) continue;
				b[nx][ny] = 1; b[i][j] = 0;
				if (!visited[Conv(b)]) Q.push({ Conv(b), dist + 1 }), visited[Conv(b)] = 1;
				b[nx][ny] = 0; b[i][j] = 1;
			}
		}
	}
}