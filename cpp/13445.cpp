#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

using ll = long long;
using vi = vector<ll>;

void FST(vi& v, bool inv) {
	const int n = v.size();
	for (int step = 1; step < n; step *= 2) {
		for (int i = 0; i < n; i += 2 * step) {
			for (int j = i; j < i + step; j++) {
				ll a = v[j], b = v[j + step];
				v[j] = a + b;
				v[j + step] = a - b;
			}
		}
	}
	if (inv) for (auto& i : v) i /= n;
}

vi Conv(vi a, vi b) {
	FST(a, 0), FST(b, 0);
	for (int i = 0; i < a.size(); i++) a[i] *= b[i];
	FST(a, 1); return a;
}

int main() {
	fastio;
	int n, k; cin >> n >> k;
	vector<ll> cnt(1 << 17); cnt[0] = 1;
	for (int prv = 0, i = 0, t; i < n && cin >> t; i++, cnt[prv ^= t]++);
	auto res = Conv(cnt, cnt); res[0] -= n + 1;
	auto sum = reduce(res.begin(), min(res.begin() + k, res.end())) / 2;
	cout << sum << '\n';
}