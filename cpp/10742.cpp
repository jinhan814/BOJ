#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

using ll = long long;

int n, k;
ll P[300'001];

bool Check(const double mid) {
	double mn = 1e9 + 7;
	for (int i = k; i <= n; i++) {
		mn = min(mn, P[i - k] - mid * (i - k));
		if (P[i] - mid * i >= mn) return 1;
	}
	return 0;
}

int main() {
	fastio;
	cin >> n >> k;
	for (int i = 1; i <= n; i++) cin >> P[i], P[i] += P[i - 1];
	double lo = 0, hi = 1e6 + 7;
	while (hi - lo > 1e-6) {
		const double mid = (lo + hi) / 2;
		if (Check(mid)) lo = mid;
		else hi = mid;
	}
	cout << fixed << setprecision(10) << lo << '\n';
}