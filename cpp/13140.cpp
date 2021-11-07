#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

constexpr int v[2][5] = { { 0, 1, 2, 2, 3 }, { 4, 3, 5, 2, 6 } };
constexpr int w[7] = { 10000, 1000, 120, 1001, 10000, 100, 1 };

int main() {
	fastio;
	int n, p[10]{ 1, 0, 2, 3, 4, 5, 6, 7, 8, 9 }; cin >> n;
	do {
		int t = 0; for (int i = 0; i < 7; i++) t += w[i] * p[i];
		if (t ^ n || p[4] == 0) continue;
		cout << "  "; for (int i = 0; i < 5; i++) cout << p[v[0][i]]; cout << '\n';
		cout << "+ "; for (int i = 0; i < 5; i++) cout << p[v[1][i]]; cout << '\n';
		cout << "-------" << '\n';
		cout << (n < 100000 ? "  " : " ") << n << '\n';
		return 0;
	} while (next_permutation(p, p + 10));
	cout << "No Answer" << '\n';
}