#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

constexpr int MOD = 100003;
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
	int N = 2; while (N < a.size() + b.size()) N <<= 1;
	A.resize(N); B.resize(N);
	FFT(A, 0); FFT(B, 0);
	for (int i = 0; i < N; i++) A[i] *= B[i];
	FFT(A, 1);
	vector<int> ret(N);
	for (int i = 0; i < ret.size(); i++) ret[i] = (int64_t)round(A[i].real()) % MOD;
	while (ret.size() && ret.back() == 0) ret.pop_back();
	return ret;
}

vector<int> Mul(const vector<vector<int>>& v, int l, int r) {
	if (l == r) return v[l];
	const int mid = l + r >> 1;
	auto&& res1 = Mul(v, l, mid);
	auto&& res2 = Mul(v, mid + 1, r);
	return Mul(res1, res2);
}

int main() {
	fastio;
	int n; cin >> n;
	vector<vector<int>> v(n);
	for (int i = 0, t; i < n && cin >> t; v[i].push_back(t), v[i++].push_back(1));
	auto res = Mul(v, 0, n - 1);
	int q; cin >> q;
    for (int t; q-- && cin >> t; cout << res[n - t] << '\n');
}