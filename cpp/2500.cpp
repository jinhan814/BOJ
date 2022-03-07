#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

constexpr int MOD = 42043;
using ll = long long;
using cpx = complex<double>;

void FFT(vector<cpx>& f, bool inv = 0) {
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

vector<int> Mul(vector<int> a, vector<int> b) {
	vector<cpx> A(a.begin(), a.end()), B(b.begin(), b.end());
	int N = 2;
	while (N < a.size() + b.size()) N <<= 1;
	A.resize(N); B.resize(N);
	FFT(A, 0); FFT(B, 0);
	for (int i = 0; i < N; i++) A[i] *= B[i];
	FFT(A, 1);
	vector<int> ret(N);
	for (int i = 0; i < ret.size(); i++) ret[i] = (ll)round(A[i].real()) % MOD;
	while (ret.size() && ret.back() == 0) ret.pop_back();
	return ret;
}

vector<int> Pow(vector<int> x, int n) {
	const int k = x.size(); vector<int> ret{ 1 };
	for (; n; n >>= 1) {
		if (n & 1) ret = Mul(ret, x), ret.resize(k);
		x = Mul(x, x), x.resize(k);
	}
	return ret;
}

int main() {
	fastio;
	int n, k, m; cin >> n >> k >> m;
	vector<int> v(k + 1);
	for (int i = 0; i < m; i++) {
		int t; cin >> t;
		if (t <= k) v[t]++;
	}
	auto res = Pow(v, n);
	cout << accumulate(res.begin(), res.end(), 0LL) % MOD << '\n';
}