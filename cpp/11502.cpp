#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

template<size_t sz = 1'000>
struct LinearSieve {
	vector<int> p;
	int sieve[sz + 1]; // sieve[i] : IsPrime(i) ? 0 : smallest prime factor
	LinearSieve() : sieve{} {
		sieve[0] = sieve[1] = -1;
		for (int i = 2; i <= sz; i++) {
			if (!sieve[i]) p.push_back(i);
			for (auto j : p) {
				if (i * j > sz) break;
				sieve[i * j] = j;
				if (i % j == 0) break;
			}
		}
	}
	bool IsPrime(int n) { return !sieve[n]; }
}; LinearSieve Sieve;

pair<int, int> v[1'001];

int main() {
	fastio;
	for (auto& i : Sieve.p) for (auto& j : Sieve.p)
		if (i < j && i + j <= 1'000) v[i + j] = { i, j };

	auto Sol = [&](int n) -> tuple<int, int, int> {
		for (auto& i : Sieve.p) {
			if (i <= n && v[n - i] != pair<int, int>{ 0, 0 }) {
				int a = i, b = v[n - i].first, c = v[n - i].second;
				if (a > b) swap(a, b); if (a > c) swap(a, c); if (b > c) swap(b, c);
				return { a, b, c };
			}
		}
		return { -1, -1, -1 };
	};

	int N; cin >> N;
	while (N--) {
		int n; cin >> n;
		auto [a, b, c] = Sol(n);
		if (a) cout << a << ' ' << b << ' ' << c << '\n';
		else cout << 0 << '\n';
	}
}