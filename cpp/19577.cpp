#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

using i64 = long long;

int Phi(int n) {
	int ret = n;
	for (int i = 2; i * i <= n; i++) {
		if (n % i) continue;
		ret = ret / i * (i - 1);
		while (n % i == 0) n /= i;
	}
	if (n > 1) ret = ret / n * (n - 1);
	return ret;
}

int Sol(const int n) {
	for (int i = 1; i * i <= n; i++) {
		if (n % i) continue;
		if ((i64)i * Phi(i) == n) return i;
		if ((i64)(n / i) * Phi(n / i) == n) return n / i;
	}
	return -1;
}

int main() {
	fastio;
	int n; cin >> n;
	cout << Sol(n) << '\n';
}