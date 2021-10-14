#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int n, m, q;
bitset<500> BIT[500], RES[500], T[500][4];
string s;

void Move(int d) {
	if (d == 0) {
		for (int i = 0; i < n; i++) T[i][d] = BIT[i] & (RES[i] << 1);
	}
	else if (d == 1) {
		for (int i = 0; i < m - 1; i++) T[i][d] = BIT[i] & (RES[i + 1]);
		T[m - 1][d].reset();
	}
	else if (d == 2) {
		for (int i = 0; i < n; i++) T[i][d] = BIT[i] & (RES[i] >> 1);
	}
	else if (d == 3) {
		for (int i = 1; i < m; i++) T[i][d] = BIT[i] & (RES[i - 1]);
		T[0][d].reset();
	}
}

int main() {
	fastio;
	cin >> n >> m >> q;
	for (int i = 0; i < n; i++) {
		cin >> s;
		for (int j = 0; j < m; j++) if (s[j] == '.') BIT[i][j] = RES[i][j] = 1;
	}

	cin >> s;
	for (const auto& c : s) {
		if (c == '?') {
			for (int i = 0; i < 4; i++) Move(i);
			for (int i = 0; i < n; i++) RES[i] = T[i][0] | T[i][1] | T[i][2] | T[i][3];
		}
		else {
			const int d = string("ENWS").find(c); Move(d);
			for (int i = 0; i < n; i++) RES[i] = T[i][d];
		}
	}

	int ans = 0;
	for (int i = 0; i < n; i++) ans += RES[i].count();
	cout << ans << '\n';
}