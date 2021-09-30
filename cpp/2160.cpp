#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

using board = array<string, 5>;

int operator* (const board& a, const board& b) {
	int ret = 0;
	for (int i = 0; i < 5; i++) for (int j = 0; j < 7; j++)
		if (a[i][j] != b[i][j]) ret++;
	return ret;
}

int main() {
	fastio;
	int n, mn = 1e9, a, b; cin >> n;
	vector<board> v(n);
	for (int i = 0; i < n; i++) for (int j = 0; j < 5; j++) cin >> v[i][j];
	for (int i = 0; i < n; i++) for (int j = i + 1; j < n; j++) {
		const int score = v[i] * v[j];
		if (mn > score) mn = score, a = i, b = j;
	}
	cout << a + 1 << ' ' << b + 1 << '\n';
}