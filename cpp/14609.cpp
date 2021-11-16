#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

#define double long double
constexpr double EPS = 1e-9L;

double n, m, a, b;
double S, dx, v[11];

double Pow(double x, int n) {
	double ret = 1;
	for (; n; n >>= 1) n & 1 && (ret *= x), x *= x;
	return ret;
}

double f(double x) {
	double ret = 0;
	for (int i = 0; i <= n; i++) ret += v[i] * Pow(x, i);
	return ret;
}

double F(double x) {
	double ret = 0;
	for (int i = 0; i <= n; i++) ret += v[i] * Pow(x, i + 1) / (i + 1);
	return ret;
}

double G(double x) {
	double ret = 0;
	for (int i = 0; i < m; i++) ret += f(x + i * dx);
	return ret;
}

int main() {
	fastio;
	cin >> n;
	for (int i = n; ~i; i--) cin >> v[i];
	cin >> a >> b >> m;
	S = F(b) - F(a), dx = (b - a) / m;

	double lo = a, hi = a + dx;
	while (hi - lo > EPS) {
		const double mid = (lo + hi) / 2;
		if (G(mid) * dx < S) lo = mid;
		else hi = mid;
	}
	cout << fixed << setprecision(20) << lo - a << '\n';
}