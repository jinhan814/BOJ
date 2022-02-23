#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int Sol(int n, int k) {
	int ret = 1;
	for (int i = 2; i <= n; i++) {
		const int cur = k % i;
		if (ret <= i - cur) ret += cur;
		else ret -= i - cur;
	}
	return ret;
}

int main() {
	fastio;
	int n, k; cin >> n >> k;
	cout << Sol(n, k) << '\n';
}