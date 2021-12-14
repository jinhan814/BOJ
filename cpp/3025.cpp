#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

using pii = pair<int, int>;

int n, m;
string board[30'000];
stack<pii> S[30];

void Query(int pos) {
	while (1) {
		auto [x, y] = S[pos].top();
		if (x < 0 || board[x][y] != 'O') break;
		S[pos].pop();
	}
	for (auto [x, y] = S[pos].top(); ;) {
		if (x + 1 == n || board[x + 1][y] == 'X') { board[x][y] = 'O', S[pos].pop(); break; }
		if (board[x + 1][y] == '.') S[pos].push({ ++x, y });
		else {
			if (y - 1 >= 0 && board[x][y - 1] == '.' && board[x + 1][y - 1] == '.') S[pos].push({ ++x, --y });
			else if (y + 1 < m && board[x][y + 1] == '.' && board[x + 1][y + 1] == '.') S[pos].push({ ++x, ++y });
			else { board[x][y] = 'O', S[pos].pop(); break; }
		}
	}
}

int main() {
	fastio;
	cin >> n >> m;
	for (int i = 0; i < n; i++) cin >> board[i];
	for (int i = 0; i < m; i++) S[i].push({ -1, i });
	int q; cin >> q;
	for (int t; q-- && cin >> t; Query(--t));
	for (int i = 0; i < n; i++) cout << board[i] << '\n';
}