#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

using vi = vector<int>;
using vvi = vector<vi>;
using vvvi = vector<vvi>;

struct Piece {
	int x, y, d;
	void Update(int nx, int ny, int nd) {
		x = nx, y = ny, d = nd;
	}
};

enum { WHITE, RED, BLUE };
struct Board {
	int n, k;
	vvi color; vvvi state;
	vector<Piece> piece;

	Board(int n, int k) : n(n), k(k), color(n, vi(n)), piece(k), state(n, vvi(n)) { Init(); }

	void Init() { // input
		for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) {
			cin >> color[i][j];
		}
		for (int i = 0; i < k; i++) {
			auto& [x, y, d] = piece[i];
			cin >> x >> y >> d;
			x--, y--, d = "00213"[d] - '0';
			state[x][y].push_back(i);
		}
	}

	bool OOB(int x, int y) {
		return x < 0 || x >= n || y < 0 || y >= n;
	}

	Piece GetNxt(int idx) {
		auto [x, y, d] = piece[idx];
		int nx = x + "1012"[d] - '1';
		int ny = y + "2101"[d] - '1';
		int nd = d;

		if (OOB(nx, ny) || color[nx][ny] == BLUE) {
			nd = (nd + 2) % 4;
			nx = x + "1012"[nd] - '1';
			ny = y + "2101"[nd] - '1';
			if (OOB(nx, ny) || color[nx][ny] == BLUE) nx = x, ny = y;
		}
		return { nx, ny, nd };
	}

	bool Move(int idx) {
		auto [x, y, d] = piece[idx];
		auto nxt = GetNxt(idx);
		int pos = find(state[x][y].begin(), state[x][y].end(), idx) - state[x][y].begin();
		int cnt = state[x][y].size() - pos;

		vector<int> piece_num;
		for (int i = 0; i < cnt; i++) piece_num.push_back(state[x][y][pos + i]);
		for (int i = 0; i < cnt; i++) {
			state[x][y].pop_back();
		}
		for (auto& i : piece_num) {
			auto& cur = piece[i];
			cur.Update(nxt.x, nxt.y, i == idx ? nxt.d : cur.d);
			state[cur.x][cur.y].push_back(i);
		}

		auto [cx, cy, cd] = piece[idx];
		if (!(x == cx && y == cy) && color[cx][cy] == RED) {
			reverse(state[cx][cy].end() - cnt, state[cx][cy].end());
		}
		return state[cx][cy].size() < 4;
	}

	int Sol() {
		int ret = 1;
		for (; ret <= 1000; ret++) {
			for (int i = 0; i < k; i++)
				if (!Move(i)) return ret;
		}
		return -1;
	}
};

int main() {
	fastio;
	int n, k; cin >> n >> k;
	Board B(n, k);
	cout << B.Sol() << '\n';
}