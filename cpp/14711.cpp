#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int n; string board[1000];
bitset<1000> check[1000];

int main() {
	fastio;
	cin >> n >> board[0];
	for (int i = 1; i < n; i++) {
        board[i].resize(n);
		for (int j = 0; j < n; j++) {
			if (board[i - 1][j] != '#') continue;
			for (int k = 0; k < 4; k++) {
				int nx = i - 1 + "1012"[k] - '1';
				int ny = j + "2101"[k] - '1';
				if (nx < 0 || nx >= n || ny < 0 || ny >= n) continue;
				check[nx][ny].flip();
			}
		}
		for (int j = 0; j < n; j++) {
			board[i][j] = check[i - 1][j] ? '#' : '.';
		}
	}
    for (int i = 0; i < n; i++) cout << board[i] << '\n';
}