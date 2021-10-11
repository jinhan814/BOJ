#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

#define OOB(x, y) (x < 0 || x >= n || y < 0 || y >= n)

int main() {
	fastio;
	int n, ans = 0; cin >> n;
	vector<string> v(n);
	for (int i = 0; i < n; i++) cin >> v[i];

	auto Check = [&](int x, int y) -> bool {
		if (!isdigit(v[x][y])) return 1;
		int cnt = 0;
		for (int k = 0; k < 8; k++) {
			int nx = x + "10001222"[k] - '1';
			int ny = y + "22100012"[k] - '1';
			if (OOB(nx, ny)) continue;
			if (v[nx][ny] == '!') cnt++;
		}
		return cnt <= (v[x][y] & 15);
	};

	for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) {
		if (v[i][j] != '#') continue;
		bool flag = 1; v[i][j] = '!';
		for (int k = 0; k < 8; k++) {
			int nx = i + "10001222"[k] - '1';
			int ny = j + "22100012"[k] - '1';
			if (!OOB(nx, ny) && !Check(nx, ny)) flag = 0;
		}
		if (!flag) v[i][j] = '#';
		else ans++;
	}
	cout << ans << '\n';
}