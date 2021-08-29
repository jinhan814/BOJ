#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int n, m, cnt;
string v[100];

int main() {
	fastio;
	cin >> n >> m;
	for (int i = 0; i < n; i++) cin >> v[i];
	for (int i = n - 1; i >= 0; i--) for (int j = m - 1; j >= 0; j--) {
		if (v[i][j] == '0') continue;
		for (int x = 0; x <= i; x++) for (int y = 0; y <= j; y++) v[x][y] ^= 1;
		cnt++;
	}
	cout << cnt << '\n';
}