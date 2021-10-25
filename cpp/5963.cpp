#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

#define int int64_t

struct Factorial {
	int F[21]{ 1 };
	Factorial() { for (int i = 1; i <= 20; i++) F[i] = F[i - 1] * i; }
	int operator[] (int i) { return F[i]; }
} F;

void Query1(const int n, int k) {
	vector<int> check(n + 1), res(n);
	for (int i = 0; i < n; i++) {
		int cnt = 0, j = 1;
		while (cnt * F[n - 1 - i] < k) {
			while (check[j]) j++;
			cnt++, j++;
		}
		res[i] = --j, check[j] = 1;
		k -= --cnt * F[n - 1 - i];
	}
	for (auto& i : res) cout << i << ' '; cout << '\n';
}

void Query2(const vector<int>& v) {
	int n = v.size(), res = 1;
	vector<int> check(n + 1);
	for (int i = 0; i < n - 1; check[v[i++]] = 1) {
		int cnt = 0;
		for (int j = 1; j < v[i]; j++) if (!check[j]) cnt++;
		res += cnt * F[n - 1 - i];
	}
	cout << res << '\n';
}

int32_t main() {
	fastio;
	int n, q; cin >> n >> q;
	while (q--) {
		char c; cin >> c;
		if (c == 'P') {
			int k; cin >> k;
			Query1(n, k);
		}
		else {
			vector<int> v(n);
			for (int i = 0; i < n; i++) cin >> v[i];
			Query2(v);
		}
	}
}