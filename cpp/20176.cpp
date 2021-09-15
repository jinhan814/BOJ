#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

using ll = long long;
using cpx = complex<double>;

void fft(vector<cpx>& f, bool inv = 0) {
	int n = f.size(), j = 0;
	vector<cpx> root(n >> 1);
	for (int i = 1; i < n; i++) {
		int bit = n >> 1;
		while (j >= bit) j -= bit, bit >>= 1;
		j += bit;
		if (i < j) swap(f[i], f[j]);
	}
	double ang = 2 * acos(-1) / n * (inv ? -1 : 1);
	for (int i = 0; i < n / 2; i++) root[i] = cpx(cos(ang * i), sin(ang * i));
	for (int i = 2; i <= n; i <<= 1) {
		int step = n / i;
		for (int j = 0; j < n; j += i) for (int k = 0; k < i / 2; k++) {
			cpx u = f[j + k], v = f[j + k + i / 2] * root[step * k];
			f[j + k] = u + v; f[j + k + i / 2] = u - v;
		}
	}
	if (inv) for (int i = 0; i < n; i++) f[i] /= n;
}

vector<ll> multiply(vector<ll> _a, vector<ll> _b) {
	vector<cpx> a(_a.begin(), _a.end()), b(_b.begin(), _b.end());
	int N = 2; while (N < _a.size() + _b.size()) N <<= 1;
	a.resize(N); b.resize(N);
	fft(a, 0); fft(b, 0);
	for (int i = 0; i < N; i++) a[i] *= b[i];
	fft(a, 1);
	vector<ll> ret(N);
	for (int i = 0; i < N; i++) ret[i] = (ll)round(a[i].real());
	return ret;
}

int main() {
	fastio;
	ll n, cnt = 0; vector<ll> a(1 << 16), b(1 << 16), c(1 << 16);
	cin >> n; for (int t; n-- && cin >> t;) a[t + 30'000]++;
	cin >> n; for (int t; n-- && cin >> t;) b[t + 30'000]++;
	cin >> n; for (int t; n-- && cin >> t;) c[t + 30'000]++;
	auto res = multiply(a, c);
	for (int i = 0; i <= 60'000; i++) cnt += b[i] * res[2 * i];
	cout << cnt << '\n';
}