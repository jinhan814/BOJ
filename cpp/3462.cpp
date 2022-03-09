#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

bool Sol(int n, int m) {
	if (n < m) return 0;
	n -= m; m = m - 1 >> 1;
	return !(n & m);
}

int main() {
	fastio;
	int N; cin >> N;
	while (N--) {
		int n, m; cin >> n >> m;
		cout << Sol(n, m) << '\n';
	}
}