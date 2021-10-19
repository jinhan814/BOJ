#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

#define int int64_t
#define double long double

using pii = pair<int, int>;
constexpr double PI = 3.141592653589793238;

int CCW(pii a, pii b) { // (a.first, a.second), (b.first, b.second)
    const int t = a.first * b.second - a.second * b.first;
	return t ? t > 0 ? 1 : -1 : 0;
}

double F(pii a, pii b) { // a dot b = |a| * |b| * cos(theta)
	double t1 = (a.first * b.first + a.second * b.second);
	double t2 = sqrt(a.first * a.first + a.second * a.second + 0.L);
	double t3 = sqrt(b.first * b.first + b.second * b.second + 0.L);
	double val = t1 / t2 / t3;
	if (val < -1.0) val = -1.0;
	if (val >  1.0) val =  1.0;
	return acos(val) / PI * 180;
}

int32_t main() {
	fastio;
	int n; cin >> n;
	vector<pii> v;
	for (int i = 0, mx = 0; i < n; i++) {
		int a, b; cin >> a >> b;
		const int r = a * a + b * b;
		if (mx < r) v.clear(), mx = r;
		if (mx == r) v.push_back({ a, b });
	}

	sort(v.begin(), v.end(), [](const pii& a, const pii& b) -> bool {
		if (a > pii(0, 0) ^ b > pii(0, 0)) return a > b;
		if (CCW(a, b)) return CCW(a, b) > 0;
        return 0;
	});

    auto Sol = [&]() -> double {
        if (v.size() == 1) return 360;
        double ret = 0;
        for (int i = 0; i < v.size(); i++) {
            const double t = F(v[i], v[(i + 1) % v.size()]);
            const int flag = CCW(v[i], v[(i + 1) % v.size()]);
            ret = max(ret, flag > 0 ? t : 360 - t);
        }
        return ret;
    };
	cout << fixed << setprecision(20) << Sol() << '\n';
}