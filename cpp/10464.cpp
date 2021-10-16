#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int F(const int n) {
	int ret = n + 1 >> 1 & 1;
	for (int i = 1; i < 30; i++)
		if (n >> i & 1 && ~n & 1) ret |= 1 << i;
	return ret;
}

int main() {
	fastio;
	int N; cin >> N;
	while (N--) {
		int a, b; cin >> a >> b;
		cout << (F(a - 1) ^ F(b)) << '\n';
	}
}