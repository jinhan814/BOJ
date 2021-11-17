#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

#define double long double

int n, A;
struct Info { int x, y, val; } I[100'001];

int main() {
	fastio;
	cin >> n >> A;
	for (int i = 0; i < n; i++) {
		auto& [x, y, val] = I[i];
		cin >> x >> y >> val;
	}
	I[n].x = I[n].y = 1e9;

	sort(I, I + n, [](const Info& a, const Info& b) {
		return a.x * a.x + a.y * a.y < b.x * b.x + b.y * b.y;
	});

	double ans = 0, m = 0, k = 0;
	for (int i = 0; i < n; i++) {
		const auto& [x, y, val] = I[i];
		const auto& [nx, ny, _] = I[i + 1];
		const double r = sqrt(x * x + y * y);
		const double nr = sqrt(nx * nx + ny * ny);
		m += val, k -= val * r;

		const double t = m / 2 / A;
		const double pos = t < r ? r : t <= nr ? t : nr;
		ans = max<double>(ans, m * pos + k - A * pos * pos);
	}
	cout << fixed << setprecision(20) << ans << '\n';
}