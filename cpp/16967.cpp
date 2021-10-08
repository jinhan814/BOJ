#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int main() {
	fastio;
	int a, b, c, d; cin >> a >> b >> c >> d;
	vector<vector<int>> v(a, vector<int>(b));
	for (int i = 0; i < a + c; i++) for (int j = 0; j < b + d; j++) {
		int val; cin >> val;
		const bool flag1 = i < a && j < b;
		const bool flag2 = i >= c && j >= d;
		if (flag1 && flag2) v[i][j] = val - v[i - c][j - d];
		else if (flag1) v[i][j] = val;
		else if (flag2) v[i - c][j - d] = val;
	}
	for (int i = 0; i < a; i++) {
		for (int j = 0; j < b; j++) cout << v[i][j] << ' ';
		cout << '\n';
	}
}